LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libdobby
LOCAL_SRC_FILES := dobby/libraries/$(TARGET_ARCH_ABI)/libdobby.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/dobby/
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := libcrypto
LOCAL_SRC_FILES := login/library/$(TARGET_ARCH_ABI)/lib/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := libssl
LOCAL_SRC_FILES := login/library/$(TARGET_ARCH_ABI)/lib/libssl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := libcurl
LOCAL_SRC_FILES := login/library/$(TARGET_ARCH_ABI)/lib/libcurl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := AkSoundEngine+
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/imgui
LOCAL_C_INCLUDES += $(LOCAL_PATH)/login
LOCAL_C_INCLUDES += $(LOCAL_PATH)/login/library/$(TARGET_ARCH_ABI)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/anti/arch/$(TARGET_ARCH_ABI)

LOCAL_LDLIBS := -landroid -lEGL -lGLESv3 -lz -ldl -lc -llog
LOCAL_CFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS += -fno-rtti -fexceptions -fpermissive
LOCAL_CPPFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -std=c++17 -w
LOCAL_CPPFLAGS += -fms-extensions -fno-rtti -fpermissive
LOCAL_LDFLAGS += -Wl,--gc-sections
LOCAL_ARM_MODE := arm

LOCAL_STATIC_LIBRARIES := libdobby \
libcrypto \
libssl \
libcurl

LOCAL_SRC_FILES := imgui/imgui.cpp \
imgui/imgui_demo.cpp \
imgui/imgui_draw.cpp \
imgui/imgui_tables.cpp \
imgui/imgui_widgets.cpp \
imgui/stb_image.cpp \
imgui/backends/imgui_impl_android.cpp \
imgui/backends/imgui_impl_opengl3.cpp \
Tools/xDL/xdl.c \
Tools/xDL/xdl_iterate.c \
Tools/xDL/xdl_linker.c \
Tools/xDL/xdl_lzma.c \
Tools/xDL/xdl_util.c \
Tools/fake_dlfcn.cpp \
Tools/Il2Cpp.cpp \
Tools/Tools.cpp \
login/Tools.cpp \
Main.cpp

# Suppress warnings for stb_image.cpp
# LOCAL_CFLAGS_stb_image.cpp := -Wno-writable-strings
# LOCAL_CPPFLAGS_stb_image.cpp := -Wno-writable-strings
                      
include $(BUILD_SHARED_LIBRARY)
