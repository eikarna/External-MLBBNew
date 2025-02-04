#pragma once

struct PlayerData {
    std::string Name;
    std::string UserID;
    std::string Verified;
    std::string Rank;
    std::string Star;
    std::string grade;
    int uiRank;
    int HeroID;
    int Spell;
};

struct {
    PlayerData PlayerB[13];
    PlayerData PlayerR[13];
} RoomInfo;

static bool InitializeNick = false;

const char * TextFormat(const char * Str, ...) {
    char buf[1000] = { 0 };
    va_list arg;
    va_start(arg, Str);
    vsprintf(buf, Str, arg);
    va_end(arg);
    return buf;
}

std::string Nick[10];

void * DoThreadGetNickName(void*) {
    List<uintptr_t> *m_RoomPlayerInfo = GetBattlePlayerInfo();
    if (!m_RoomPlayerInfo) nullptr;
    for (int i = 0; i < m_RoomPlayerInfo->getSize(); i++) {
        auto roomData = m_RoomPlayerInfo->getItems()[i];
        if (roomData != NULL) {
            auto lUid = *(int *) ((uintptr_t)roomData + RoomData_lUid);
            auto uiZoneId = *(int *) ((uintptr_t)roomData + RoomData_uiZoneId);
            Nick[i] = GetNickName(TextFormat("%d", lUid), TextFormat("%d", uiZoneId));
        }
    }
    pthread_exit(nullptr);
    return nullptr;
}

void RoomInfoList() {
    auto iBattleState = GetBattleState();
    if (iBattleState == 2 || iBattleState == 3) {
        if (InitializeNick == false) {
            pthread_t thread;
            pthread_create(&thread, NULL, DoThreadGetNickName, NULL);
            InitializeNick = true;
        }
        List<uintptr_t> *m_RoomPlayerInfo = GetBattlePlayerInfo();
        if (!m_RoomPlayerInfo) return;
        int PlayerB = 0, PlayerR = 0, iSelfCamp = -1;
        int m_uiID = *(int *)(SystemData_m_uiID);
        for (int i = 0; i < m_RoomPlayerInfo->getSize(); i++) {
            auto roomData = m_RoomPlayerInfo->getItems()[i];
            if (!roomData) continue;
            auto iCamp = *(int *) ((uintptr_t)roomData + RoomData_iCamp);
            auto lUid = *(int *) ((uintptr_t)roomData + RoomData_lUid);
            if (lUid != m_uiID) continue;
            iSelfCamp = iCamp;
            break;
        }
        for (int i = 0; i < m_RoomPlayerInfo->getSize(); i++) {
            auto roomData = m_RoomPlayerInfo->getItems()[i];
            if (!roomData) continue;
            auto iCamp = *(int *) ((uintptr_t)roomData + RoomData_iCamp);
            auto lUid = *(int *) ((uintptr_t)roomData + RoomData_lUid);
            auto uiZoneId = *(int *) ((uintptr_t)roomData + RoomData_uiZoneId);
            auto heroid = *(int *) ((uintptr_t)roomData + RoomData_heroid);
            auto uiHeroIDChoose = *(int *) ((uintptr_t)roomData + RoomData_uiHeroIDChoose);
            auto summonSkillId = *(int *) ((uintptr_t)roomData + RoomData_summonSkillId);
            auto *_sName = *(String **) ((uintptr_t)roomData + RoomData_sName);
            auto *StrName = *(String **) ((uintptr_t)roomData + RoomData_get_strName);
            auto iCertify = *(int *) ((uintptr_t)roomData + RoomData_iCertify);
            auto uiRankLevel = *(int *) ((uintptr_t)roomData + RoomData_uiRankLevel);
            auto iMythPoint = *(int *) ((uintptr_t)roomData + RoomData_iMythPoint);
            auto splitRank = SplitRankAndStars(uiRankLevel, iMythPoint);
            std::string rankName = std::get<0>(splitRank);
            std::string starCount = std::get<1>(splitRank);
            auto Grade = SplitGrade(uiRankLevel);
            if (iCamp == iSelfCamp) {
                RoomInfo.PlayerB[PlayerB].UserID = to_string(lUid) + " (" + to_string(uiZoneId) + ")";
                RoomInfo.PlayerB[PlayerB].Name = Nick[i].c_str();
                RoomInfo.PlayerB[PlayerB].Rank = rankName;
                RoomInfo.PlayerB[PlayerB].Star = starCount;
                RoomInfo.PlayerB[PlayerB].Verified = VerifiedToString(iCertify);
                RoomInfo.PlayerB[PlayerB].HeroID = (uiHeroIDChoose) ? uiHeroIDChoose : heroid;
                RoomInfo.PlayerB[PlayerB].Spell = summonSkillId;
                RoomInfo.PlayerB[PlayerB].uiRank = uiRankLevel;
                RoomInfo.PlayerB[PlayerB].grade = Grade;
                
                PlayerB++;
            } else {
                RoomInfo.PlayerR[PlayerR].UserID = to_string(lUid) + " (" + to_string(uiZoneId) + ")";
                RoomInfo.PlayerR[PlayerR].Name = Nick[i].c_str();
                RoomInfo.PlayerR[PlayerR].Rank = rankName;
                RoomInfo.PlayerR[PlayerR].Star = starCount;
                RoomInfo.PlayerR[PlayerR].Verified = VerifiedToString(iCertify);
                RoomInfo.PlayerR[PlayerR].HeroID = (uiHeroIDChoose) ? uiHeroIDChoose : heroid;
                RoomInfo.PlayerR[PlayerR].Spell = summonSkillId;
                RoomInfo.PlayerR[PlayerR].uiRank = uiRankLevel;
                RoomInfo.PlayerR[PlayerR].grade = Grade;
                
                PlayerR++;
            }
        }
    } else {
        InitializeNick = false;
        for (int i = 0; i < 10; i++) Nick[i] = "-";
    }
}
