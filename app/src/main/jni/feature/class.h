#pragma once

//Class Screen
#define Screen_get_width (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("get_width"))
#define Screen_get_height (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("get_height"))
#define Screen_SetResolution (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("SetResolution"), 3)

class Screen {
    public:
    static void SetResolution(int width, int height, bool fullscreen) {
        auto _ = reinterpret_cast<void(*)(int ,int ,bool ) > ((uintptr_t)Screen_SetResolution);
        return _(width,height,fullscreen);
    }
    static int get_width() {
        auto _ = reinterpret_cast<int(*)()>((uintptr_t)Screen_get_width);
        return _();
    }
    static int get_height() {
        auto _ = reinterpret_cast<int(*)()>((uintptr_t)Screen_get_height);
        return _();
    }
};

//Class Camera
#define Camera_get_main (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("get_main"))
#define Camera_WorldToScreenPoint (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("WorldToScreenPoint"), 1)
#define Camera_get_fieldOfView (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("get_fieldOfView"))
#define Camera_set_fieldOfView (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("set_fieldOfView"), 1)

void *get_main() {
    return reinterpret_cast<void *(__fastcall *)()>(Camera_get_main)();
}

Vector3 WorldToScreen(Vector3 position) {
    return reinterpret_cast<Vector3(__fastcall *)(void *, Vector3)>(Camera_WorldToScreenPoint)(get_main(), position);
}

float get_fieldOfView() {
    return reinterpret_cast<float(__fastcall *)(void *)>(Camera_get_fieldOfView)(get_main());
}

void *set_fieldOfView(float value) {
    return reinterpret_cast<void *(__fastcall *)(void *, float)>(Camera_set_fieldOfView)(get_main(), value);
}

ImVec2 getPosVec2(Vector3 _Position, int screenWidth, int screenHeight) {
    auto RootPosW2S = WorldToScreen(_Position);
    if (RootPosW2S.z > 0) {
        return ImVec2(RootPosW2S.x, screenHeight - RootPosW2S.y);
    }
    return ImVec2(screenWidth - RootPosW2S.x, RootPosW2S.y);
}

#define ShowSelfPlayer_TryUseSkill (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowSelfPlayer"), OBFUSCATE("TryUseSkill"), 9)
#define ShowSelfPlayer_OnUpdate (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowSelfPlayer"), OBFUSCATE("OnUpdate"))

//field
uintptr_t BattleData_m_BattleBridge, BattleData_battleManager;
void loadBattleData() {
	BattleData_m_BattleBridge = (uintptr_t) Il2CppGetStaticFieldOffset("Assembly-CSharp.dll", "", "BattleData", OBFUSCATE("m_BattleBridge"));
	BattleData_battleManager = (uintptr_t) Il2CppGetStaticFieldOffset("Assembly-CSharp.dll", "", "BattleData", OBFUSCATE("battleManager"));
}

#define LogicBattleManager_Instance (uintptr_t) Il2CppGetStaticFieldOffset("Assembly-CSharp.dll", "", "LogicBattleManager", "Instance")


#define BattleBridge_bStartBattle (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "BattleBridge", "bStartBattle")

#define BattleManager_m_LocalPlayerShow (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "BattleManager", "m_LocalPlayerShow")
#define BattleManager_m_dicMonsterShow (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "BattleManager", "m_dicMonsterShow")
#define BattleManager_m_dicPlayerShow (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "BattleManager", "m_dicPlayerShow")
#define LogicPlayer_KillWildTimes (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("LogicPlayer"), OBFUSCATE("_KillWildTimes"))

#define ShowEntity_Position (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", "_Position")
#define ShowEntity_bShowEntityLayer (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", "bShowEntityLayer")
#define ShowEntity_m_RoleName (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", "m_RoleName")
#define EntityBase_m_ID (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "ShowEntityBase", OBFUSCATE("m_ID"))
#define EntityBase_m_Level (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "ShowEntityBase", OBFUSCATE("m_Level"))
#define EntityBase_m_bDeath (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "ShowEntityBase", OBFUSCATE("<m_bDeath>k__BackingField"))
#define EntityBase_m_bSameCampType (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "ShowEntityBase", OBFUSCATE("m_bSameCampType"))
#define EntityBase_m_Hp (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "ShowEntityBase", OBFUSCATE("m_Hp"))
#define EntityBase_m_HpMax (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "ShowEntityBase", OBFUSCATE("m_HpMax"))
#define EntityBase_m_EntityCampType (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "ShowEntityBase", OBFUSCATE("m_EntityCampType"))

