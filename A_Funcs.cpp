﻿#include "main.h"

#include <wininet.h>
#include <vector>   

struct S1 {
	int m1;
	double m2, m3;
};

#pragma comment ( lib, "Wininet.lib" )

using std::string;

const char *szFracktionName[] =
{
	"LSPD",
	"FBI",
	"LVa",
	"MOH",
	"LCN",
	"Yakuza",
	"Mayor",
	"RM",
	"SFn",
	"LSn",
	"Instrustors",
	"Rifa",
	"Grove",
	"Ballas",
	"Vagos",
	"Aztec",
	"SFPD",
	"LVPD",
	"SFa",
	"None",
	"LVn",
	"Hell Angel's MC",
	"Mongols MC",
	"Pagans MC",
	"Outlaws MC",
	"Son's Of Silence MC",
	"Warlocks MC",
	"Highwayman MC",
	"Bandidos MC",
	"FreeSouls MC",
	"Vagos MC"
};

int getPlayerID(char *name)
{
	if (g_Players == NULL)
		return -1;

	if (strcmp(name, getPlayerName(g_Players->sLocalPlayerID)) == 0)
		return g_Players->sLocalPlayerID;

	int ID;
	for (int p = 0; p < SAMP_MAX_PLAYERS; p++)
	{
		if (g_Players->iIsListed[p] != 1)
			continue;

		if (strcmp(getPlayerName(p), name) == 0)
		{
			ID = p;
			return ID;
		}
	}
	return -1;
}

char* getfractionname(int fractionId)
{
	switch (fractionId) {
	case 1: return "LSPD"; case 2: return "FBI"; case 3: return "LVa";
	case 4: return "MOH"; case 5: return "LCN"; case 6: return "Yakuza"; case 7: return "Mayor";
	case 8: return "RM"; case 9: return "SFn"; case 10: return "LSn"; case 11: return "Instrustors";
	case 12: return "Rifa"; case 13: return "Grove"; case 14: return "Ballas"; case 15: return "Vagos";
	case 16: return "Aztec"; case 17: return "SFPD"; case 18: return "LVPD"; case 19: return "SFa";
	case 21: return "LVn"; case 22: return "Hell Angel's MC"; case 23: return "Mongols MC";
	case 24: return "Pagans MC"; case 25: return "Outlaws MC"; case 26: return "Son's Of Silence MC";
	case 27: return "Warlocks MC"; case 28: return "Highwayman MC"; case 29: return "Bandidos MC";
	case 30: return "FreeSouls MC"; case 31: return "Vagos MC";
	}
}

