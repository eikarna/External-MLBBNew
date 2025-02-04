#pragma once

#include <curl/curl.h>

using json = nlohmann::ordered_json;

std::string strRank[] = {
        "Warrior - III * 1",
        "Warrior - III * 2",
        "Warrior - III * 3",
        "Warrior - II * 0",
        "Warrior - II * 1",
        "Warrior - II * 2",
        "Warrior - II * 3",
        "Warrior - I * 0",
        "Warrior - I * 1",
        "Warrior - I * 2",
        "Warrior - I * 3",
        "Elite - III * 0",
        "Elite - III * 1",
        "Elite - III * 2",
        "Elite - III * 3",
        "Elite - III * 4",
        "Elite - II * 0",
        "Elite - II * 1",
        "Elite - II * 2",
        "Elite - II * 3",
        "Elite - II * 4",
        "Elite - I * 0",
        "Elite - I * 1",
        "Elite - I * 2",
        "Elite - I * 3",
        "Elite - I * 4",
        "Master - IV * 0",
        "Master - IV * 1",
        "Master - IV * 2",
        "Master - IV * 3",
        "Master - IV * 4",
        "Master - III * 0",
        "Master - III * 1",
        "Master - III * 2",
        "Master - III * 3",
        "Master - III * 4",
        "Master - II * 0",
        "Master - II * 1",
        "Master - II * 2",
        "Master - II * 3",
        "Master - II * 4",
        "Master - I * 0",
        "Master - I * 1",
        "Master - I * 2",
        "Master - I * 3",
        "Master - I * 4",
        "Grandmaster - V * 0",
        "Grandmaster - V * 1",
        "Grandmaster - V * 2",
        "Grandmaster - V * 3",
        "Grandmaster - V * 4",
        "Grandmaster - V * 5",
        "Grandmaster - IV * 0",
        "Grandmaster - IV * 1",
        "Grandmaster - IV * 2",
        "Grandmaster - IV * 3",
        "Grandmaster - IV * 4",
        "Grandmaster - IV * 5",
        "Grandmaster - III * 0",
        "Grandmaster - III * 1",
        "Grandmaster - III * 2",
        "Grandmaster - III * 3",
        "Grandmaster - III * 4",
        "Grandmaster - III * 5",
        "Grandmaster - II * 0",
        "Grandmaster - II * 1",
        "Grandmaster - II * 2",
        "Grandmaster - II * 3",
        "Grandmaster - II * 4",
        "Grandmaster - II * 5",
        "Grandmaster - I * 0",
        "Grandmaster - I * 1",
        "Grandmaster - I * 2",
        "Grandmaster - I * 3",
        "Grandmaster - I * 4",
        "Grandmaster - I * 5",
        "Epic - V * 0",
        "Epic - V * 1",
        "Epic - V * 2",
        "Epic - V * 3",
        "Epic - V * 4",
        "Epic - V * 5",
        "Epic - IV * 0",
        "Epic - IV * 1",
        "Epic - IV * 2",
        "Epic - IV * 3",
        "Epic - IV * 4",
        "Epic - IV * 5",
        "Epic - III * 0",
        "Epic - III * 1",
        "Epic - III * 2",
        "Epic - III * 3",
        "Epic - III * 4",
        "Epic - III * 5",
        "Epic - II * 0",
        "Epic - II * 1",
        "Epic - II * 2",
        "Epic - II * 3",
        "Epic - II * 4",
        "Epic - II * 5",
        "Epic - I * 0",
        "Epic - I * 1",
        "Epic - I * 2",
        "Epic - I * 3",
        "Epic - I * 4",
        "Epic - I * 5",
        "Legend - V * 0",
        "Legend - V * 1",
        "Legend - V * 2",
        "Legend - V * 3",
        "Legend - V * 4",
        "Legend - V * 5",
        "Legend - IV * 0",
        "Legend - IV * 1",
        "Legend - IV * 2",
        "Legend - IV * 3",
        "Legend - IV * 4",
        "Legend - IV * 5",
        "Legend - III * 0",
        "Legend - III * 1",
        "Legend - III * 2",
        "Legend - III * 3",
        "Legend - III * 4",
        "Legend - III * 5",
        "Legend - II * 0",
        "Legend - II * 1",
        "Legend - II * 2",
        "Legend - II * 3",
        "Legend - II * 4",
        "Legend - II * 5",
        "Legend - I * 0",
        "Legend - I * 1",
        "Legend - I * 2",
        "Legend - I * 3",
        "Legend - I * 4",
        "Legend - I * 5"
};

std::string SplitGrade(const int uiRankLevel) {
    if (uiRankLevel <= 136) {
        std::string rankWithStars = strRank[uiRankLevel];
        std::size_t starPos = rankWithStars.find('-');
        if (starPos != std::string::npos) {
            std::string Row = rankWithStars.substr(starPos + 2);
            std::size_t awd = Row.find('*');
            std::string row1;
            std::string row2;
            if(awd != std::string::npos){
                row1 = Row.substr(0, awd - 1);
                row2 = Row.substr(awd + 2);
            }
            return row1;
        }
    }
    if (uiRankLevel > 136) {
        int Star = uiRankLevel - 136;
        if ((int)Star <= 24) return "Mythic";
        if ((int)Star > 24) return "Honor";
        if ((int)Star > 49) return "Glory";
        if ((int)Star > 99) return "Immortal";
    }
}

