#pragma once

struct sConfig {
    struct sESP {
        struct sPlayer {
            bool Line;
            bool Round;
            bool Name;
            bool Hero;
            bool Health;
        };
        sPlayer Player{0};
        
        struct sMonster {
            bool Round;
            bool Health;
        };
        sMonster Monster{0};
        
        struct sInfo {
            bool SkillCD;
            bool SpellCD;
        };
        sInfo Info{0};
        
        struct sMinimap {
            bool Icon;
            bool Line;
        };
        sMinimap Minimap{0};
    };
    sESP ESP{0};
};
sConfig Config{0};

namespace Minimap {
    ImVec2 StartPos = {(float)105, (float)0};
    int MapSize = 341; //width & height
}
using namespace Minimap;

Vector2 WorldToMinimap(uint CampType, Vector3 HeroPosition) {
    float angle = (CampType == 2 ? 314.60f : 134.76f) * 0.017453292519943295;
    float angleCos = (float)std::cos(angle);
    float angleSin = (float)std::sin(angle);
    Vector2 Res0;
    Res0.x = (angleCos * HeroPosition.x - angleSin * (HeroPosition.z * -1)) / 74.11f;
    Res0.y = (angleSin * HeroPosition.x + angleCos * (HeroPosition.z * -1)) / 74.11f;
    Vector2 Res1;
    Res1.x = (Res0.x * MapSize) + StartPos.x + MapSize / 2.f;
    Res1.y = (Res0.y * MapSize) + StartPos.y + MapSize / 2.f;
    return Res1;
}

static float SetFieldOfView = 0, GetFieldOfView = 0;

void DroneView() {
    if (GetFieldOfView == 0) {
        GetFieldOfView = get_fieldOfView();
    }
    if (SetFieldOfView > 0 && GetFieldOfView != 0) {
        set_fieldOfView((float)GetFieldOfView + SetFieldOfView);
    }
    if (SetFieldOfView == 0 && GetFieldOfView != 0) {
        set_fieldOfView((float)GetFieldOfView);
    }
}

struct CooldownValues {
    int skillCount;
    int skill1;
    int skill2;
    int skill3;
    int skill4;
    int spell;
};

CooldownValues getPlayerCoolDown(int keys, uintptr_t values) {
    auto logicFighter = GetPlayerLogic((uint)keys);
    if (!logicFighter) return {0, 0, 0, 0, 0, 0};
    auto m_SkillComp = *(uintptr_t *) ((uintptr_t)logicFighter + LogicFighter_m_SkillComp);
    if (!m_SkillComp) return {0, 0, 0, 0, 0, 0};
    auto m_CoolDownComp = *(uintptr_t *) ((uintptr_t)m_SkillComp + LogicSkillComp_m_CoolDownComp);
    if (!m_CoolDownComp) return {0, 0, 0, 0, 0, 0};
    auto m_OwnSkillComp = *(uintptr_t *) ((uintptr_t)values + ShowEntity_m_OwnSkillComp);
    if (!m_OwnSkillComp) return {0, 0, 0, 0, 0, 0};
    int skillCount = 0, skill1 = 0, skill2 = 0, skill3 = 0, skill4 = 0, spell = 0;
    Dictionary<int, List<int> *> *skillUseTypeList = *(Dictionary<int, List<int> *> **) ((uintptr_t)m_OwnSkillComp + ShowOwnSkillComp_skillUseTypeList);
    if (!skillUseTypeList) return {0, 0, 0, 0, 0, 0};
    for (int v = 0; v < skillUseTypeList->getNumKeys(); v++) {
        auto keysskillUseType = skillUseTypeList->getKeys()[v];
        auto valuesskillUseType = skillUseTypeList->getValues()[v];
        if (!keysskillUseType) continue;
        if (keysskillUseType != 1) continue;
        skillCount = valuesskillUseType->getSize();
        List<uintptr_t> *m_SkillList = *(List<uintptr_t> **) ((uintptr_t)m_OwnSkillComp + ShowOwnSkillComp_m_SkillList);
        if (!m_SkillList) return {0, 0, 0, 0, 0, 0};
        for (int i = 0; i < 5; i++) {
            auto p_SkillList = m_SkillList->getItems()[i];
            if (!p_SkillList) continue;
            auto m_TranID = *(int *) ((uintptr_t)p_SkillList + ShowSkillData_m_TranID);
            auto m_DicCoolInfo = *(Dictionary<int, uintptr_t> **) ((uintptr_t)m_CoolDownComp + CoolDownComp_m_DicCoolInfo);
            if (!m_DicCoolInfo) continue;
            for (int l = 0; l < m_DicCoolInfo->getNumKeys(); l++) {
                auto keysCool = m_DicCoolInfo->getKeys()[l];
                auto valuesCool = m_DicCoolInfo->getValues()[l];
                if (!keysCool || !valuesCool) continue;
                auto m_iSummonSkillId = *(int *) ((uintptr_t)values + ShowPlayer_m_iSummonSkillId);
                int coolTime = GetCoolTime((void*)valuesCool) / 1000;
                if (keysCool == m_iSummonSkillId) spell = coolTime;
                if ((int)m_TranID != keysCool) continue;
                if (i == 1) skill1 = coolTime;
                if (i == 2) skill2 = coolTime;
                if (i == 3) skill3 = coolTime;
                if (i == 4) skill4 = coolTime;
            }
        }
    }
    return {skillCount, skill1, skill2, skill3, skill4, spell};
}