void OnCloseDialog(void *pDialog)
{
    stDialogInfo Dialog = *(stDialogInfo*)pDialog;
    switch (Dialog.iType)
    {
    case DialogStyle::DIALOG_STYLE_LIST:
    {
        int iSelectItem = *(int*)(DWORD(Dialog.pList) + 0x147);
        switch (Dialog.DialogID)
        {
        case 2:
        {
            if (A_Set.usSetLeaderID > 999)
            {
                return;
            }

            if (iSelectItem < 20)
                A_Set.byteFrackID = iSelectItem;
            else
                A_Set.byteFrackID = iSelectItem + 1;

            if (A_Set.byteFrackID != 0)
                ShowLocalSampDialog(3, DIALOG_STYLE_MSGBOX, "Подтверждение", (char *)std::string("Вы уверены что хотите назначить " + std::string(getPlayerName(A_Set.usSetLeaderID)) + " на лидерство " + szFracktionName[A_Set.byteFrackID - 1]/*std::string(getfractionname(byteFrackID))*/).c_str(), "Назначить", "Закрыть");
            else
                ShowLocalSampDialog(3, DIALOG_STYLE_MSGBOX, "Подтверждение", (char *)std::string("%sВы уверены что хотите cнять " + std::string(getPlayerName(A_Set.usSetLeaderID)) + " с лидерства").c_str(), "Назначить", "Закрыть");
            break;
        }
		case 3:
		{

			if (iSelectItem < 5)
				A_Set.byteACMD = iSelectItem;
			else
				A_Set.byteACMD = iSelectItem + 1;

			if (A_Set.byteACMD == 0)
				ShowLocalSampDialog(5, DIALOG_STYLE_MSGBOX, "Команды 1 уровня", "{f98a00}/a [текст]{ffffff} - Чат администраторов.\n{f98a00}/pm[id][текст]{ffffff} - Ответить на жалобу.\n{f98a00}/getskill[id]{ffffff} - Показать навыки игрока.\n{f98a00}/admins{ffffff} - Показать список Администраторов онлайн.\n{f98a00}/givecopkeys[id]{ffffff} - Дать, забрать ключи от полицейского участка.\n{f98a00}/getstats[id]{ffffff} - Показать статистику игрока.\n{f98a00}/ooc[Текст](/ o){ffffff} - Отправить сообщение в общий чат.\n{f98a00}/togphone{ffffff} - Выключить, включить телефон.\n{f98a00}/unjail[id]{ffffff} - Освободить игрока из тюрьмы или Форта ДеМорган.\n{f98a00}/jail[id][мин.]{ffffff} - Посадить игрока в тюрьму(если минуты не указанно - пожизненно).\n{f98a00}/mute[id][время в сек][причина]{ffffff} - Заблокировать чат игроку(если не указывать время, то 5 минут / -1 узнать кол - во секунд).\n{f98a00}/kick[id / name][Причина]{ffffff} - Кикнуть игрока.\n{f98a00}/aad[Текст]{ffffff} - сообщение в формате : Администратор Yann_Dobermann : [Текст].Будет видно всем.\n{f98a00}/alock{ffffff} - Открыть транспорт.\n{f98a00}/ram{ffffff} - войти в закрытый дом.\n{f98a00}/tjail[ID]{ffffff} - выводит в чат время через которое игрок выйдет из тюрьмы(в секундах).\n{f98a00}/sduty{ffffff} - для прослушивания вопросов, ответов и чата саппоротов.\n{f98a00}/sc{ffffff} - чат для саппортов, видно только под / sduty.\n{f98a00}/gm{ffffff} - GM для админов.\n{f98a00}/atipster[id фракции]{ffffff} - Прослушка чата организации.\n{f98a00}/fid{ffffff} - показывает список всех фракций и их ид.\n{f98a00}/gmap[id банды]{ffffff} - показывает количество захваченных территорий указанной банды.\n{f98a00}/anim{ffffff} - список доступных анимаций Администратора(использование - /anim[библиотека][номер анимации][повторять]).\n{f98a00}/ajob{ffffff} - вывести меню устройства на работу.\n{f98a00}/sort{ffffff} - сортировка и вывод в окне данных игроков(к примеру рпр, лвл таксиста).\n{f98a00}/hp{ffffff} - Пополнить себе здоровье до 255.", "Вернуться", "Закрыть");
			if (A_Set.byteACMD == 1)
				ShowLocalSampDialog(5, DIALOG_STYLE_MSGBOX, "Команды 2 уровня", "{f98a00}/spcar{ffffff} - Отправить машину в которой сидишь на место появления.\n{f98a00}/recon[id](/re) (/ку){ffffff} - Войти в режим наблюдения за игроком.\n{f98a00}/prison[id] [время в сек]{ffffff} - Посадить игрока в Форт ДеМорган(если не указывать время, то дается на 60 минут).\n{f98a00}/goto [id]{ffffff} - ТП к игроку.\n{f98a00}/take[id]{ffffff} - Забрать лицензии, оружие, наркотики, маты.\n{f98a00}/warn[id] [Причина]{ffffff} - Выдать предупреждение за использование читов(Варн).\n{f98a00}/ban[id] [Причина]{ffffff} - Заблокировать игрока.\n{f98a00}/setskin[id скина]{ffffff} - Сменить одежду(скин фракции снимается).\n{f98a00}/iwep[id]{ffffff} - Показать статистику оружия у игрока.\n{f98a00}/slap[id]{ffffff} - Дать пинка игроку.\n{f98a00}/whoNear{ffffff} - Показывает список игроков в указанном радиусе и с указанным лвл(вокруг админа).\n{f98a00}/offprison[ник] [время]{ffffff} - посадить игрока в Форт Де Морган в момент, когда игрок не в игре(оффлайн).\n{f98a00}/v[id auto][Color 1][Color 2]{ffffff} - создать автомобиль.\n{f98a00}/g [id оружия]{ffffff} - создать оружие.", "Вернуться", "Закрыть");
			if (A_Set.byteACMD == 2)
				ShowLocalSampDialog(5, DIALOG_STYLE_MSGBOX, "Команды 3 уровня", "{f98a00}/tplist (/tp){ffffff} - Список мест для телепортации.\n{f98a00}/spcars{ffffff} - Отправить машины на место появления.\n{f98a00}/forceskin[id]{ffffff} - Отправить на смену скина.\n{f98a00}/setnik[id]{ffffff} - Одобрить смену ника.\n{f98a00}/mark{ffffff} - Установить метку для телепорта на месте где стоишь.\n{f98a00}/gotomark{ffffff} - Телепортироватся к метке.\n{f98a00}/gethere[id]{ffffff} - Телепортировать игрока к себе.\n{f98a00}/freeze[id]{ffffff} - Заморозить игрока.\n{f98a00}/unfreeze[id]{ffffff} - Разморозить игрока.\n{f98a00}/banip[ip]{ffffff} - Блокировка ip адреса.\n{f98a00}/gotocar[id]{ffffff} - Телепортироваться к транспорту.\n{f98a00}/amembers [id фракции]{ffffff} - Просмотр онлайн фракций без вступления в них.\n{f98a00}/givemf [id]{ffffff} - дает игроку мегафон.\n{f98a00}/fpanel{ffffff} - панель управления фермой(нужно быть у фермы).","Вернуться", "Закрыть");
			if (A_Set.byteACMD == 3)
				ShowLocalSampDialog(5, DIALOG_STYLE_MSGBOX, "Команды 4 уровня", "{08e700}/settime [time]{ffffff} - Установить время суток (в /time время не меняется).\n{08e700}/noooc{ffffff} - Вкл/выкл чат оос.\n{08e700}/sp{ffffff} - Телепортироваться на свой респавн.\n{08e700}/sethealcost [цена]{ffffff} - Установить цену лечения (за 1 единицу жизни).\n{08e700}/uninvite [id] [Причина]{ffffff} - Уволить игрока из организации.\n{08e700}/skick [id]{ffffff} - Тихий кик.\n{08e700}/sban [id]{ffffff} - Тихая блокировка.\n{08e700}/gmx{ffffff} - Рестарт сервера!!!\n{08e700}/gettax{ffffff} - Узнать баланс казны.\n{08e700}/reloadlog{ffffff} - Обновить лог Сампа!!!\n{08e700}/unbanip{ffffff} - Разблокирование ip адреса.\n{08e700}/getip{ffffff} - Узнать ip игрока.\n{08e700}/agetip{ffffff} - Узнать ip у оффлайн игрока.\n{08e700}/pgetip [1 - 4 частей] [ip]{ffffff} - узнать ники игроков с IP (проверяет только онлайн игроков).\n{08e700}/offban [ник]{ffffff} - Заблокировать игрока в оффлайн.\n{08e700}/olimit{ffffff} - Антифлуд в оос (устанавливает время в секундах).\n{08e700}/agetstats{ffffff} - Посмотреть статистику игрока в оффлайн.\n{08e700}/iban [id]{ffffff} - Выдать вечный бан игроку.\n{08e700}/splist{ffffff} - Информация о Саппортах.\n{08e700}/ioffban [nick]{ffffff} - Выдать вечный бан игроку offline.\n{08e700}/farmstats{ffffff} - Статистика фермы.\n{08e700}/namelog{ffffff} - проверка на прошлые ники.\n{08e700}/cUninvite{ffffff} - уволить крупье казино.", "Вернуться", "Закрыть");
			if (A_Set.byteACMD == 4)
				ShowLocalSampDialog(5, DIALOG_STYLE_MSGBOX, "Команды 5 уровня", "/house - Телепорт в указанный дом.\n{08e700}/biz{ffffff} - Телепорт к указаному бизнесу.\n{08e700}/houseo{ffffff} - Телепорт к указаному дому.\n{08e700}/makeleader[id]{ffffff} - Сделать игрока Лидером организации.\n{08e700}/givegun{ffffff} - Выдать игроку оружие.\n{08e700}/sethp[количество]{ffffff} - Установить игроку жизни.\n{08e700}/fixveh{ffffff} - Отремонтировать машину в которой находишься.\n{08e700}/fixvehs{ffffff} - Отремонтировать транспорт в радиусе 60 метров.\n{08e700}/veh[id auto][Color 1][Color 2]{ffffff} - Создать транспорт.\n{08e700}/destroycar{ffffff} - Уничтожить транспорт в котором находишся.\n{08e700}/unban[name]{ffffff} - Разблокирование аккаунта.\n{08e700}/arace{ffffff} - Начать гонку.\n{08e700}/aderby{ffffff} - Начать гонку <Дерби>.\n{08e700}/apain{ffffff} - Начать PaintBall.\n{08e700}/hbject{ffffff} - Прикрепить объект к игроку.\n{08e700}/offuninvite{ffffff} - Уволить игрока в оффлайн.\n{08e700}/unwarn{ffffff} - Снять варн у игрока.{08e700}/apanel{ffffff} - Банки организаций.\n{08e700}/setmbiz[BizID(-1 список)][Mafia 5, 6, 8]{ffffff} - Установить бизнес.\n{08e700}/hbedit{ffffff} - /hbject редактор.\n{08e700}/createvote{ffffff} - создать голосование.\n{08e700}/bantime{ffffff} - Показывает дату и время снятия бана.\n{08e700}/weather[Номер]{ffffff} - Установить погоду.\n{08e700}/spmenu{ffffff} - Управление Саппортами.\n{08e700}/farm[id]{ffffff} - Телепорт к Фермам.\n{08e700}/tune[id]{ffffff} - телепорт к СТО.\n{08e700}/actor[слот][скин][хп][аним.библиотека][аним.ид][повторять]{ffffff} - создать бота с указанным скином, ХП и анимацией.\n{08e700}/banlog[nick]{ffffff} - проверить лог банов аккаунта.\n{08e700}/abizMafia{ffffff} - смена мафии у бизнеса.", "Вернуться", "Закрыть");
			break;
		}
		case 4:
		{

			if (iSelectItem < 3)
				A_Set.byteAhelp = iSelectItem;
			else
				A_Set.byteAhelp = iSelectItem + 1;

			if (A_Set.byteAhelp == 0)
				ShowLocalSampDialog(5, DIALOG_STYLE_MSGBOX, "Информация по командам", "/ahelp - вызывать меню помощи собейта.\n/masshp [кол-во ХП] - выдаёт указаное кол-во ХП игрокам в зоне стрима.\n/leader [id] - назначение на лидерство через диалоговую панель.\n/gobj [название объекта][id'ы игроков] - выдача объектов по id игроков.\n/massw [id оружия][кол-во пуль] - выдача оружия игрокам в зоне стрима.\n/ranks [название фракции] - показывает ранги фракции.\n/skill [id] - выдача оружия на скиллы.\n/startp [кол-во игроков] - начать телепортацию игроков по SMS.\n/endtp - закончить телепортацию игроков.\n/tr [параметр] - трейсеры игроков.\n/savegz [Имя файла] - сохранит состояние гетто на данное время.\n/cmpgz [Имя файла] - загрузить состояние гетто.\n/clrgz - отключить подсветку изменения состояния гетто\n/setfont - изменить шрифт собейта.", "Вернуться", "Закрыть");
			if (A_Set.byteAhelp == 1)
				ShowLocalSampDialog(5, DIALOG_STYLE_MSGBOX, "Информация по командам", "/ahelp er - вызывать меню помощи собейта", "Вернуться", "Закрыть");
			if (A_Set.byteAhelp == 2)
				ShowLocalSampDialog(3, DialogStyle::DIALOG_STYLE_LIST, "Команды администрации", "1-ый уровень администрирования\n2-ой уровень администрирования\n3-ий уровень администрирования\n4-ый уровень администрирования\n5-ый уровень администрирования", "Выбрать", "Закрыть");
			break;
		}
        }
        break;
    }
    case DialogStyle::DIALOG_STYLE_MSGBOX:
    {
        switch (Dialog.DialogID)
        {
        case 3:
            say("/makeleader %hd %hhd", A_Set.usSetLeaderID, A_Set.byteFrackID);
            break;

		case 5:
			ShowLocalSampDialog(4, DialogStyle::DIALOG_STYLE_LIST, "Помощь по собейту", "Команды собейта\nКлавиши собейта\nКоманды администрации", "OK", "Cancel");
			break;
        }
        break;
    }

    case DialogStyle::DIALOG_STYLE_INPUT:
    case DialogStyle::DIALOG_STYLE_PASSWORD:
        char input[256];
        wchar_t *inputBuf = *(wchar_t **)(uint32_t(g_Dialog->pEditBox) + 0x4D);
        UnicodeToAnsi(inputBuf, input);
        switch (Dialog.DialogID)
        {
        case 523:
            setFontParams(&pD3DFont, input, A_Set.byteFontHeight);
            A_Set.fontName = input;
            A_Ini.SetString("FontSetting", "MainFontName", input);
			addMessageToChatWindow("Шрифт изменён");
            break;
        }
        break;
    }
}

