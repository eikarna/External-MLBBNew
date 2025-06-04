#pragma once
#include <imgui.h>
#include <string>
#include <imgui.h>
#include <imgui_internal.h> // Untuk ImFormatStringToTempBufferV
#include "config/JNIStuff.h" // Untuk fungsi JNI
#include <cstring> // untuk strncpy
#include <thread>  // untuk std::thread

// ======================
// Utility Functions
// ======================
namespace Utils {
    [[noreturn]] static void crash(int randomval) {
      volatile int* p = reinterpret_cast<int*>(0xfa91b9cd);
      p += randomval;
      p += *p + randomval;
      // Perbaikan di bawah ini
      volatile int* null_ptr = nullptr;
      *null_ptr = 0; // Force null pointer crash
    }

    void CenteredText(ImColor color, const char* fmt, ...);
    ImVec4 RGBA2ImVec4(int r, int g, int b, int a);
}

// ======================
// Feature Structures
// ======================
namespace Features {
    struct ESP {
        // Player ESP
        bool Line = false;
        bool Round = false;
        bool Name = false;
        bool Hero = false;
        bool Health = false;
        bool Alert = false;

        // Info ESP
        bool SkillCD = false;
        bool SpellCD = false;

        // Jungle ESP
        bool MRound = false;
        bool MHealth = false;

        // Minimap
        bool MinimapIcon = false;
        bool HideLine = false;
        int SetAjust = 2;
    };

    struct Auto {
        bool SwordLing = false;
        bool Karina = false;
        bool GusionSkills = false;
        bool Gusion = false;
        bool Gusion2 = false;
        bool Martis = false;
        bool Zilong = false;
    };

    struct Aim {
        enum TargetMode { CLOSEST, LOWEST_HP, LOWEST_HP_PERCENT };
        TargetMode Target = CLOSEST;
        
        bool AutoTakeSword = false;
        bool Basic = false;
        bool Spell = false;
        bool Skill1 = false;
        bool Skill2 = false;
        bool Skill3 = false;
        bool Skill4 = false;
    };

    struct AutoRetribution {
        bool Buff = false;
        bool Turtle = false;
        bool Lord = false;
        bool Creep = false;
        bool Litho = false;
    };
}

struct RoomInfoStruct {
    struct PlayerInfo {
        std::string Name;
        std::string UserID;
        std::string Verified;
        std::string Rank;
        std::string Star;
        int HeroID;
        int Spell;
    } PlayerB[5], PlayerR[5];
};

namespace ESP {
    int MinimapPos = 49;
    int MinimapSize = 227;
    float ICSize = 20.0f;
    float ICHealthThin = 1.0f;
};

// ======================
// Global State
// ======================
namespace State {
    inline bool showMenu = true;
    inline bool bFullChecked = false;
    inline bool UnlockSkins = false;
    
    inline Features::ESP ESP;
    inline Features::Auto Auto;
    inline Features::Aim Aim;
    inline Features::AutoRetribution AutoRetribution;
    
    inline float SetFieldOfView = 0.0f;
    inline float RangeFOV = 15.0f;
}

// ======================
// UI Components
// ======================
namespace UISystem {
    void HideMenu(bool& bShow);
    void RenderLoginTab(char* userKeyBuffer, bool* isLogin, std::string& loginMessage); // Fixed
                                                              void RenderSettingsTab(float& windowScale, bool& autoResize, bool& showHideConfirm); // Fixed
    void RenderVisualTab();
    void RenderHelperTab();
    void RenderRoomInfoTab();
    void ShowMenu();
}

// ======================
// Thread Functions
// ======================
namespace Threads {
    void LoginThread(const std::string& user_key, bool* success);
    void LoadBattleData();
}

// ======================
// Utils Implementation
// ======================
void Utils::CenteredText(ImColor color, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    const char* text, *text_end;
    ImFormatStringToTempBufferV(&text, &text_end, fmt, args);
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(text, text_end).x) * 0.5f);
    ImGui::TextColoredV(color, fmt, args);
    va_end(args);
}

