//
// Created by hasbi on 4/9/2023.
//
bool UnlockSkins;
bool GusionSkills;

namespace ESP {
	int MinimapSize = 227; //width & height
	int MinimapPos = 49;
};

Vector2 WorldToMinimap(uint CampType, Vector3 HeroPosition) {
    float angle = (CampType == 2 ? 314.60f : 134.76f) * 0.017453292519943295;
    float angleCos = (float)std::cos(angle);
    float angleSin = (float)std::sin(angle);
    Vector2 Res0;
    Res0.x = (angleCos * HeroPosition.x - angleSin * (HeroPosition.z * -1)) / 74.11f;
    Res0.y = (angleSin * HeroPosition.x + angleCos * (HeroPosition.z * -1)) / 74.11f;
    Vector2 Res1;
    Res1.x = (Res0.x * ESP::MinimapSize) + ESP::MinimapPos + ESP::MinimapSize / 2.f;
    Res1.y = (Res0.y * ESP::MinimapSize) + ESP::MinimapSize / 2.f;
    return Res1;
}