bool stringToD3DColor(const char* szStrColor, D3DCOLOR* dwOutColor)
{
	int len = strlen(szStrColor);
	if (len != 6 && len != 8)
		return false;

	*dwOutColor = 0;

	if (len == 6)
		*dwOutColor = 0xFF << 24;

	len -= 1;

	for (int i = 0; i <= len; i++)
	{
		if (szStrColor[i] < '0' || (szStrColor[i] > '9' && szStrColor[i] < 'A') || szStrColor[i]>'F')
			return false;

		byte temp = 0;
		if (szStrColor[i] > '9')
			temp = szStrColor[i] - 'A' + 10;
		else
			temp = szStrColor[i] - '0';

		*dwOutColor |= (temp << ((len - i) * 4));
	}
	return true;
}

void D3DColorToStringColor(D3DCOLOR dwColor, char *szOutColor)
{
	sprintf(szOutColor, "{%06X}", dwColor & 0x00FFFFFF/*(dwColor << 8) >> 8*/);
}


void stringSplit(string const &source, string const &delimiter, std::vector <string> &out)
{
	string::size_type last_pos = 0, i = 0;
	while ((i = source.find(delimiter, i)) != string::npos) {
		out.push_back(source.substr(last_pos, i - last_pos)), last_pos = ++i;
	}
	out.push_back(source.substr(last_pos, source.length() - last_pos));
}