ImVec4 Utils::RGBA2ImVec4(int r, int g, int b, int a) {
    return ImVec4(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
}

// ======================
// Threads Implementation
// ======================
void Threads::LoginThread(const std::string& user_key, bool* success) {
    // Asumsikan Login() didefinisikan di tempat lain
    std::string message = Login(g_vm, user_key.c_str(), success);
    // Handle thread-safe message passing jika diperlukan
}

void Threads::LoadBattleData() {
    loadBattleData(); // Fungsi eksternal
    State::bFullChecked = true;
}

// ======================
// UI Implementation
// ======================
void UISystem::HideMenu(bool& bShow) {
    if (bShow) ImGui::OpenPopup("ConfirmHide");

    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, 
                                  ImGui::GetIO().DisplaySize.y * 0.5f), 
                           ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    
    if (ImGui::BeginPopupModal("ConfirmHide", nullptr, 
        ImGuiWindowFlags_AlwaysAutoResize | 
        ImGuiWindowFlags_NoMove | 
        ImGuiWindowFlags_NoTitleBar | 
        ImGuiWindowFlags_NoCollapse)) 
    {
        ImGui::Text("Are you sure you want to hide the menu?");
        
        if (ImGui::Button("Yes", ImVec2(120, 0))) {
            State::showMenu = false;
            bShow = false;
            ImGui::CloseCurrentPopup();
        }
        
        ImGui::SameLine();
        
        if (ImGui::Button("No", ImVec2(120, 0))) {
            bShow = false;
            ImGui::CloseCurrentPopup();
        }
        
        ImGui::EndPopup();
    }
}

