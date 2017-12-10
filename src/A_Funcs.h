#pragma once

void			adminMainThread(void);
bool			FileExists(char *filename);
void			OnCloseDialog(void *pDialog);
void			D3DColorToStringColor(D3DCOLOR dwColor, char* szOutColor);
void			StringReplace(char str[], char a[], char b[], char output[]);
void			StringFind(char *string, char *search, char stop_symbol, char output[]);
int				getPlayerID(char *name);
bool			stringToD3DColor(const char* szStrColor, D3DCOLOR* dwOutColor);
LRESULT			CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT			CALLBACK LLKeyProc(int nCode, WPARAM wParam, LPARAM lParam);
void			SravnenieIP();
void			addAdminCommand(char *name, CMDPROC function);
void            string2Keycombo(const std::string &str, keycombo &ret);
void            setFontParams(CD3DFont **pFont, const char *fontName, uint8_t fontHeight);
void            addOnlineAdmin(uint16_t playerId, const char *szPlayerName, bool bToFile = false);
void            addOnlinePlayer(uint16_t playerId, const char *szPlayerName, const char *szReason, bool bToFile = false);
bool            deleteFromOnlineList(std::vector<uint16_t> &checker, std::string &msg, uint16_t playerId, const std::string &nick);
void            deleteFromAdminList(uint16_t playerId);
void            deleteFromPlayerList(uint16_t playerId);
std::string     keycombo2String(const keycombo &keycombo);
void            adminLog(FILE *fileLog, const char *fmt, ...);
void            stringSplit(std::string const &source, std::string const &delimiter, std::vector <std::string> &out);
void            setFontParams(CD3DFont **pFont, const char *fontName, uint8_t fontHeight);