int key_lookup(const char *name);
void string2Keycombo(const std::string &str, keycombo &ret)
{
    if (str.empty())
        return;

	std::vector <string> keys;
	ZeroMemory(&ret, sizeof(ret));
    stringSplit(str, " ", keys);
	if (keys.size() > 0 && keys.size() <= INI_KEYCOMBO_MAX) {
		for (string &key : keys) {
			int keyCode = key_lookup(key.c_str());
            if (keyCode != -1)
                ret.key[ret.count++] = keyCode;
            else
                addMessageToChatWindow("[ERROR]: Unknown key: %s", key.c_str());
		}
	}
}

std::string keycombo2String(const keycombo &keycombo)
{
    std::string ret;
    for (int id = 0; id < keycombo.count; ++id) {
        uint16_t key = keycombo.key[id];
        ret.append(key_name(keycombo.key[id]));
        ret.append(" ");
    }
    ret.pop_back();
    return ret;
}

void setFontParams(CD3DFont **pFont, const char *fontName, uint8_t fontHeight)
{
    /*delete pD3DFont;
    pD3DFont = new CD3DFont(A_Set.fontName.c_str(), A_Set.byteFontHeight, FCR_BORDER);
    pD3DFont->Initialize(origIDirect3DDevice9);*/
    delete *pFont;
    *pFont = new CD3DFont(fontName, fontHeight, FCR_BORDER);
    (*pFont)->Initialize(origIDirect3DDevice9);
}

inline bool operator<=(const POINT &a, const POINT &b)
{
    return a.x <= b.x && a.y <= b.y;
}

inline bool operator>=(const POINT &a, const POINT &b)
{
    return a.x >= b.x && a.y >= b.y;
}

inline bool operator==(const POINT &a, const POINT &b)
{
    return a.x == b.x && a.y == b.y;
}

inline bool operator!=(const POINT &a, const POINT &b)
{
    return !(a == b);
}

inline POINT operator+(const POINT &a, const POINT &b)
{
    POINT tmp(a);
    tmp.x += b.x;
    tmp.y += b.y;
    return tmp;
}

inline POINT operator-(const POINT &a, const POINT &b)
{
    POINT tmp(a);
    tmp.x -= b.x;
    tmp.y -= b.y;
    return tmp;
}