void UISystem::RenderLoginTab(char* userKeyBuffer, bool* isLogin, std::string& loginMessage) {
    if (ImGui::BeginTabItem("Login Menu")) {
        ImGui::BeginGroupPanel("Please Login! (Copy Key to Clipboard)", ImVec2(0.0f, 0.0f));
        
        // Input text
        ImGui::PushItemWidth(-1);
        ImGui::InputText("##key", userKeyBuffer, 64);
        ImGui::PopItemWidth();

        // Button layout
        if (ImGui::Button("Paste Key", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 0))) {
            std::string key = getClipboardText(g_vm);
            strncpy(userKeyBuffer, key.c_str(), 63);
        }
        ImGui::SameLine();
        
        if (ImGui::Button("Load Saved Key", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
            // Implement saved key loading
        }
        
        if (ImGui::Button("Login", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
            std::thread(Threads::LoginThread, std::string(userKeyBuffer), isLogin).detach();
        }
        
        // Status message
        if (!loginMessage.empty()) {
            ImGui::TextColored(Utils::RGBA2ImVec4(255, 255, 0, 255), "%s", loginMessage.c_str());
        }
        
        ImGui::EndGroupPanel();
        ImGui::EndTabItem();
    }
}

void UISystem::RenderVisualTab() {
    if (!ImGui::BeginTabItem("Visual Menu")) return;

    // Player ESP Section
    ImGui::BeginGroupPanel("Player ESP", ImVec2(0.0f, 0.0f));
    {
        ImGui::Checkbox("Line", &State::ESP.Line);
        ImGui::Checkbox("Round", &State::ESP.Round);
        ImGui::Checkbox("Name", &State::ESP.Name);
        ImGui::Checkbox("Hero", &State::ESP.Hero);
        ImGui::Checkbox("Health", &State::ESP.Health);
    }
    ImGui::EndGroupPanel();

    // Jungle ESP Section
    ImGui::BeginGroupPanel("Jungle ESP", ImVec2(0.0f, 0.0f));
    {
        ImGui::Checkbox("Round", &State::ESP.MRound);
        ImGui::SameLine();
        ImGui::Checkbox("Health", &State::ESP.MHealth);
    }
    ImGui::EndGroupPanel();

    // Info ESP Section
    ImGui::BeginGroupPanel("Info ESP", ImVec2(0.0f, 0.0f));
    {
        ImGui::Checkbox("Skill CD", &State::ESP.SkillCD);
        ImGui::Checkbox("Spell CD", &State::ESP.SpellCD);
        ImGui::Checkbox("Hero Alert", &State::ESP.Alert);
    }
    ImGui::EndGroupPanel();

    // Minimap Section
    ImGui::BeginGroupPanel("Minimap Settings", ImVec2(0.0f, 0.0f));
    {
        ImGui::Checkbox("Show Minimap Icons", &State::ESP.MinimapIcon);
        ImGui::SliderInt("Position", &ESP::MinimapPos, 0, 400);
        ImGui::SliderInt("Size", &ESP::MinimapSize, 0, 600);
        ImGui::SliderFloat("Icon Size", &ICSize, 20, 40, "%.1f");
        ImGui::SliderFloat("Health Thickness", &ICHealthThin, 1, 5, "%.1f");
    }
    ImGui::EndGroupPanel();

    // Camera Section
    ImGui::BeginGroupPanel("Camera Settings", ImVec2(0.0f, 0.0f));
    {
        ImGui::SliderFloat("Drone View", &State::SetFieldOfView, 0, 30, "%.1f");
    }
    ImGui::EndGroupPanel();

    ImGui::EndTabItem();
}

void UISystem::RenderHelperTab() {
    if (!ImGui::BeginTabItem("Helper Menu")) return;

    // Jungle Retribution Section
    ImGui::BeginGroupPanel("Auto Retribution", ImVec2(0.0f, 0.0f));
    {
        ImGui::Checkbox("Buff", &State::AutoRetribution.Buff);
        ImGui::SameLine();
        ImGui::Checkbox("Turtle", &State::AutoRetribution.Turtle);
        ImGui::SameLine();
        ImGui::Checkbox("Lord", &State::AutoRetribution.Lord);
        ImGui::Checkbox("Crab", &State::AutoRetribution.Creep);
        ImGui::SameLine();
        ImGui::Checkbox("Lithowanderer", &State::AutoRetribution.Litho);
    }
    ImGui::EndGroupPanel();

    // Auto Aim Section
    ImGui::BeginGroupPanel("Auto Aim", ImVec2(0.0f, 0.0f));
    {
        ImGui::Checkbox("Basic Attack", &State::Aim.Basic);
        ImGui::SameLine();
        ImGui::Checkbox("Battle Spell", &State::Aim.Spell);
        ImGui::Columns(2, nullptr, false);
        ImGui::Checkbox("Skill 1", &State::Aim.Skill1);
        ImGui::NextColumn();
        ImGui::Checkbox("Skill 2", &State::Aim.Skill2);
        ImGui::Columns(1);
        ImGui::Columns(2, nullptr, false);
        ImGui::Checkbox("Skill 3", &State::Aim.Skill3);
        ImGui::NextColumn();
        ImGui::Checkbox("Skill 4", &State::Aim.Skill4);
        ImGui::Columns(1);
    }
    ImGui::EndGroupPanel();

    // Hero-specific Automation
    ImGui::BeginGroupPanel("Hero Automation", ImVec2(0.0f, 0.0f));
    {
        ImGui::Checkbox("Ling: Manual Sword", &State::Aim.AutoTakeSword);
        ImGui::SameLine();
        ImGui::Checkbox("Auto Sword", &State::Auto.SwordLing);
        ImGui::Checkbox("Karina Combo", &State::Auto.Karina);
        ImGui::SameLine();
        ImGui::Checkbox("Gusion Combo", &State::Auto.Gusion);
        ImGui::Checkbox("Martis Ult", &State::Auto.Martis);
        ImGui::SameLine();
        ImGui::Checkbox("Zilong Charge", &State::Auto.Zilong);
    }
    ImGui::EndGroupPanel();

    // Targeting Logic
    ImGui::BeginGroupPanel("Target Selection", ImVec2(0.0f, 0.0f));
    {
        ImGui::RadioButton("Closest", reinterpret_cast<int*>(&State::Aim.Target), Features::Aim::CLOSEST);
        ImGui::RadioButton("Lowest HP", reinterpret_cast<int*>(&State::Aim.Target), Features::Aim::LOWEST_HP);
        ImGui::RadioButton("Lowest % HP", reinterpret_cast<int*>(&State::Aim.Target), Features::Aim::LOWEST_HP_PERCENT);
        ImGui::SliderFloat("Detection Range", &State::RangeFOV, 0, 200, "%.1f m");
    }
    ImGui::EndGroupPanel();

    ImGui::EndTabItem();
}

// Implementasi fungsi lainnya (RenderRoomInfoTab, RenderSettingsTab, ShowMenu)...
void UISystem::RenderRoomInfoTab() {
    if (!ImGui::BeginTabItem("Room Info")) return;

    // Pastikan data sudah dimuat
    if (!State::bFullChecked) {
        Threads::LoadBattleData();
    }

    // Tampilkan informasi ruangan
    RoomInfoList();  // Fungsi eksternal

    // Tampilkan tim sendiri (Biru)
    ImGui::TextColored(ImVec4(0.0f, 0.8f, 1.0f, 1.0f), "Team");
    if (ImGui::BeginTable("##Team", 7, 
        ImGuiTableFlags_BordersOuter | 
        ImGuiTableFlags_BordersInner | 
        ImGuiTableFlags_ScrollY, 
        ImVec2(0, 200))) 
    {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 100);
        ImGui::TableSetupColumn("Verified", ImGuiTableColumnFlags_WidthFixed, 80);
        ImGui::TableSetupColumn("Rank", ImGuiTableColumnFlags_WidthFixed, 80);
        ImGui::TableSetupColumn("Star", ImGuiTableColumnFlags_WidthFixed, 60);
        ImGui::TableSetupColumn("Hero", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("Spell", ImGuiTableColumnFlags_WidthFixed, 80);
        ImGui::TableHeadersRow();
        
        for (int row = 0; row < 5; row++) {
            ImGui::TableNextRow();
            for (int column = 0; column < 7; column++) {
                ImGui::TableSetColumnIndex(column);
                switch (column) {
                    case 0: ImGui::Text("%s", RoomInfo.PlayerB[row].Name.c_str()); break;
                    case 1: ImGui::Text("%s", RoomInfo.PlayerB[row].UserID.c_str()); break;
                    case 2: ImGui::Text("%s", RoomInfo.PlayerB[row].Verified.c_str()); break;
                    case 3: ImGui::Text("%s", RoomInfo.PlayerB[row].Rank.c_str()); break;
                    case 4: ImGui::Text("%s", RoomInfo.PlayerB[row].Star.c_str()); break;
                    case 5: RoomInfoHero(RoomInfo.PlayerB[row].HeroID); break;
                    case 6: RoomInfoSpell(RoomInfo.PlayerB[row].Spell); break;
                }
            }
        }
        ImGui::EndTable();
    }

    // Tampilkan tim lawan (Merah)
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Enemy");
    if (ImGui::BeginTable("##Enemy", 7, 
        ImGuiTableFlags_BordersOuter | 
        ImGuiTableFlags_BordersInner | 
        ImGuiTableFlags_ScrollY, 
        ImVec2(0, 200))) 
    {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 100);
        ImGui::TableSetupColumn("Verified", ImGuiTableColumnFlags_WidthFixed, 80);
        ImGui::TableSetupColumn("Rank", ImGuiTableColumnFlags_WidthFixed, 80);
        ImGui::TableSetupColumn("Star", ImGuiTableColumnFlags_WidthFixed, 60);
        ImGui::TableSetupColumn("Hero", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("Spell", ImGuiTableColumnFlags_WidthFixed, 80);
        ImGui::TableHeadersRow();
        
        for (int row = 0; row < 5; row++) {
            ImGui::TableNextRow();
            for (int column = 0; column < 7; column++) {
                ImGui::TableSetColumnIndex(column);
                switch (column) {
                    case 0: ImGui::Text("%s", RoomInfo.PlayerR[row].Name.c_str()); break;
                    case 1: ImGui::Text("%s", RoomInfo.PlayerR[row].UserID.c_str()); break;
                    case 2: ImGui::Text("%s", RoomInfo.PlayerR[row].Verified.c_str()); break;
                    case 3: ImGui::Text("%s", RoomInfo.PlayerR[row].Rank.c_str()); break;
                    case 4: ImGui::Text("%s", RoomInfo.PlayerR[row].Star.c_str()); break;
                    case 5: RoomInfoHero(RoomInfo.PlayerR[row].HeroID); break;
                    case 6: RoomInfoSpell(RoomInfo.PlayerR[row].Spell); break;
                }
            }
        }
        ImGui::EndTable();
    }

    ImGui::EndTabItem();
}

void UISystem::RenderSettingsTab(float& windowScale, bool& autoResize, bool& showHideConfirm) {
    if (!ImGui::BeginTabItem("Settings")) return;

    // Menu Settings
    ImGui::BeginGroupPanel("Menu Settings", ImVec2(0.0f, 0.0f));
    {
        ImGui::Checkbox("Unlock All Skins", &State::UnlockSkins);
        ImGui::Checkbox("Auto Resize Window", &autoResize);
        
        // Window Scale
        ImGui::BeginGroupPanel("Window Scale", ImVec2(0.0f, 0.0f));
        ImGui::SliderFloat("##Scale", &windowScale, 0.5f, 1.5f, "%.1f");
        ImGui::EndGroupPanel();
        
        // Hide Menu Button
        if (ImGui::Button("Hide Menu", ImVec2(0.0f, 0.0f))) {
            showHideConfirm = true;
        }
    }
    ImGui::EndGroupPanel();

    // Instructions
    ImGui::BeginGroupPanel("English Instructions", ImVec2(0.0f, 0.0f));
    {
        ImGui::TextColored(Utils::RGBA2ImVec4(255, 255, 0, 255), "To display the menu again,");
        ImGui::TextColored(Utils::RGBA2ImVec4(255, 255, 0, 255), "touch the lower left corner of your screen");
    }
    ImGui::EndGroupPanel();

    ImGui::BeginGroupPanel("Instruksi Bahasa Indonesia", ImVec2(0.0f, 0.0f));
    {
        ImGui::TextColored(Utils::RGBA2ImVec4(255, 255, 0, 255), "Untuk menampilkan menu kembali,");
        ImGui::TextColored(Utils::RGBA2ImVec4(255, 255, 0, 255), "sentuh pojok kiri bawah layar Anda");
    }
    ImGui::EndGroupPanel();

    // Additional Features
    ImGui::BeginGroupPanel("Experimental Features", ImVec2(0.0f, 0.0f));
    {
        ImGui::TextWrapped("Note: These features are still in testing phase");
        if (ImGui::Button("Clear Cache", ImVec2(0.0f, 0.0f))) {
            // Implement cache clearing
        }
    }
    ImGui::EndGroupPanel();

    ImGui::EndTabItem();
}

// Implementasi utama ShowMenu
void UISystem::ShowMenu() {
    if (!State::showMenu) return;

    // Setup window
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x + 650, viewport->WorkPos.y + 20), 
                           ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(650, 680), ImGuiCond_FirstUseEver);

    // State management
    static bool isLogin = false;
    static char userKey[64] = "";
    static std::string loginMsg;
    static float windowScale = 1.0f;
    static bool autoResize = true;
    static bool showHideConfirm = false;
    
    ImGui::GetIO().FontGlobalScale = windowScale;

    // Hide confirmation modal
    HideMenu(showHideConfirm);

    // Window rendering
    ImGui::Begin("Nisaki | V1.0", nullptr, 
                autoResize ? ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None);
    
    if (!isLogin) {
        ImGui::BeginTabBar("AuthTabs");
        RenderLoginTab(userKey, &isLogin, loginMsg);
        ImGui::EndTabBar();
    } else {
        ImGui::BeginTabBar("MainTabs");
        RenderVisualTab();
        RenderHelperTab();
        RenderRoomInfoTab();
        RenderSettingsTab(windowScale, autoResize, showHideConfirm);
        ImGui::EndTabBar();
    }
    
    ImGui::End();
}
