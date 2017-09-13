#pragma once

enum KEYCOMBO : uint16_t
{
    TRACE,
	GOTOSELF,
	REPORTER,
	REPORTOUT,
	RELASTWARN,
	GETSTATS,
	GETLASTIP,
	IPOFFBAN
};

struct Trace
{
	D3DXVECTOR3 start, end;
	DWORD color, time;
	Trace(float *st, float *en, DWORD col, DWORD tim)
	{
		start.x = st[0];
		start.y = st[1];
		start.z = st[2] - 0.2f;
		end.x = en[0];
		end.y = en[1];
		end.z = en[2];
		color = col;
		time = tim;
	}
};

struct stIpInfo
{
	std::string City, Provider;
	float pos[2];
};

struct AdminSetting
{
    using stPlayerChecker = std::pair<std::string, std::string>;
    using keyBind = std::pair<std::string, keycombo>;

	std::vector<uint16_t> PlayersIDForTP;
    std::vector<uint16_t> AdminsOnline;
    std::vector<uint16_t> PlayersOnline;
	std::vector<Trace> Tracers;
	std::vector<std::string> AdminChecker;
    std::vector<stPlayerChecker> PlayerChecker;
    std::vector<keyBind> keycombo;

    std::string aCheckerMsg, pCheckerMsg;
    std::string connectLog, disconnectLog;
    std::string fontName;

    uint64_t connectTime, disconnectTime;
    POINT aCheckPos, pCheckPos, killListPos, connectionPos;

    FILE *fLogBan, *fLogWarn, *fLogKillList;


	/* ֱûסענûו גûהאקט */
	int						process;
	int						objid;
	char                    objname[50];
	char                    massobjname[50];
	int						uninv_players_left;
	int						players_left;
	int						gplayercount;
	int						ids[14];
	int						mass_players_left;
	//////////////////////////////////////////

	char IP[3][100];
	char banIP[2][100];
	int lastip = 0;
	int ipoffban = 0;
	int tags;
	int reportid;
	int reportvalid = 0;
	int warningid;
	int warningvalid = 0;
	short reconID;

	/*4 bytes*/
    DWORD dwTraceTimer;
	DWORD dwColorTracerHit;
	DWORD dwColorTracer;
#pragma region ChatColor
	DWORD dwColorSms;
    DWORD dwColorReport;
    DWORD dwColorReportr;
    DWORD dwColorSupport;
    DWORD dwColorFeedback;
#pragma endregion
#pragma region VisualSetting
	DWORD dwColorEnable;
	DWORD dwColorDisable;
#pragma endregion
	int iHpCount;
	int iAmmoCount;

	/*2 bytes*/
	unsigned short usSetLeaderID;
	unsigned short usMaxPlayerTP;
	unsigned short usTraceID;
	unsigned short usTraceMaxCount;

	/*1 bytes*/
	unsigned char byteAhelp;
	unsigned char byteACMD;
	unsigned char byteFrackID;
	unsigned char byteWeaponID;
	unsigned char byteSkillWeaponID;
    uint8_t       byteFontHeight;

#pragma region ChatColorControl
	bool bChatcolor;
	bool bHudIndicatorChatcolors;
	bool bChatcolorsSms;
	bool bChatcolorsReport;
	bool bChatcolorsFeedback;
	bool bChatcolorsReportr;
	bool bChatcolorsSupport;
#pragma endregion
	bool bTraces;
	bool bMassHP;
	bool AllIP;
	bool offbanip;
	bool Gobj;
	bool bGiveGuns;
	bool bSkillGun;
	bool bMassTP;
	bool bTraceAll;
	bool bChatID;
	bool bIpInfo;
	bool bReport;
    bool bConnectLog;
    bool bDisconnectLog;
    bool bHudIndicatorTrace;
    bool bLogBan;
    bool bLogWarn;
    bool bLogKillList;
    bool bHudPing;
};

struct stSettingParams
{
    using keycomboSet = std::pair<uint8_t, std::string>;
    std::vector<keycomboSet> keycombo;
    uint8_t keycomboId;
};

void initAdminSettings();
void endKeyHook();
extern struct AdminSetting A_Set;
extern IniFile A_Ini;
extern stSettingParams parAdminSetting;