inline POINT operator-(const POINT &a, const long &b)
{
    POINT tmp(a);
    tmp.x -= b;
    return tmp;
}

inline POINT CursorPos()
{
    POINT CurPos;
	GetCursorPos(&CurPos);
	if (pPresentParam.Windowed)
	{
		RECT *pos = new RECT();
		GetWindowRect(pPresentParam.hDeviceWindow, pos);
		CurPos.x -= (8 + pos->left);
		CurPos.y -= (30 + pos->top);
		delete pos;
	}
	return CurPos;
}

float GeoDistance(float *start, float *end)
{
	start[0] *= M_PI / 180;
	start[1] *= M_PI / 180;
	end[0] *= M_PI / 180;
	end[1] *= M_PI / 180;
	float y, x, del = start[1] - end[1];
	y = sqrt(pow(cos(end[0])*sin(del), 2) + pow(cos(start[0])*sin(end[0]) - sin(start[0])*cos(end[0])*cos(del), 2));
	x = sin(start[0])*sin(end[0]) + cos(start[0])*cos(end[0])*cos(del);
	return atan2(y, x) * 6372.795;//km
}

//LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//	if (g_SAMP != nullptr)
//	{
//		switch (uMsg)
//		{
//			//case WM_KEYUP:
//			{
//				//char *key = key_name(wParam);//code key // не определяет shift/alt/ctrl (другие коды клавишь)
//				//addMessageToChatWindow("Key: %s, Code: 0x%X | lParam: 0x%X", key, wParam, lParam);
//			break;
//			}
//		}
//	}
//	return CallWindowProcA(WNDPROC(lOldWndProc), hwnd, uMsg, wParam, lParam);
//}

LRESULT CALLBACK LLKeyProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (GetForegroundWindow() == *(HWND*)0xC97C1C)
    {
        if (g_SAMP != nullptr)
        {
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
            {
                return -1;
            }
            else
                if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
                {
                    if (nCode == HC_ACTION)
                    {
                        uint16_t vk = ((LPKBDLLHOOKSTRUCT)lParam)->vkCode;
                        if (vk == 0x1B || vk == 0xD) {//esc = 0x1B, 0xD = enter
                            endKeyHook();
                            return 0;
                        }

                        const char *key = key_name(vk);
                        if (key == nullptr) {
                            addMessageToChatWindow("[KEY_HOOK] Unknown key: 0x%X. Данная клавиша проигнорирована для бинда. Если требуется отпишитесь.", vk);
                        }
                        else {
                            if (std::find_if(parAdminSetting.keycombo.cbegin(), parAdminSetting.keycombo.cend(), 
                                [&vk](const std::pair<uint8_t, std::string> &pair) { return pair.first == vk; }) == parAdminSetting.keycombo.cend()){
                                parAdminSetting.keycombo.emplace_back(uint8_t(vk), key);//.push_back(std::make_pair(vk, key));
                                if (parAdminSetting.keycombo.size() >= INI_KEYCOMBO_MAX) {
                                    endKeyHook();
                                }
                            }
                        }
                        return 0;
                    }
                }
        }
    }
    ///UnhookWindowsHookEx(hhKeyKook);
    ///hhKeyKook = nullptr;
    return CallNextHookEx(hhKeyKook, nCode, wParam, lParam);
}