void drawESP(ImDrawList *draw, float screenWidth, float screenHeight) {
    auto m_BattleBridge = *(uintptr_t *) ((uintptr_t)BattleData_m_BattleBridge);
    if (!m_BattleBridge) return;
    auto bStartBattle = *(bool *) ((uintptr_t)m_BattleBridge + BattleBridge_bStartBattle);
    if (!bStartBattle) return;
    DroneView();
    if (Config.ESP.Minimap.Icon) {
        if (!Config.ESP.Minimap.Line)
            draw->AddRect(ImVec2(StartPos.x, StartPos.y), ImVec2(StartPos.x + MapSize, StartPos.y + MapSize), IM_COL32(255, 255, 255, 255));
    }
    auto battleManager = *(uintptr_t *) ((uintptr_t)BattleData_battleManager);
    if (!battleManager) return;
    /*self*/
    auto m_LocalPlayerShow = *(uintptr_t *) ((uintptr_t)battleManager + BattleManager_m_LocalPlayerShow);
    if (!m_LocalPlayerShow) return;
    auto selfPos = *(Vector3 *) ((uintptr_t)m_LocalPlayerShow + ShowEntity_Position);
    auto selfPosVec2 = getPosVec2(selfPos, screenWidth, screenHeight);
    auto m_dicPlayerShow = *(Dictionary<int, uintptr_t> **) ((uintptr_t)battleManager + BattleManager_m_dicPlayerShow);
    if (!m_dicPlayerShow) return;
    for (int i = 0; i < m_dicPlayerShow->getNumKeys(); i++) {
        auto keys = m_dicPlayerShow->getKeys()[i];
        auto values = m_dicPlayerShow->getValues()[i];
        if (!keys || !values) continue;
        auto m_ID = *(int *) ((uintptr_t)values + ShowEntityBase_m_ID);
        auto m_bDeath = *(bool *) ((uintptr_t)values + ShowEntityBase_m_bDeath);
        if (m_bDeath) continue;
        auto m_bSameCampType = *(bool *) ((uintptr_t)values + ShowEntityBase_m_bSameCampType);
        if (m_bSameCampType) continue;
        auto m_Hp = *(int *) ((uintptr_t)values + ShowEntityBase_m_Hp);
        auto m_HpMax = *(int *) ((uintptr_t)values + ShowEntityBase_m_HpMax);
        auto _Position = *(Vector3 *) ((uintptr_t)values + ShowEntity_Position);
        auto rootPosVec2 = getPosVec2(_Position, screenWidth, screenHeight);
        /*esp*/
        auto bShowEntityLayer = *(bool *) ((uintptr_t)values + ShowEntity_bShowEntityLayer);
        if (Config.ESP.Minimap.Icon && m_ID == 53 && AttachIconDone) {
            auto m_EntityCampType = *(int *) ((uintptr_t)values + ShowEntityBase_m_EntityCampType);
            auto minimapPos = WorldToMinimap(m_EntityCampType, _Position);
            DrawIconHero(ImVec2(minimapPos.x, minimapPos.y), m_ID, m_Hp, m_HpMax);
        } else if (Config.ESP.Minimap.Icon && !bShowEntityLayer && AttachIconDone) {
            auto m_EntityCampType = *(int *) ((uintptr_t)values + ShowEntityBase_m_EntityCampType);
            auto minimapPos = WorldToMinimap(m_EntityCampType, _Position);
            DrawIconHero(ImVec2(minimapPos.x, minimapPos.y), m_ID, m_Hp, m_HpMax);
        }
        if (!bShowEntityLayer) {
            if (Config.ESP.Player.Line) {
                draw->AddLine(selfPosVec2, rootPosVec2, IM_COL32(230, 230, 250, 255));
            }
            auto *m_RoleName = *(String **) ((uintptr_t)values + ShowEntity_m_RoleName);
            if (Config.ESP.Player.Name && m_RoleName) {
                std::string strName = m_RoleName->toString();
                auto textSize = ImGui::CalcTextSize(strName.c_str(), 0, 30);
                draw->AddText(NULL, 30, {rootPosVec2.x - (textSize.x / 2), rootPosVec2.y + 40}, IM_COL32(255, 255, 255, 255), strName.c_str());
            }
            if (Config.ESP.Player.Health) {
                auto LineHealthStart = ImVec2(rootPosVec2.x + 40, rootPosVec2.y - 30);
                auto LineHealthEnd = ImVec2(LineHealthStart.x + 160, LineHealthStart.y);
                auto HealthStart = ImVec2(LineHealthStart.x, LineHealthStart.y - 20);
                auto HealthEnd = ImVec2(LineHealthEnd.x, LineHealthEnd.y - 5);
                float healthWidth = abs(HealthEnd.x - HealthStart.x);
                float PercentHP = ((float)m_Hp * healthWidth) / (float)m_HpMax;
                draw->AddLine(rootPosVec2, LineHealthStart, IM_COL32(255, 255, 255, 255));
                draw->AddLine(LineHealthStart, LineHealthEnd, IM_COL32(255, 255, 255, 155));
                draw->AddRectFilled(HealthStart, ImVec2(HealthStart.x + PercentHP, HealthEnd.y), IM_COL32(225, 0, 0, 255), 10);
                draw->AddRect(HealthStart, HealthEnd, IM_COL32(0, 0, 0, 255), 10);
            }
        }
        if (Config.ESP.Player.Round) {
            draw->AddCircleFilled(rootPosVec2, 10, IM_COL32(255, 255, 255, 255));
        }
        if (Config.ESP.Info.SkillCD || Config.ESP.Info.SpellCD) {
            auto coolDownData = getPlayerCoolDown(keys, values);
            if (Config.ESP.Info.SkillCD) {
                if (coolDownData.skill1) {
                    std::string strCoolDown = to_string(coolDownData.skill1);
                    auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                    draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(255, 255, 0, 255), strCoolDown.c_str());
                } else {
                    draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55, rootPosVec2.y - 15), 10, IM_COL32(255, 255, 0, 255));
                }
                if (coolDownData.skill2) {
                    std::string strCoolDown = to_string(coolDownData.skill2);
                    auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                    draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + (40 * 1) - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(255, 255, 0, 255), strCoolDown.c_str());
                } else {
                    draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + (40 * 1), rootPosVec2.y - 15), 10, IM_COL32(255, 255, 0, 255));
                }
                if (coolDownData.skill3) {
                    std::string strCoolDown = to_string(coolDownData.skill3);
                    auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                    draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + (40 * 2) - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(255, 255, 0, 255), strCoolDown.c_str());
                } else {
                    draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + (40 * 2), rootPosVec2.y - 15), 10, IM_COL32(255, 255, 0, 255));
                }
            }
            if (coolDownData.skillCount >= 4) {
                if (Config.ESP.Info.SkillCD && Config.ESP.Info.SpellCD) {
                    if (coolDownData.skill4) {
                        std::string strCoolDown = to_string(coolDownData.skill4);
                        auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + (40 * 3) - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(255, 255, 0, 255), strCoolDown.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + (40 * 3), rootPosVec2.y - 15), 10, IM_COL32(255, 255, 0, 255));
                    }
                    if (coolDownData.spell) {
                        std::string strCoolDown = to_string(coolDownData.spell);
                        auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + (40 * 4) - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(30, 144, 255, 255), strCoolDown.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + (40 * 4), rootPosVec2.y - 15), 10, IM_COL32(30, 144, 255, 255));
                    }
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 225, rootPosVec2.y), IM_COL32(255, 255, 255, 255));
                } else if (Config.ESP.Info.SkillCD) {
                    if (coolDownData.skill4) {
                        std::string strCoolDown = to_string(coolDownData.skill4);
                        auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + (40 * 3) - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(255, 255, 0, 255), strCoolDown.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + (40 * 3), rootPosVec2.y - 15), 10, IM_COL32(255, 255, 0, 255));
                    }
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 185, rootPosVec2.y), IM_COL32(255, 255, 255, 255));
                } else if (Config.ESP.Info.SpellCD) {
                    if (coolDownData.spell) {
                        std::string strCoolDown = to_string(coolDownData.spell);
                        auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(30, 144, 255, 255), strCoolDown.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55, rootPosVec2.y - 15), 10, IM_COL32(30, 144, 255, 255));
                    }
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 65, rootPosVec2.y), IM_COL32(255, 255, 255, 255));
                }
            } else if (coolDownData.skillCount == 3) {
                if (Config.ESP.Info.SkillCD && Config.ESP.Info.SpellCD) {
                    if (coolDownData.spell) {
                        std::string strCoolDown = to_string(coolDownData.spell);
                        auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 + (40 * 3) - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(30, 144, 255, 255), strCoolDown.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55 + (40 * 3), rootPosVec2.y - 15), 10, IM_COL32(30, 144, 255, 255));
                    }
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 185, rootPosVec2.y), IM_COL32(255, 255, 255, 255));
                } else if (Config.ESP.Info.SkillCD) {
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 145, rootPosVec2.y), IM_COL32(255, 255, 255, 255));
                } else if (Config.ESP.Info.SpellCD) {
                    if (coolDownData.spell) {
                        std::string strCoolDown = to_string(coolDownData.spell);
                        auto textSize = ImGui::CalcTextSize(strCoolDown.c_str(), 0, 30);
                        draw->AddText(NULL, 30, ImVec2(rootPosVec2.x + 55 - (textSize.x / 2), rootPosVec2.y - 30), IM_COL32(30, 144, 255, 255), strCoolDown.c_str());
                    } else {
                        draw->AddCircleFilled(ImVec2(rootPosVec2.x + 55, rootPosVec2.y - 15), 10, IM_COL32(30, 144, 255, 255));
                    }
                    draw->AddLine(rootPosVec2, ImVec2(rootPosVec2.x + 65, rootPosVec2.y), IM_COL32(255, 255, 255, 255));
                }
            }
        }
        if (Config.ESP.Player.Hero) {
            DrawHero(rootPosVec2, m_ID, m_Hp, m_HpMax);
        }
    }
    /*monster*/
    auto m_dicMonsterShow = *(Dictionary<int, uintptr_t> **) ((uintptr_t)battleManager + BattleManager_m_dicMonsterShow);
    if (!m_dicMonsterShow) return;
    for (int i = 0; i < m_dicMonsterShow->getNumKeys(); i++) {
        auto keys = m_dicMonsterShow->getKeys()[i];
        auto values = m_dicMonsterShow->getValues()[i];
        if (!keys || !values) continue;
        auto m_ID = *(int *) ((uintptr_t)values + ShowEntityBase_m_ID);
        if (!bMonster(m_ID)) continue;
        auto m_bDeath = *(bool *) ((uintptr_t)values + ShowEntityBase_m_bDeath);
        if (m_bDeath) continue;
        auto m_bSameCampType = *(bool *) ((uintptr_t)values + ShowEntityBase_m_bSameCampType);
        if (m_bSameCampType) continue;
        auto bShowEntityLayer = *(bool *) ((uintptr_t)values + ShowEntity_bShowEntityLayer);
        auto m_Hp = *(int *) ((uintptr_t)values + ShowEntityBase_m_Hp);
        auto m_HpMax = *(int *) ((uintptr_t)values + ShowEntityBase_m_HpMax);
        if (bShowEntityLayer && m_Hp != m_HpMax) continue;
        auto _Position = *(Vector3 *) ((uintptr_t)values + ShowEntity_Position);
        auto rootPosVec2 = getPosVec2(_Position, screenWidth, screenHeight);
        float fDistance = Vector3::Distance(selfPos, _Position);
        if (Config.ESP.Monster.Round) {
            draw->AddCircleFilled(rootPosVec2, 10, IM_COL32(255, 255, 255, 255));
        }
        if (Config.ESP.Monster.Health) {
            auto LineHealthStart = ImVec2(rootPosVec2.x + 40, rootPosVec2.y - 30);
            auto LineHealthEnd = ImVec2(LineHealthStart.x + 160, LineHealthStart.y);
            auto HealthStart = ImVec2(LineHealthStart.x, LineHealthStart.y - 20);
            auto HealthEnd = ImVec2(LineHealthEnd.x, LineHealthEnd.y - 5);
            float healthWidth = abs(HealthEnd.x - HealthStart.x);
            float PercentHP = ((float)m_Hp * healthWidth) / (float)m_HpMax;
            draw->AddLine(rootPosVec2, LineHealthStart, IM_COL32(255, 255, 255, 255));
            draw->AddLine(LineHealthStart, LineHealthEnd, IM_COL32(255, 255, 255, 155));
            draw->AddRectFilled(HealthStart, ImVec2(HealthStart.x + PercentHP, HealthEnd.y), IM_COL32(225, 0, 0, 255), 10);
            draw->AddRect(HealthStart, HealthEnd, IM_COL32(0, 0, 0, 255), 10);
            std::string strHealth = to_string(m_Hp);
            auto textSize = ImGui::CalcTextSize(strHealth.c_str(), 0, 20);
            draw->AddText(NULL, 20, {HealthEnd.x - (textSize.x / 2), HealthStart.y - 20}, IM_COL32(255, 255, 255, 255), strHealth.c_str());
        }
    }
}

