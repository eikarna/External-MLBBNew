#include "Menu.h"

void Auto_Retri(void *instance)
{
	auto battleManager = *(uintptr_t *) ((uintptr_t)BattleData_battleManager);
    if (!battleManager) return;
    
	auto logic_BattleManager = sary_LogicBattleManager(instance);
    auto LogicFighter = sary_GetPlayerRealSelf(logic_BattleManager);
             
	auto m_LocalPlayerShow = *(uintptr_t *) ((uintptr_t)battleManager + BattleManager_m_LocalPlayerShow);
    if (!m_LocalPlayerShow) return;
	auto selfPos = *(Vector3 *) ((uintptr_t)m_LocalPlayerShow + ShowEntity_Position);
    auto m_dicPlayerShow = *(Dictionary<int, uintptr_t> **) ((uintptr_t)battleManager + BattleManager_m_dicPlayerShow);
    if (!m_dicPlayerShow) return;
    for (int u = 0; u < m_dicPlayerShow->getNumKeys(); u++) {
        auto keys1 = m_dicPlayerShow->getKeys()[u];
        auto values1 = m_dicPlayerShow->getValues()[u];
        if (!keys1 || !values1) continue;
        auto m_ID = *(int *) ((uintptr_t)values1 + EntityBase_m_ID);
        auto m_bDeath = *(bool *) ((uintptr_t)values1 + EntityBase_m_bDeath);
        if (m_bDeath) continue;
        auto m_bSameCampType = *(bool *) ((uintptr_t)values1 + EntityBase_m_bSameCampType);
        if (m_bSameCampType) continue;
        auto m_Hp1 = *(int *) ((uintptr_t)values1 + EntityBase_m_Hp);
        auto m_HpMax1 = *(int *) ((uintptr_t)values1 + EntityBase_m_HpMax);
        auto _Position1 = *(Vector3 *) ((uintptr_t)values1 + ShowEntity_Position);
      float fDistance1 = Vector3::Distance(selfPos, _Position1);
      
    auto m_dicMonsterShow = *(Dictionary<int, uintptr_t> **) ((uintptr_t)battleManager + BattleManager_m_dicMonsterShow);
    if (!m_dicMonsterShow) return;
    for (int i = 0; i < m_dicMonsterShow->getNumKeys(); i++) {
        auto keys = m_dicMonsterShow->getKeys()[i];
        auto values = m_dicMonsterShow->getValues()[i];
        if (!keys || !values) continue;
        auto m_ID = *(int *) ((uintptr_t)values + EntityBase_m_ID);
        if (!bMonster(m_ID)) continue;
        auto m_bDeath = *(bool *) ((uintptr_t)values + EntityBase_m_bDeath);
        if (m_bDeath) continue;
        auto m_bSameCampType = *(bool *) ((uintptr_t)values + EntityBase_m_bSameCampType);
        if (m_bSameCampType) continue;
	auto m_Hp = *(int *) ((uintptr_t)values + EntityBase_m_Hp);
    auto m_HpMax = *(int *) ((uintptr_t)values + EntityBase_m_HpMax);
    auto _Position = *(Vector3 *) ((uintptr_t)values + ShowEntity_Position);
    float fDistance = Vector3::Distance(selfPos, _Position);
    int player_level = *(int *)((uintptr_t) instance + EntityBase_m_Level);
    int m_KillWildTimes =  *(int *)((uintptr_t) LogicFighter + LogicPlayer_KillWildTimes);
    float retriDamage = 520.f + (80.f * (float) player_level);
         if (m_KillWildTimes >= 5) {
          retriDamage = retriDamage * 1.5f;
          }
		  
	auto dicTalentSkill = *(Dictionari< int, int *> **)((uintptr_t)LogicFighter + LogicPlayer_dicTalentSkill);
       if (dicTalentSkill) {
          auto keys2 = dicTalentSkill->getKeys();
          auto values2 = dicTalentSkill->getValues();
          for (int j = 0; j < dicTalentSkill->getSize(); j++) {
          int sary_key = keys2[j];
          int sary_value =*(int *) values2[j];
	if (sary_key == 402) {
       retriDamage += (int)((float)retriDamage * (0.07f * sary_value));
            }
      if (State::AutoRetribution.Lord|| State::AutoRetribution.Turtle) {
       if (sary_key == 409) {
           retriDamage += (int)((float)retriDamage * 0.20f);
              }
		    }
		}
	}
  if ( m_ID == 2002 && State::AutoRetribution.Lord || m_ID == 2003 && State::AutoRetribution.Turtle ) {                              
          if (m_Hp <= (int) retriDamage && fDistance <= 5.4) {              	
                  ShowSelfPlayer_TryUseSkillByLockUnit(instance, 20020, Vector3::Normalized(_Position - selfPos), true, selfPos);                        
				}
			}
	if (m_ID == 2013  && State::AutoRetribution.Creep || m_ID == 2011  && State::AutoRetribution.Creep || m_ID == 2056  && State::AutoRetribution.Litho||m_ID == 2004 && State::AutoRetribution.Buff || m_ID == 2005 && State::AutoRetribution.Buff || m_ID == 2002 && State::AutoRetribution.Lord || m_ID == 2003 && State::AutoRetribution.Turtle ) {                              
          if (m_Hp <= (int) retriDamage && fDistance <= 5.4 && fDistance1 <= 8) {           	
                  ShowSelfPlayer_TryUseSkillByLockUnit(instance, 20020, Vector3::Normalized(_Position - selfPos), true, selfPos);                        
			}
		  }
		}
	 }
  }

void (*oShowSelfPlayerOnUpdate)(void * instance);
void ShowSelfPlayerOnUpdate(void* instance) {
	if (instance != NULL){
	Auto_Retri(instance);
	if (State::Auto.SwordLing || State::Auto.Gusion2){
    SpeedAim++;
	if(SpeedAim > 30){
	Auto_Skill(instance);
        }
	}
	if (State::Auto.Karina || State::Auto.Gusion || State::Auto.Martis || State::Auto.Zilong){
	Auto_Skill(instance);
	  }
	}
    return oShowSelfPlayerOnUpdate(instance);
}