void adminMainThread(void)
{
	traceLastFunc("adminMainThread()");
	static DWORD timer = 0;
	DWORD dwCurrentTime = GetTickCount();
    if (dwCurrentTime - timer > 1150) {
    #pragma region MassHP
        if (A_Set.bMassHP)
        {
            static unsigned short sPlId = 0;
            if (sPlId <= g_Players->ulMaxPlayerID)
            {
                if (g_Players->iIsListed[sPlId] && g_Players->pRemotePlayer[sPlId]->pPlayerData->pSAMP_Actor != nullptr)
                {
                    say("/sethp %hu %d", sPlId, A_Set.iHpCount);
                    addMessageToChatWindow("Игроку %s[%d] выдано %d HP", getPlayerName(sPlId), sPlId, A_Set.iHpCount);
                    timer = dwCurrentTime;
                }
                sPlId++;
            }
            else
            {
                A_Set.bMassHP = false;
                sPlId = 0;
                addMessageToChatWindow("Выдача HP окончена");
                MessageBeep(MB_ICONEXCLAMATION);
            }
        }
    #pragma endregion
	#pragma region AllIP
		if (A_Set.AllIP)
		{
			say("/pgetip 4 %s", A_Set.IP[1]);
			A_Set.AllIP = false;
		}
	#pragma endregion
	#pragma region IPOFFBAN
		if (A_Set.offbanip)
		{
			say("/banip %s", A_Set.IP[1]);
			A_Set.offbanip = false;
		}
	#pragma endregion
	#pragma region Gobj
		if (A_Set.Gobj)
		{
			char	filename[MAX_PATH];
			FILE	*file;
			int		j, lines = 0;
			char	arr[100], content[100][100];

			snprintf(filename, sizeof(filename), "%s\\mod_sa\\Objects\\%s.txt", g_szWorkingDirectory, A_Set.objname);
			file = fopen(filename, "r");

			if (file == NULL) return addMessageToChatWindow("Ошибка: файл %s.txt не найден в папке mod_sa\\Objects", A_Set.objname);

			if (file)
			{
				A_Set.process = 1;

				for (j = 0; fgets(arr, 100, file) != NULL; j++)
				{
					strcpy(content[j], arr);
					lines++;
				}

				fclose(file);
				addMessageToChatWindow("Выдача объектов начата");
				MessageBeep(MB_ICONEXCLAMATION);

				A_Set.players_left = A_Set.gplayercount;

				for (int i = 0; i < A_Set.gplayercount; i++)
				{
					if (!A_Set.process)
						break;

					for (j = 0; j < lines; j++)
					{
						if (!A_Set.process)
							break;

						say("/hbject %d %s", A_Set.ids[i], content[j]);
						timer = dwCurrentTime;
						return;
					}
					addMessageToChatWindow("Игроку %s[%d] выдан комплект объектов \"%s\"", getPlayerName(A_Set.ids[i]), A_Set.ids[i], A_Set.objname);
					A_Set.players_left--;
					timer = dwCurrentTime;
				}

				A_Set.process = 0;
				addMessageToChatWindow("Выдача объектов окончена");
				A_Set.bMassHP = false;
				MessageBeep(MB_ICONEXCLAMATION);
				memset(A_Set.ids, 0, sizeof(A_Set.ids));
			}
			else
			{
				addMessageToChatWindow("Ошибка: файл %s.txt не найден в папке mod_sa\\Objects", A_Set.massobjname);
				A_Set.bMassHP = false;
				return;
			}
		}
	#pragma endregion
    #pragma region GiveGun
        if (A_Set.bGiveGuns)
        {
            static unsigned short sPlId = 0;
            static int iAmmo = 0;
            if (sPlId <= g_Players->ulMaxPlayerID)
            {
                if (!iAmmo)
                    iAmmo = A_Set.iAmmoCount;
                if (g_Players->iIsListed[sPlId] && g_Players->pRemotePlayer[sPlId]->pPlayerData->pSAMP_Actor != nullptr)
                {
                    if (iAmmo > 999)
                    {
                        say("/givegun %d %d 999", sPlId, A_Set.byteWeaponID);
                        iAmmo -= 999;
                    }
                    else
                    {
                        say("/givegun %d %d %d", sPlId, A_Set.byteWeaponID, iAmmo);
                        addMessageToChatWindow("Игроку %s[%d] выдано оружие", getPlayerName(sPlId), sPlId);
                        sPlId++;
                        iAmmo = A_Set.iAmmoCount;
                    }
                    timer = dwCurrentTime;
                    return;
                }
                else
                {
                    sPlId++;
                    iAmmo = A_Set.iAmmoCount;
                }
            }
            else
            {
                A_Set.bGiveGuns = false;
                sPlId = 0;
                iAmmo = 0;
                addMessageToChatWindow("Выдача оружия окончена");
                MessageBeep(MB_ICONEXCLAMATION);
            }
        }
    #pragma endregion
    #pragma region TpPlayers
        if (A_Set.bMassTP)
        {
            if (!A_Set.PlayersIDForTP.empty())
            {
                USHORT& sPlId = A_Set.PlayersIDForTP.back();
                if (sPlId <= g_Players->ulMaxPlayerID)
                {
                    say("/gethere %hu", sPlId);
                }
                A_Set.PlayersIDForTP.pop_back();
                timer = dwCurrentTime;
                return;
            }
            else
                if (!A_Set.usMaxPlayerTP)
                {
                    A_Set.bMassTP = false;
                    addMessageToChatWindow("Телепортирование завершено");
                }
        }
    #pragma endregion
    }

    #pragma region GunSkills
	if (A_Set.bSkillGun && !A_Set.bGiveGuns)
	{
		A_Set.byteSkillWeaponID++;
		switch (A_Set.byteSkillWeaponID)
		{
		case 0: A_Set.iAmmoCount = 5500; A_Set.byteWeaponID = 31; A_Set.bGiveGuns = true; break;
		case 1: A_Set.iAmmoCount = 3500; A_Set.byteWeaponID = 24; A_Set.bGiveGuns = true; break;
		case 2: A_Set.iAmmoCount = 3500; A_Set.byteWeaponID = 25; A_Set.bGiveGuns = true; break;
		case 3: A_Set.iAmmoCount = 5500; A_Set.byteWeaponID = 29; A_Set.bGiveGuns = true;
		default:
			A_Set.bSkillGun = false;
			A_Set.byteSkillWeaponID = 0;
		}
	}
    #pragma endregion

    if (A_Set.bTraces && !A_Set.Tracers.empty())
	{
        if ((dwCurrentTime - A_Set.Tracers.back().time) > A_Set.dwTraceTimer)
		{
			A_Set.Tracers.pop_back();
		}
	}
	if (KEYCOMBO_PRESSED(A_Set.keycombo[REPORTER].second)){
		if (A_Set.lastip == 0) return addMessageToChatWindow("Ошибка: последний IP не найден");

		say("/banip %s", A_Set.IP[1]);
		timer = dwCurrentTime;
		A_Set.AllIP = true;
		return;
	}

	if (KEYCOMBO_PRESSED(A_Set.keycombo[GETLASTIP].second)){
		if (A_Set.lastip == 0) return addMessageToChatWindow("Ошибка: последний IP не найден");

		say("/pgetip 4 %s", A_Set.IP[1]);
		return;
	}
	if (KEYCOMBO_PRESSED(A_Set.keycombo[IPOFFBAN].second)){
		if (A_Set.ipoffban == 0) return addMessageToChatWindow("Ошибка: последний заблокированный в оффлайне не найден");
		{
			say("/agetip %s", A_Set.banIP[1]);
			timer = dwCurrentTime;
			A_Set.offbanip = true;
		}
	}

	if (KEYCOMBO_PRESSED(A_Set.keycombo[GETSTATS].second)){

		if (g_Players->iIsListed[A_Set.reconID])
		{
			say("/getstats %d", A_Set.reconID);
			return;
		}
	}


	if (KEYCOMBO_PRESSED(A_Set.keycombo[RELASTWARN].second)){
		if (A_Set.warningvalid == 0) return addMessageToChatWindow("Ошибка: id игрока не найден");

		say("/re %d", A_Set.warningid);
		return;

	}

	if (KEYCOMBO_PRESSED(A_Set.keycombo[REPORTOUT].second)){
		if (A_Set.reportvalid == 0) return addMessageToChatWindow("Ошибка: последняя жалоба не найдена");

		say("/re %d", A_Set.reportid);
		return;
	}

	if (KEYCOMBO_PRESSED(A_Set.keycombo[GOTOSELF].second)){
		say("/goto %d", g_Players->sLocalPlayerID);
	}

    if (KEYCOMBO_PRESSED(A_Set.keycombo[TRACE].second)) {
        A_Set.bTraces ^= true;
		return;
    }

    if (KEY_DOWN(0x1)) {
        POINT cursorPos = CursorPos();
        static POINT offset, newPos, min = { 0, 0 }, max = { *(int*)0xC9C040, *(int*)0xC9C044 }, size;
        if ((cursorPos - offset) >= min && (cursorPos - offset) <= (max - size)) {
            size_t aCount = A_Set.AdminsOnline.size(), pCount = A_Set.PlayersOnline.size();

            if (cursorPos >= A_Set.aCheckPos && cursorPos <= (A_Set.aCheckPos + POINT{ long(pD3DFont->DrawLength("Нет админов в сети")), pD3DFont->DrawHeight() * (1 + (aCount == 0 ? 1 : aCount)) })) {
                if (KEY_PRESSED(0x1)) {
                    offset = cursorPos - A_Set.aCheckPos;
                    size.x = uint16_t(pD3DFont->DrawLength("Нет админов в сети"));
                    size.y = pD3DFont->DrawHeight() * (1 + (aCount == 0 ? 1 : aCount));
                }
                newPos = cursorPos - offset;
                if (A_Set.aCheckPos != newPos) {
                    A_Set.aCheckPos = newPos;
                    A_Ini.SetInt("Position", "AdminChecker_X", A_Set.aCheckPos.x);
                    A_Ini.SetInt("Position", "AdminChecker_Y", A_Set.aCheckPos.y);
                }
            }
            else {
                if (cursorPos >= A_Set.pCheckPos && cursorPos <= (A_Set.pCheckPos + POINT{ long(pD3DFont->DrawLength("Нет игроков в сети")), pD3DFont->DrawHeight() * (1 + (pCount == 0 ? 1 : pCount)) })) {
                    if (KEY_PRESSED(0x1)) {
                        offset = cursorPos - A_Set.pCheckPos;
                        size.x = uint16_t(pD3DFont->DrawLength("Нет игроков в сети"));
                        size.y = pD3DFont->DrawHeight() * (1 + (pCount == 0 ? 1 : pCount));
                    }
                    newPos = cursorPos - offset;
                    if (A_Set.pCheckPos != newPos) {
                        A_Set.pCheckPos = newPos;
                        A_Ini.SetInt("Position", "PlayerChecker_X", A_Set.pCheckPos.x);
                        A_Ini.SetInt("Position", "PlayerChecker_Y", A_Set.pCheckPos.y);
                    }
                }
                else {
                    if ((A_Set.bConnectLog || A_Set.bDisconnectLog) && (cursorPos >= A_Set.connectionPos && cursorPos <= (A_Set.connectionPos + POINT{ long(pD3DFont->DrawLength(" подключен к серверу") + 20), pD3DFont->DrawHeight() * 2 }))) {
                        if (KEY_PRESSED(0x1)) {
                            offset = cursorPos - A_Set.connectionPos;
                            size.x = uint16_t(pD3DFont->DrawLength(" подключен к серверу") + 20);
                            size.y = pD3DFont->DrawHeight() * 2;
                        }
                        newPos = cursorPos - offset;
                        if (A_Set.connectionPos != newPos) {
                            A_Set.connectionPos = newPos;
                            A_Ini.SetInt("Position", "Connection_X", A_Set.connectionPos.x);
                            A_Ini.SetInt("Position", "Connection_Y", A_Set.connectionPos.y);
                        }
                    }
                    else {
                        if (cursorPos >= (A_Set.killListPos - long(pD3DFont->DrawLength("D")) * 18) && cursorPos <= (A_Set.killListPos + POINT{ long(pD3DFont->DrawLength("D")) * 18, 24 * 5 })) {
                            if (KEY_PRESSED(0x1)) {
                                offset = cursorPos - A_Set.killListPos;
                                size.x = uint16_t(pD3DFont->DrawLength("D")) * 18;
                                size.y = 24 * 5;
                            }
                            newPos = cursorPos - offset;
                            if (A_Set.killListPos != newPos) {
                                A_Set.killListPos = newPos;
                                A_Ini.SetInt("Position", "KillList_X", A_Set.killListPos.x);
                                A_Ini.SetInt("Position", "KillList_Y", A_Set.killListPos.y);
                            }
                        }
                    }
                }
            }
        }
    }

    if (KEY_PRESSED('R')) {
        g_Input->iInputEnabled = 1;
        g_Input->pDXUTEditBox->bIsChatboxOpen = 1;
    }
}

