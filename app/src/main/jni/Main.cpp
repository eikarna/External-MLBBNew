#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <vector>
#include <map>
#include <chrono>
#include <fstream>
#include <thread>
#include <pthread.h>
#include <dirent.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <jni.h>
#include <android/log.h>
#include <elf.h>
#include <dlfcn.h>
#include <sys/system_properties.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/native_window.h>

#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui.h"
#include "imgui_additional.h"
#include "imgui_themes.h"
#include "backends/imgui_impl_android.h"
#include "backends/imgui_impl_opengl3.h"
#include "fonts/GoogleSans.h"

#include "Tools/xDL/xdl.h"
#include "Tools/fake_dlfcn.h"
#include "Tools/Il2Cpp.h"
#include "Tools/Tools.h"
#include "Tools/Logger.h"

#include "struct/Vector3.hpp"
#include "struct/Vector2.h"
#include "struct/Rect.h"
#include "struct/Quaternion.h"

#include "config/setup.h"
#include "config/JNIStuff.h"

#include "TouchSystem.h"

#include "icon/DrawIcon.h"

#include "login/Login.h"

#include "feature/class.h"
#include "feature/ToString.h"
#include "feature/room.h"
#include "feature/esp.h"
#include "feature/protection.h"
#include "feature/AutoSkill.h"
#include "feature/TrySkill.h"
#include "feature/Retribution.h"
#include "Menu.h"

// ====================
// GLOBAL STATE
// ====================
static bool modInitialized = false;
static pthread_t mainThread = 0;
EGLBoolean (*orig_eglSwapBuffers)(...);

// ====================
// FORWARD DECLARATIONS
// ====================
void initializeImGui(EGLDisplay dpy, EGLSurface surface);
void renderImGuiFrame(EGLDisplay dpy);
void* main_thread(void*);
jint JNICALL hook_JNI_OnLoad(JavaVM* vm, void* reserved);

// ====================
// EGL HOOK IMPLEMENTATION
// ====================
EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);
    
    if (!(glWidth > 0 && glHeight > 0))
        return orig_eglSwapBuffers(dpy, surface);

    if (!g_Initialized) {
        initializeImGui(dpy, surface);
    }

    renderImGuiFrame(dpy);
    return orig_eglSwapBuffers(dpy, surface);
}

void initializeImGui(EGLDisplay dpy, EGLSurface surface) {
    ImGui::CreateContext();
    ImGuiStyle* style = &ImGui::GetStyle();

    SetAnotherDarkThemeReally();
    style->WindowBorderSize = 1.0f;
    style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style->ScaleAllSizes(1.8f);

    ImGuiIO* io = &ImGui::GetIO();
    io->IniFilename = nullptr;
    io->DisplaySize = ImVec2((float)glWidth, (float)glHeight);

    ImGui_ImplOpenGL3_Init("#version 300 es");

    ImFontConfig font_cfg;
    io->Fonts->AddFontFromMemoryCompressedTTF(
        GoogleSans_compressed_data, 
        GoogleSans_compressed_size, 
        23.0f,
        &font_cfg, 
        io->Fonts->GetGlyphRangesChineseFull()
    );

    setRes(glWidth, glHeight);
    g_Initialized = true;
}

void renderImGuiFrame(EGLDisplay dpy) {
    ImGuiIO* io = &ImGui::GetIO();

    ImGui_ImplOpenGL3_NewFrame();
    ImplAndroid_NewFrame();
    ImGui::NewFrame();

    // Handle resolution changes
    if (screenWidth < glWidth && screenHeight < glHeight)
        setRes(glWidth, glHeight);

    if (screenWidth != Screen::get_width() || 
        screenHeight != Screen::get_height()) {
        Screen::SetResolution(screenWidth, screenHeight, true);
    }

    // Handle touch input
    ImGui_GetTouch(io, screenHeight);

    // Toggle menu visibility
    const ImVec2 hideShowMin(0, screenHeight - 80);
    const ImVec2 hideShowMax(80, screenHeight);
    const ImVec2 mousePos = io->MousePos;

    if (mousePos.x >= hideShowMin.x && mousePos.x <= hideShowMax.x &&
        mousePos.y >= hideShowMin.y && mousePos.y <= hideShowMax.y) {
        State::showMenu = true;
    }

    // Game features
    GusionSkill();
    
    if (State::showMenu)
        UISystem::ShowMenu();

    if (State::bFullChecked)
        drawESP(ImGui::GetBackgroundDrawList(), screenWidth, screenHeight);

    // Initialize icons and spells
    static bool AttachIconDone = false;
    static bool AttachSpellDone = false;
    
    if (!AttachIconDone) {
        AttachIcon();
        AttachIconDone = true;
    }

    if (!AttachSpellDone) {
        AttachSpell();
        AttachSpellDone = true;
    }

    // Finalize frame
    ImGui::EndFrame();
    ImGui::Render();
    glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (clearMousePos) {
        io->MousePos = ImVec2(-1, -1);
        clearMousePos = false;
    }
}