#define Transform_get_position (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_position"))
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

class Transform {
public:
    Vector3 get_position() {
        auto get_position = (Vector3 (*)(Transform *)) (Transform_get_position);
        return get_position(this);
    }
};
//Class Bullet
#define Bullet_m_Id (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("Bullet"), OBFUSCATE("m_Id"))
#define Bullet_m_Target (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("Bullet"), OBFUSCATE("m_Target"))
#define Bullet_transform (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("Bullet"), OBFUSCATE("transform"))


#define ShowEntityBase_m_ID (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "ShowEntityBase", "m_ID")
#define ShowEntityBase_m_bDeath (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "ShowEntityBase", "<m_bDeath>k__BackingField")
#define ShowEntityBase_m_bSameCampType (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "ShowEntityBase", "m_bSameCampType")
#define ShowEntityBase_m_Hp (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "ShowEntityBase", "m_Hp")
#define ShowEntityBase_m_HpMax (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "ShowEntityBase", "m_HpMax")
#define ShowEntityBase_m_EntityCampType (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "ShowEntityBase", "m_EntityCampType")
#define ShowEntityBase_m_HpPer (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "ShowEntityBase", "m_HpPer")

int ListMonsterId[] = {
    2002,
    2003,
    2004,
    2005,
    2006,
    2008,
    2009,
    2011,
    2012,
    2013,
    2056,
    2059,
    2072,
};

bool bMonster(int iValue) {
    return std::find(std::begin(ListMonsterId), std::end(ListMonsterId), iValue) != std::end(ListMonsterId);
}

//Class RoomData
#define RoomData_iCamp (uintptr_t) Il2CppGetStaticFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("SystemData/RoomData"), OBFUSCATE("iCamp"))
#define RoomData_lUid (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("SystemData/RoomData"), OBFUSCATE("lUid"))
#define RoomData_uiZoneId (uintptr_t) Il2CppGetStaticFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("SystemData/RoomData"), OBFUSCATE("uiZoneId"))
#define RoomData_heroid (uintptr_t) Il2CppGetStaticFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("SystemData/RoomData"), OBFUSCATE("heroid"))
#define RoomData_uiHeroIDChoose (uintptr_t) Il2CppGetStaticFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("SystemData/RoomData"), OBFUSCATE("uiHeroIDChoose"))
#define RoomData_summonSkillId (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("SystemData/RoomData"), OBFUSCATE("summonSkillId"))
#define RoomData_sName (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("SystemData/RoomData"), OBFUSCATE("_sName"))
#define RoomData_get_strName (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("SystemData/RoomData"), OBFUSCATE("get_strName"))
#define RoomData_iCertify (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("SystemData/RoomData"), OBFUSCATE("iCertify"))
#define RoomData_uiRankLevel (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("SystemData/RoomData"), OBFUSCATE("uiRankLevel"))
#define RoomData_iMythPoint (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("SystemData/RoomData"), OBFUSCATE("iMythPoint"))

//Class BattleData
#define BattleData_m_BattleBridge (uintptr_t) Il2CppGetStaticFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("BattleData"), OBFUSCATE("m_BattleBridge"))
#define BattleData_battleManager (uintptr_t) Il2CppGetStaticFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("BattleData"), OBFUSCATE("battleManager"))

//Class BattleBridge
#define BattleBridge_bStartBattle (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("BattleBridge"), OBFUSCATE("bStartBattle"))

//Class BattleManager
#define BattleManager_m_LocalPlayerShow (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("BattleManager"), OBFUSCATE("m_LocalPlayerShow"))
#define BattleManager_m_dicPlayerShow (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("BattleManager"), OBFUSCATE("m_dicPlayerShow"))
#define BattleManager_m_dicMonsterShow (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("BattleManager"), OBFUSCATE("m_dicMonsterShow"))

//Class ShowEntity
#define ShowEntity_Position (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowEntity"), OBFUSCATE("_Position"))
#define ShowEntity_bShowEntityLayer (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowEntity"), OBFUSCATE("bShowEntityLayer"))
#define ShowEntity_m_OwnSkillComp (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowEntity"), OBFUSCATE("m_OwnSkillComp"))
#define ShowEntity_m_RoleName (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowEntity"), OBFUSCATE("m_RoleName"))