void StringFind(char *string, char *search, char stop_symbol, char output[])
{
	char	*find = strstr(string, search);
	int		start_pos = strlen(search);
	int		pos;

	if (strstr(string, search))
	{
		for (pos = 0; pos < 100; pos++)
		{
			if (find[start_pos + pos] == stop_symbol)
				break;

			output[pos] = find[start_pos + pos];
		}

		output[pos] = '\0';
	}
	else
		strcpy(output, "");
}

void ResponsePasre(const std::string& resp, stIpInfo& IpInfo)
{
	traceLastFunc("RequestPasre()");
	Log(resp.c_str());
	size_t start = 9, end = resp.find('\"', start);
	IpInfo.City = resp.substr(start, end - start);
	start = end + 8;
	end = resp.find(',', start);
	IpInfo.pos[0] = std::stof(resp.substr(start, end - start));
	start = end + 7;
	end = resp.find(',', start);
	IpInfo.pos[1] = std::stof(resp.substr(start, end - start));
	start = end + 8;
	end = resp.find('\"', start);
	IpInfo.Provider = resp.substr(start, end - start);
}

void IpQuery(HINTERNET hSession, const std::string& ip_address, stIpInfo& IpInfo)
{
	traceLastFunc("IpQuery()");
	HINTERNET hURL = InternetOpenUrlA(hSession, ip_address.c_str(), nullptr, 0, 0, 0);
	if (hURL != nullptr)
	{
		DWORD dwSize = 0;
		InternetQueryDataAvailable(hURL, &dwSize, 0, 0);
		if (dwSize > 25)
		{
			try
			{
				char *szBuffer = new char[dwSize + 1];
				DWORD dwRead = 0;
				if (InternetReadFile(hURL, szBuffer, dwSize, &dwRead))
				{
					if (dwRead < dwSize)
						dwSize = dwRead;
					szBuffer[dwSize] = 0;
					ResponsePasre(szBuffer, IpInfo);
				}
				delete[] szBuffer;
			}
			catch (const std::bad_alloc &ex)
			{
				addMessageToChatWindow("Error mem alloc: %s", ex.what());
			}
		}
		InternetCloseHandle(hURL);
	}
}