// ====================
// MAIN MOD THREAD
// ====================
void* main_thread(void*) {
    LOGI(OBFUSCATE("main_thread created"));

    // Wait for main library
    const int MAX_ATTEMPTS = 30;
    int attempts = 0;
    
    while (!m_IL2CPP && attempts < MAX_ATTEMPTS) {
        m_IL2CPP = Tools::GetBaseAddress("liblogic.so");
        if (!m_IL2CPP) {
            LOGI(OBFUSCATE("Waiting for liblogic.so..."));
            sleep(1);
            attempts++;
        }
    }

    if (!m_IL2CPP) {
        LOGE(OBFUSCATE("Failed to find liblogic.so"));
        return nullptr;
    }

    // Wait for EGL
    while (!m_EGL) {
        m_EGL = dlopen_ex("libEGL.so", RTLD_NOW);
        sleep(1);
    }

    // Initialize and hook
    Il2CppAttach("liblogic.so");
    sleep(10);
    
    void* eglSwapBuffersAddr = dlsym_ex(m_EGL, "eglSwapBuffers");
    Tools::Hook(eglSwapBuffersAddr, (void*)_eglSwapBuffers, (void**)&orig_eglSwapBuffers);
    
    sleep(20);
    
    Tools::Hook(
        (void*)ShowSelfPlayer_OnUpdate, 
        (void*)ShowSelfPlayerOnUpdate,
        (void**)&oShowSelfPlayerOnUpdate
    );
    
    Tools::Hook(
        (void*)ShowSelfPlayer_TryUseSkill, 
        (void*)TryUseSkill,
        (void**)&orig_TryUseSkill
    );
    
    return nullptr;
}

// ====================
// JNI ENTRY POINT
// ====================
jint(JNICALL *Real_JNI_OnLoad)(JavaVM *vm, void *reserved);

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    if (modInitialized) {
        LOGI(OBFUSCATE("Mod already initialized, skipping"));
        return Real_JNI_OnLoad ? 
            Real_JNI_OnLoad(vm, reserved) : 
            JNI_VERSION_1_6;
    }
    modInitialized = true;

    LOGI(OBFUSCATE("AkSoundEngine called!"));
    JNIEnv *env;
    
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        LOGE(OBFUSCATE("Failed to get JNIEnv"));
        return JNI_ERR;
    }
    g_vm = vm;

    // Get package info
    const std::string apkPkg = getPackageName(GetJNIEnv(g_vm));
    LOGI("Package name %s", apkPkg.c_str());
    
    // Prepare paths
    const char* LIB_AK_SOUND = OBFUSCATE("libAkSoundEngine.so");
    const char* LIB_AK_BYTES = OBFUSCATE("libAkSoundEngine.bytes");
    const char* LIB_AK_ORI1 = OBFUSCATE("libAkSoundEngine+.bytes");
    const char* LIB_AK_ORI2 = OBFUSCATE("libAkSoundEngine+.so");
    
    const std::string localPath = 
        std::string(OBFUSCATE("/storage/emulated/0/Android/data/")) + 
        apkPkg + 
        std::string(OBFUSCATE("/files/dragon2017/assets/comlibs/")) +
        std::string(ARCH);
    
    const std::string rootPath = 
        std::string(OBFUSCATE("/data/data/")) + 
        apkPkg + 
        std::string(OBFUSCATE("/app_libs"));
    
    const std::string pathAkSound = rootPath + "/" + LIB_AK_SOUND;
    const std::string pathAkSoundBytes = localPath + "/" + LIB_AK_BYTES;
    const std::string pathAkSoundOri1 = localPath + "/" + LIB_AK_ORI1;
    const std::string pathAkSoundOri2 = rootPath + "/" + LIB_AK_ORI2;

    // Initialize mod
    if (CopyFile(pathAkSoundOri1.c_str(), pathAkSoundOri2.c_str())) {
        void* handle = dlopen(pathAkSoundOri2.c_str(), RTLD_NOW);
        
        if (!handle) {
            LOGE("dlopen failed: %s", dlerror());
            handle = dlopen(pathAkSoundOri2.c_str(), RTLD_NOW);
            sleep(10);
        }
        
        auto Hook_JNI_OnLoad = dlsym(handle, OBFUSCATE("JNI_OnLoad"));
        
        if (Hook_JNI_OnLoad) {
            LOGI(OBFUSCATE("Found Real JNI_OnLoad!"));
            Real_JNI_OnLoad = decltype(Real_JNI_OnLoad)(Hook_JNI_OnLoad);
            
            if (mainThread == 0) {
                if (pthread_create(&mainThread, nullptr, main_thread, nullptr) != 0) {
                    LOGE(OBFUSCATE("Failed to create main_thread"));
                }
            }
            
            jint ret = Real_JNI_OnLoad(vm, reserved);
            LOGI("Real_JNI_OnLoad returned: %d", ret);
            return ret;
        } else {
            LOGE("dlsym for JNI_OnLoad failed: %s", dlerror());
        }
    }
    return JNI_ERR;
}
