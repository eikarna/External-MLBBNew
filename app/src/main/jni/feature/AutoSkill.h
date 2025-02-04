int ShowSelfPlayer_TryUseSkillByLockUnit(void *instance, int skillId, Vector3 dir, bool dirDefault, Vector3 pos ) {
    return reinterpret_cast<int (__fastcall *)(void *, int, Vector3, bool, Vector3)>(ShowSelfPlayer_TryUseSkill)(instance, skillId, dir, dirDefault, pos);
}

//Assembly-CSharp.dll -> Class LogicBattleEndCtrl
#define Offsets_LogicBattleEndCtrl_get_logicBattleManager (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("LogicBattleEndCtrl"),OBFUSCATE("get_logicBattleManager"))

//Assembly-CSharp.dll -> Class LogicBattleManager
#define Offsets_LogicBattleManager_GetPlayerRealSelf (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("LogicBattleManager"),OBFUSCATE("GetPlayerRealSelf"))

void *sary_LogicBattleManager(void *instance) {
    return reinterpret_cast<void * (__fastcall *)(void *)>(Offsets_LogicBattleEndCtrl_get_logicBattleManager)(instance);
}

void *sary_GetPlayerRealSelf(void *instance) {
    return reinterpret_cast<void * (__fastcall *)(void *)>(Offsets_LogicBattleManager_GetPlayerRealSelf)(instance);
}

void GusionSkill(){
	if (GusionSkills){
    Auto.Gusion = true;
	Auto.Gusion2 = true;
	}else{
    Auto.Gusion = false;
	Auto.Gusion2 = false;
	}
}
float SpeedAim;
void Auto_Skill(void *instance)
{
	    float MaxDist = std::numeric_limits<float>::infinity();
        float MaxEnemyHP = std::numeric_limits<float>::infinity();
        float MaxPercentHP = std::numeric_limits<float>::infinity();
        float MaxSwordDist = std::numeric_limits<float>::infinity();
		Vector3 EntityPos = Vector3::zero();
		Vector3 SwordPos = Vector3::zero();
	auto logic_BattleManager = sary_LogicBattleManager(instance);
    auto LogicFighter = sary_GetPlayerRealSelf(logic_BattleManager);
          
	auto battleManager = *(uintptr_t *) ((uintptr_t)BattleData_battleManager);
    if (!battleManager) return;
    auto m_LocalPlayerShow = *(uintptr_t *) ((uintptr_t)battleManager + BattleManager_m_LocalPlayerShow);
    if (!m_LocalPlayerShow) return;
	auto selfPos = *(Vector3 *) ((uintptr_t)m_LocalPlayerShow + ShowEntity_Position);
    auto HeroID = *(int *) ((uintptr_t)m_LocalPlayerShow + EntityBase_m_ID);
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
        float PercentHP = m_Hp1 * 100 / m_HpMax1;
		float fDistance1 = Vector3::Distance(selfPos, _Position1);
        int player_level = *(int *)((uintptr_t) instance + EntityBase_m_Level);
        int m_basePhyAtt = *(int *)((uintptr_t) instance + M_BasePhyAtt);
       
		int m_KillWildTimes =  *(int *)((uintptr_t) LogicFighter + LogicPlayer_KillWildTimes);
    
	float MartisS3 = 900.f + m_basePhyAtt;
	float KarinaS3 = 950.f ;
	float ZilongS2 = 850.f;
  
	 if (Auto.Karina){
		  if (_Position1 != Vector3::zero() && fDistance1 <= 2 && PercentHP <= 100){
		ShowSelfPlayer_TryUseSkillByLockUnit(instance, 820, Vector3::Normalized(_Position1 - selfPos), true, selfPos);                        
	   }
	   if (_Position1 != Vector3::zero() && fDistance1 <= 4 && m_Hp1 <= (int) KarinaS3){
		ShowSelfPlayer_TryUseSkillByLockUnit(instance, 830, Vector3::Normalized(_Position1 - selfPos), true, selfPos);                        
	   }
	 }
	 
	if (Auto.Martis){
			if (_Position1 != Vector3::zero() && fDistance1 <= 2.5f && m_Hp1 <= (int) MartisS3){
		ShowSelfPlayer_TryUseSkillByLockUnit(instance, 5830, Vector3::Normalized(_Position1 - selfPos), true, selfPos);                        
	   }
	 } 
	 
	 if (Auto.Zilong){
		  if (_Position1 != Vector3::zero() && fDistance1 <= 2.5f && m_Hp1 <= (int) ZilongS2){
		ShowSelfPlayer_TryUseSkillByLockUnit(instance, 1620, Vector3::Normalized(_Position1 - selfPos), true, selfPos);                        
	   }
	 } 
	 
	 if (fDistance1 < 6.5f){
		 if (m_Hp1 < MaxEnemyHP){
		 EntityPos = _Position1;
         MaxEnemyHP = m_Hp1;
	    }
	 }
	 if (EntityPos != Vector3::zero()){
		auto targetLockPos = Vector3::Normalized(EntityPos - selfPos);
		
		if (Auto.Gusion) {
		ShowSelfPlayer_TryUseSkillByLockUnit(instance, 5620, targetLockPos, true, selfPos);                        
		ShowSelfPlayer_TryUseSkillByLockUnit(instance, 5610, targetLockPos, true, selfPos);                       
	    }
	}
	 if (Auto.Gusion2) {
	 if (_Position1 != Vector3::zero() && fDistance1 < 6.5f){
		ShowSelfPlayer_TryUseSkillByLockUnit(instance, 5630, Vector3::zero(), true, _Position1);             
	    SpeedAim=0;
		}
	}
	   if (Auto.SwordLing){
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
                      if (Distance2 < MaxSwordDist && Auto.SwordLing ) {
                      SwordPos = transform->get_position();
                       MaxSwordDist = Distance2;
                    }
                }
            }
        }
            if (SwordPos != Vector3::zero() && HeroID == 84) {
            ShowSelfPlayer_TryUseSkillByLockUnit(instance, 8420, Vector3::Normalized(SwordPos - selfPos), true, selfPos);                        
			SpeedAim=0;
		   	   }
          }
	 }
}