//Class ShowEntityBase
#define ShowEntityBase_m_bSameCampType (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("ShowEntityBase"), OBFUSCATE("m_bSameCampType"))
#define ShowEntityBase_m_EntityCampType (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("ShowEntityBase"), OBFUSCATE("m_EntityCampType"))
#define ShowEntityBase_m_IsDeathProgress (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("ShowEntityBase"), OBFUSCATE("m_IsDeathProgress"))
#define ShowEntityBase_m_bDeath (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("ShowEntityBase"), OBFUSCATE("<m_bDeath>k__BackingField"))
#define ShowEntityBase_m_Hp (uintptr_t)  Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("ShowEntityBase"), OBFUSCATE("m_Hp"))
#define ShowEntityBase_m_HpMax (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("ShowEntityBase"), OBFUSCATE("m_HpMax"))
#define ShowEntityBase_m_ID (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("ShowEntityBase"), OBFUSCATE("m_ID"))
#define ShowEntityBase_m_uGuid (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("ShowEntityBase"), OBFUSCATE("m_uGuid"))
#define ShowEntityBase_m_Level (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("ShowEntityBase"), OBFUSCATE("m_Level"))

//Class LogicFighter
#define LogicFighter_m_SkillComp (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("LogicFighter"), OBFUSCATE("m_SkillComp"))

//Class LogicSkillComp
#define LogicSkillComp_m_CoolDownComp (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("LogicSkillComp"), OBFUSCATE("m_CoolDownComp"))

//Class CoolDownComp
#define CoolDownComp_m_DicCoolInfo (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("CoolDownComp"), OBFUSCATE("m_DicCoolInfo"))

//Class CoolDownData
#define CoolDownData_GetCoolTime (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("CoolDownData"), OBFUSCATE("GetCoolTime"))
int GetCoolTime(void* instance) {
    return reinterpret_cast<int(__fastcall *)(void *)>(CoolDownData_GetCoolTime)(instance);
}

//Class ShowSkillData
#define ShowSkillData_m_TranID (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowSkillData"), OBFUSCATE("m_TranID"))
#define ShowSkillData_m_InitSkillID (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowSkillData"), OBFUSCATE("m_InitSkillID"))

//Class ShowPlayer
#define ShowPlayer_m_iSummonSkillId (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowPlayer"), OBFUSCATE("m_iSummonSkillId"))
#define ShowPlayer_m_HeroName (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowPlayer"), OBFUSCATE("m_HeroName"))
#define ShowPlayer_m_killNum (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowPlayer"), OBFUSCATE("m_killNum"))
#define ShowPlayer_m_assistNum (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowPlayer"), OBFUSCATE("m_assistNum"))
#define ShowPlayer_m_KillWildTimes (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowPlayer"), OBFUSCATE("m_KillWildTimes"))

//Class ShowOwnSkillComp
#define ShowOwnSkillComp_m_SkillList (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("ShowOwnSkillComp"), OBFUSCATE("m_SkillList"))
#define ShowOwnSkillComp_skillUseTypeList (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("ShowOwnSkillComp"), OBFUSCATE("skillUseTypeList"))

//Class LogicBattleManager
#define LogicBattleManager_Instance (uintptr_t) Il2CppGetStaticFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("LogicBattleManager"), OBFUSCATE("Instance"))
#define LogicBattleManager_GetPlayerLogic (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("LogicBattleManager"), OBFUSCATE("GetPlayerLogic"), 1)
#define LogicBattleManager_GetBattleState (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("LogicBattleManager"), OBFUSCATE("GetBattleState"))
#define LogicBattleManager_GetPlayerRealSelf (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("LogicBattleManager"), OBFUSCATE("GetPlayerRealSelf"))

uintptr_t GetPlayerLogic(uint id) {
    auto instance = *(uintptr_t *) ((uintptr_t)LogicBattleManager_Instance);
    if (!instance) return 0;
    return reinterpret_cast<uintptr_t(__fastcall *)(void *, uint)>(LogicBattleManager_GetPlayerLogic)((void *)instance, id);
}

int GetBattleState() {
    auto instance = *(uintptr_t *) ((uintptr_t)LogicBattleManager_Instance);
    if (!instance) return 0;
    return reinterpret_cast<int(__fastcall *)(void*)>(LogicBattleManager_GetBattleState)((void*)instance);
}

uintptr_t GetPlayerRealSelf() {
    auto instance = *(uintptr_t *) ((uintptr_t)LogicBattleManager_Instance);
    if (instance == NULL) return 0;
    return reinterpret_cast<uintptr_t(__fastcall *)(void *)>(LogicBattleManager_GetPlayerRealSelf)((void *)instance);
}

