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
	IPOFFBAN,
	STOP
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



	/* Чекеры */
	char                    admin[300][30];
	char                    check[300][30];
	char                    reason[300][255];
	std::vector<int>		adm_online, player_online;
	/* IP-INFO */
	int						ipresult[2];
	int						IPinfo;
	int						IPinfo_progress;
	char					countryandcity[2][70];
	char					provider[2][70];
	int						distance;
	int						isProviderValid[2];
	int						distancevalid[2];
	double					latFirstIP;
	double					lngFirstIP;
	double					latSecondIP;
	double					lngSecondIP;
	int						outmethod;
	/* Быстрые выдачи */
	int						process;
	int						objid;
	char                    objname[50];
	char                    massobjname[50];
	int						uninv_players_left;
	int						players_left;
	int						gplayercount;
	int						ids[14];
	int                     hpcount;
	int						mass_players_left;
	int						gunlist;
	int						gunid[7];
	int						gunbullets[7];
	int                     obnova = 0;
	//////////////////////////////////////////
	/* Телепорт */
	int                     phonestate;
	int						tpcount;
	int						tpcount_left;
	int						tpid[100];
	int						teleportlist;
	int						tphp;
	int						gcount;
	int						tplimit;
	int						started;
	int						stopped;
	int						listed[1004];
	//////////////////////////////////////////

	char IP[3][150];
	char banIP[2][100];
	int lastip = 0;
	int ipoffban = 0;
	int tags;
	int reportid;
	int reportvalid = 0;
	int warningid;
	int warningvalid = 0;
	short reconID;
	int Chat = 0;
	int Vivod = 1;
	int stoped = 0;

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
	unsigned short sPlId;
	unsigned short usTraceMaxCount;

	/*1 bytes*/
	unsigned char byteAhelp;
	unsigned char byteACMD;
	unsigned char byteInfo;
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
	bool bGiveGuns;
	bool bSkillGun;
	bool bMassTP;
	bool SravnenieIP;
	bool bTraceAll;
	bool bChatID;
	bool bReport;
    bool bConnectLog;
    bool bDisconnectLog;
    bool bHudIndicatorTrace;
    bool bLogBan;
    bool bLogWarn;
    bool bLogKillList;
    bool bHudPing;
	bool bSortID;
};

struct stSettingParams
{
    using keycomboSet = std::pair<uint8_t, std::string>;
    std::vector<keycomboSet> keycombo;
    uint8_t keycomboId;
};

void initAdminSettings();
void endKeyHook();
void getAdminList();
void getPlayerList();
void removeInFile(const char *filename, const uint16_t sRemoveLineId);
void deleteFromFile(char *playername, char *filename);
void appendToFile(const char *filename, const char *nickname);
void appendToPlayerFile(const char *nickname, const char *reason);
extern struct AdminSetting A_Set;
extern IniFile A_Ini;
extern stSettingParams parAdminSetting;