void SravnenieIP(const std::string& reg_ip, const std::string& current_ip)
{
	if (!InternetCheckConnectionA("http://ip-api.com", FLAG_ICC_FORCE_CONNECTION, 0))
	{
		addMessageToChatWindow("Error connection");
		return;
	}

	HINTERNET hSession = InternetOpenA("SAMP STEALER", INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0);
	if (hSession != nullptr)
	{
		stIpInfo IpInfo[2];
		IpQuery(hSession, "http://ip-api.com/json/" + reg_ip + "?fields=city,lat,lon,org", IpInfo[0]);
		IpQuery(hSession, "http://ip-api.com/json/" + current_ip + "?fields=city,lat,lon,org", IpInfo[1]);
		addMessageToChatWindow("Reg City: %s | Current City: %s", IpInfo[0].City.c_str(), IpInfo[1].City.c_str());
		addMessageToChatWindow("Reg Provider: %s | Current Provider: %s", IpInfo[0].Provider.c_str(), IpInfo[1].Provider.c_str());
		addMessageToChatWindow("Distance: %.3f km", GeoDistance(IpInfo[0].pos, IpInfo[1].pos));
		InternetCloseHandle(hSession);
	}
}

void addAdminCommand(char *name, CMDPROC function)
{
	if (name == nullptr || function == nullptr || g_Input == nullptr)
		return;

	if (g_Input->iCMDCount == (SAMP_MAX_CLIENTCMDS - 1))
	{
		Log("Error: couldn't initialize '%s'. Maximum command amount reached.", name);
		return;
	}

	if (strlen(name) > 30)
	{
		Log("Error: command name '%s' was too long.", name);
		return;
	}

	if (g_m0dCmdNum < (SAMP_MAX_CLIENTCMDS - 22))
	{
		g_m0dCmdNum++;
	}
	else
		Log("m0d_cmd_list[] too short.");

	((void(__thiscall *) (void *_this, char *command, CMDPROC function)) (g_dwSAMP_Addr + SAMP_FUNC_ADDCLIENTCMD)) (g_Input, name, function);
}

void adminLog(FILE *fileLog, const char *fmt, ...)
{
    if (fileLog == nullptr)
        return;

    SYSTEMTIME	time;
    va_list		ap;

    GetLocalTime(&time);
    fprintf(fileLog, "[%02d-%02d-%02d || %02d:%02d:%02d.%03d] ", time.wDay, time.wMonth, time.wYear, time.wHour,
        time.wMinute, time.wSecond, time.wMilliseconds);
    va_start(ap, fmt);
    vfprintf(fileLog, fmt, ap);
    va_end(ap);
    fprintf(fileLog, "\n");
    fflush(fileLog);
}