const char ascii_hex_4bit[23] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 10, 11, 12, 13, 14, 15};

static inline char to_upper(char c) {
    if ((c >= 'a') && (c <= 'z')) return c ^ 0x20;
    return c;
}

char * urldecode(const char * str) {
    size_t i, j, len = strlen(str);
    char c, d, url_hex;
    char * decoded = (char*)malloc(len + 1);
    if (decoded == NULL) return NULL;
    i = 0;
    j = 0;
    do {
        c = str[i];
        d = 0;
        if (c == '%') {
            url_hex = to_upper(str[++i]);
            if (((url_hex >= '0') && (url_hex <= '9')) || ((url_hex >= 'A') && (url_hex <= 'F'))) {
                d = ascii_hex_4bit[url_hex - 48] << 4;

                url_hex = to_upper(str[++i]);
                if (((url_hex >= '0') && (url_hex <= '9')) || ((url_hex >= 'A') && (url_hex <= 'F'))) {
                    d |= ascii_hex_4bit[url_hex - 48];
                } else {
                    d = 0;
                }
            }
        } else if (c == '+') {
            d = ' ';
        } else if ((c == '*') || (c == '-') || (c == '.') || ((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'Z')) || (c == '_')  || ((c >= 'a') && (c <= 'z'))) {
            d = c;
        }
        decoded[j++] = d;
        ++i;
    } while ((i < len) && (d != 0));

    decoded[j] = 0;
    return decoded;
}

std::string GetNickName(std::string UserId, std::string ZoneId) {
    std::string Result = "-";
    struct MemoryStruct chunk {};
    chunk.memory = (char*)malloc(1);
    chunk.size = 0;

    CURL * curl = curl_easy_init();
    if (curl != NULL) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, "https://order-sg.codashop.com/initPayment.action");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");

        struct curl_slist * headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Origin: https://www.codashop.com");
        headers = curl_slist_append(headers, "Referer: https://www.codashop.com/");
        headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Mobile Safari/537.36");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        std::string PostData = "{\"voucherPricePoint.id\": \"27670\", \"voucherPricePoint.price\": \"242535.0\", \"voucherPricePoint.variablePrice\": \"0\", \"n\": \"12/7/2022-2046\", \"email\": \"\", \"userVariablePrice\": \"0\", \"order.data.profile\": \"eyJuYW1lIjoiICIsImRhdGVvZmJpcnRoIjoiIiwiaWRfbm8iOiIifQ==\", \"user.userId\": \"" + UserId + "\", \"user.zoneId\": \"" + ZoneId + "\", \"msisdn\": \"\", \"voucherTypeName\": \"MOBILE_LEGENDS\", \"shopLang\": \"id_ID\", \"voucherTypeId\": \"5\", \"gvtId\": \"19\", \"checkoutId\": \"\", \"affiliateTrackingId\": \"\", \"impactClickId\": \"\", \"anonymousId\": \"\"}";

        curl_easy_setopt(curl, CURLOPT_POST, true);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, PostData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            try {
                json Response = json::parse(chunk.memory);
                if (Response["success"]) {
                    std::string Encrypt = Response["confirmationFields"]["username"].get<std::string>();
                    Result = urldecode(Encrypt.c_str());
                }
            } catch (json::exception & e) {
            }
        }
    }
    curl_easy_cleanup(curl);

    return Result;
}

std::tuple<std::string, std::string> SplitRankAndStars(const int uiRankLevel, const int iMythPoint) {
    if (uiRankLevel <= 136) {
        std::string rankWithStars = strRank[uiRankLevel];
        std::size_t starPos = rankWithStars.find('*');
        if (starPos != std::string::npos) {
            std::string rankName = rankWithStars.substr(0, starPos - 1);
            std::string starCount = rankWithStars.substr(starPos + 2);
            return std::make_tuple(rankName, starCount);
        }
    }
    std::string nameMythic = "Mythic";
    if(uiRankLevel > 136){
        float starMythic = (float)iMythPoint * (50.0 / 600.0);
        int Star = uiRankLevel - 136;
        if ((int)Star > 24)  nameMythic = "Mythical Honor";
        if ((int)Star > 49)  nameMythic = "Mythical Glory";
        if ((int)Star > 99)  nameMythic = "Mythical Immortal";
        return std::make_tuple(nameMythic, std::to_string(Star));
    }
}

std::string VerifiedToString(int iCertify) {
    std::string str = std::string(OBFUSCATE("-"));
    if (iCertify == 0) {
        str = std::string(OBFUSCATE("No"));
    } else {
        str = std::string(OBFUSCATE("Yes"));
    }
    return str;
}

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


