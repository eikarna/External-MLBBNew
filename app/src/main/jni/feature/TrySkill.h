

void (*orig_TryUseSkill)(...);
void TryUseSkill(void*instance,int skillId, Vector3 dir, bool dirDefault, Vector3 pos, bool bCommonAttack, bool bAlong, bool isInFirstDragRange) {
	bool isDoneAim = false;
     if (instance != NULL) {
        float MaxDist = std::numeric_limits<float>::infinity();
        float MaxEnemyHP = std::numeric_limits<float>::infinity();
        float MaxPercentHP = std::numeric_limits<float>::infinity();
        float MaxSwordDist = std::numeric_limits<float>::infinity();
        auto logic_BattleManager = sary_LogicBattleManager(instance);
    auto LogicFighter = sary_GetPlayerRealSelf(logic_BattleManager);
      
		Vector3 EntityPos = Vector3::zero();
		Vector3 SwordPos = Vector3::zero();
	auto battleManager = *(uintptr_t *) ((uintptr_t)BattleData_battleManager);
    if (!battleManager) return;
    /*self*/
	auto m_LocalPlayerShow = *(uintptr_t *) ((uintptr_t)battleManager + BattleManager_m_LocalPlayerShow);
    if (!m_LocalPlayerShow) return;
	auto selfPos = *(Vector3 *) ((uintptr_t)m_LocalPlayerShow + ShowEntity_Position);
    auto HeroID = *(int *) ((uintptr_t)m_LocalPlayerShow + EntityBase_m_ID);
	/*player*/
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
        auto CurHP = *(int *) ((uintptr_t)values1 + EntityBase_m_Hp);
        auto MaxHP = *(int *) ((uintptr_t)values1 + EntityBase_m_HpMax);
        float PercentHP = CurHP * 100 / MaxHP;
		auto _Position = *(Vector3 *) ((uintptr_t)values1 + ShowEntity_Position);
       float Distance = Vector3::Distance(selfPos, _Position);
     
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
    auto _Position1 = *(Vector3 *) ((uintptr_t)values + ShowEntity_Position);
    float fDistance = Vector3::Distance(selfPos, _Position1);
    int player_level = *(int *)((uintptr_t) instance + EntityBase_m_Level);
 /*
	int m_KillWildTimes =  *(int *)((uintptr_t) LogicFighter + LogicPlayer_KillWildTimes);
    float retriDamage = 523.f + (80.f * (float) player_level);
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
      if (AutoRetribution.Lord|| AutoRetribution.Turtle) {
       if (sary_key == 409) {
           retriDamage += (int)((float)retriDamage * 0.20f);
              }
		    }
		}
	}
	if ( m_ID == 2002 && AutoRetribution.Lord || m_ID == 2003 && AutoRetribution.Turtle ) {                              
          if (m_Hp <= (int) retriDamage && fDistance <= 5.4) {              	
               orig_TryUseSkill(instance, 20020, Vector3::Normalized(_Position1 - selfPos), dirDefault, pos, bCommonAttack, bAlong, false);
                    }
			}
	if (m_ID == 2013  && AutoRetribution.Creep || m_ID == 2011  && AutoRetribution.Creep || m_ID == 2056  && AutoRetribution.Litho||m_ID == 2004 && AutoRetribution.Buff || m_ID == 2005 && AutoRetribution.Buff  ) {                              
          if (m_Hp <= (int) retriDamage && fDistance <= 5.4 && Distance <= 8) {           	
              orig_TryUseSkill(instance, 20020, Vector3::Normalized(_Position1 - selfPos), dirDefault, pos, bCommonAttack, bAlong, false);
                  }
		  }*/
		}
	   if (Distance < RangeFOV) {
                                if (Aim.Target == 0 && Distance < MaxDist) {
                                    EntityPos = _Position;
                                    MaxDist = Distance;
                                }
                                if (Aim.Target == 1 && CurHP < MaxEnemyHP) {
                                    EntityPos = _Position;
                                    MaxEnemyHP = CurHP;
                                }
                                if (Aim.Target == 2 && PercentHP < MaxPercentHP) {
                                    EntityPos = _Position;
                                    MaxPercentHP = PercentHP;
                                }
							}
						}
		List<void **> *_RunBullets;
                    Il2CppGetStaticFieldValue("Assembly-CSharp.dll", "", "BattleManager", "_RunBullets", &_RunBullets);
                     if (_RunBullets) {
                        for (int i = 0; i < _RunBullets->getSize(); i++) {
                            auto Pawn = _RunBullets->getItems()[i];
                            if (!Pawn) continue;
                            auto m_ID = *(int *) ((uintptr_t)Pawn + Bullet_m_Id);
                            if (m_ID != 8452) continue; 
                            auto transform = *(Transform **) ((uintptr_t)Pawn + Bullet_transform);
			
                            float Distance2 = (int) Vector3::Distance2(selfPos, transform->get_position());
                      if (Distance2 < 5) {
                            if (Distance2 < MaxSwordDist && Aim.AutoTakeSword ) {
                                    SwordPos = transform->get_position();
                                    MaxSwordDist = Distance2;
                                }
                            }
                        }
                    }
            if (SwordPos != Vector3::zero() && HeroID == 84) {
                        auto targetLockPos1 = Vector3::Normalized(SwordPos - selfPos);
                        if (skillId == 100 * HeroID + 20) {
                            isDoneAim = true;
							orig_TryUseSkill(instance, skillId, targetLockPos1, dirDefault, pos, bCommonAttack, bAlong, false);
                        }
                    }  

	  else if (EntityPos != Vector3::zero()) {
	   auto LockPos = EntityPos;
		auto targetLockPos = Vector3::Normalized(EntityPos - selfPos);
		  
                     //Basic
                        if (Aim.Basic) {
                            if (skillId == 100 * HeroID + 00) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, pos, bCommonAttack, bAlong, false);
                            }
                        }
                        //Spell
                      
                        //Skill 1
                        if (Aim.Skill1) {
                            if (skillId == 100 * HeroID + 10) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, LockPos, bCommonAttack, bAlong, false);
                           }
                        }
					  //Skill 2
                        if (Aim.Skill2) {
                            if (skillId == 100 * HeroID + 20 || skillId == 2010520 /*Beatrix Skill2*/) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, LockPos, bCommonAttack, bAlong, false);
                           }
                        }
                        //Skill 3
                        if (Aim.Skill3) {
                            if (skillId == 100 * HeroID + 30 || skillId == 2010530 /*Beatrix Ulti*/) {
                                isDoneAim = true;
                             orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, LockPos, bCommonAttack, bAlong, false);                        
                          
							 }
                        }
                        //Skill 4
                        if (Aim.Skill4) {
                            if (skillId == 100 * HeroID + 40) {
                                isDoneAim = true;
                                orig_TryUseSkill(instance, skillId, targetLockPos, dirDefault, pos, bCommonAttack, bAlong, false);                                  
                    }

                }
            }
        }
    
    if (!isDoneAim) {
        orig_TryUseSkill(instance, skillId, dir, dirDefault, pos, bCommonAttack, bAlong, isInFirstDragRange);
    }
}

