#include "main.h"

void ACMD_MassHP(char *par)
{
	USHORT hp;
	if (sscanf_s(par, "%hu", &hp) < 0) return addMessageToChatWindow("Использование: /masshp [кол-во HP]");

	if (sscanf_s(par, "%hu", &hp) > 0)
	{
		if (hp > 0 && hp < 256)
		{
			A_Set.bMassHP = true;
			A_Set.iHpCount = hp;
			addMessageToChatWindow("Выдача HP начата");
			MessageBeep(MB_ICONEXCLAMATION);
		}
	}
}

void ACMD_ahelp(char *par)
{
		ShowLocalSampDialog(4, DialogStyle::DIALOG_STYLE_LIST, "Помощь по собейту", "Команды собейта\nКлавиши собейта\nКоманды администрации", "OK", "Cancel");
}

void ACMD_leader(char *par)
{
	if (sscanf(par, "%d", &A_Set.usSetLeaderID) == 1)
	{
		ShowLocalSampDialog(2, DialogStyle::DIALOG_STYLE_LIST, "Меню лидеров", "Снять с лидерства\nLSPD\nFBI\nLVa\nMOH\nLCN\nYakuza\nMayor\nRM\nSFn\nLSn\nInstrustors\nRifa\nGrove\nBallas\nVagos\nAztec\nSFPD\nLVPD\nSFa\nLVn\nHell Angel's MC\nMongols MC\nPagans MC\nOutlaws MC\nSon's Of Silence MC\nWarlocks MC\nHighwayman MC\nBandidos MC\nFreeSouls MC\nVagos MC", "OK", "Cancel");
	}
}

void ACMD_GiveGuns(char *par)
{
	USHORT ammo;
	BYTE weapon;
	if (sscanf_s(par, "%hhu %hu", &weapon, &ammo) < 0) return addMessageToChatWindow("Использование: /massw [id оружия][кол-во пуль]");

	if (sscanf_s(par, "%hhu %hu", &weapon, &ammo) > 1)
	{
		if (ammo > 0 && ammo < 30000 && weapon < 54)
		{
			A_Set.bGiveGuns = true;
			A_Set.byteWeaponID = weapon;
			A_Set.iAmmoCount = ammo;
			addMessageToChatWindow("Выдача оружия начата");
			MessageBeep(MB_ICONEXCLAMATION);
		}
	}
}

void ACMD_SkillGuns(char *par)
{
	addMessageToChatWindow("Выдача оружия на скиллы начата");
	A_Set.iAmmoCount = 5500; 
	A_Set.byteWeaponID = 31; 
	A_Set.bGiveGuns = true;
	A_Set.byteSkillWeaponID = 0;
	A_Set.bSkillGun = true;
	MessageBeep(MB_ICONEXCLAMATION);
}

void ACMD_PlayerTP(char *par)
{
	if (par[0] != 0)
	{
		USHORT maxPlayers = 0;
		if (sscanf_s(par, "%hu", &maxPlayers) && maxPlayers > 0 && maxPlayers <= g_Players->ulMaxPlayerID)
		{
			addMessageToChatWindow("Телепортирование %d игроков началось.", maxPlayers);
			A_Set.usMaxPlayerTP = maxPlayers;
			A_Set.bMassTP = true;
		}
		else
			addMessageToChatWindow("Ошибка параметров");
	}
}

void ACMD_gobj(char *par)
{
	int params = sscanf(par, "%s%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d", &A_Set.objname, &A_Set.ids[0], &A_Set.ids[1], &A_Set.ids[2], &A_Set.ids[3], &A_Set.ids[4],
		&A_Set.ids[5], &A_Set.ids[6], &A_Set.ids[7], &A_Set.ids[8], &A_Set.ids[9], &A_Set.ids[10], &A_Set.ids[11], &A_Set.ids[12], &A_Set.ids[13], &A_Set.ids[14]);

	if (A_Set.process != 0) return addMessageToChatWindow("Ошибка: процесс выдачи оружия/HP/объектов/телепортации/увольнения игроков уже запущен, дождитесь его завершения");

	if (params < 2)
	{
		addMessageToChatWindow("Использование: /gobj [название] [id'ы игроков]");
		addMessageToChatWindow("Пример: /gobj зомби 20 30 40 50");
		addMessageToChatWindow("Примечание: в названии пишем название текстового файла с объектами из папки mod_sa/Objects (без .txt)");
		addMessageToChatWindow("Примечание: максимальное кол-во игроков - 15");
		return;
	}

	A_Set.gplayercount = params - 1;
	A_Set.Gobj = true;
}

void ACMD_PlayerTPBreak(char *)
{
	A_Set.usMaxPlayerTP = 0;
	A_Set.bMassTP = false;
	A_Set.PlayersIDForTP.clear();
	addMessageToChatWindow("Телепортирование прекращено");
}

void ACMD_IpInfo(char *par)
{
    if (par[0] != 0)
	{
		USHORT Id = 0;
		if (sscanf_s(par, "%hu", &Id))
		{
			say("/getip %d", Id);
		}
		else
			say("/agetip %s", par);
		A_Set.bIpInfo = true;
	}
}

void ACMD_trace(char *par)
{
	if (par[0] < 1)
	{
		addMessageToChatWindow("Использование: /tr [параметр]");
		addMessageToChatWindow("Параметр: ид игрока - будут выводится только трейсеры пуль выбранного игрока");
		addMessageToChatWindow("Параметр: all - будут выводиться трейсеры пуль всех игроков в зоне прорисовки");
		addMessageToChatWindow("Параметр: clear - очистка трейсеров, все существующие трейсеры будут уничтожены");
		addMessageToChatWindow("Параметр: on / off - включение/отключение трейсеров пуль (установленные параметры сохраняются после отключения)");
		return;
	}

    if (par[0] != 0)
	{
		if (!strncmp(par, "all", 3))
		{
			A_Set.bTraceAll = true;
			addMessageToChatWindow("[Трейсеры]: Включены для всех игроков.");
		}
		else
		{
			USHORT pID;
			if (sscanf_s(par, "%hu", &pID) && pID <= g_Players->ulMaxPlayerID)
			{
				A_Set.bTraceAll = false;
				A_Set.usTraceID = pID;
				addMessageToChatWindow("[Трейсеры]: Включены для игрока с %d ID", pID);
			}
		}
        A_Set.bTraces = true;
	}
	else
	{
        A_Set.bTraces ^= true;
        addMessageToChatWindow("[Трейсеры]: %s", A_Set.bTraces ? "Включены" : "Выключены");
		if (!A_Set.bTraces)
		{
			A_Set.Tracers.clear();
		}
	}
}

void ACMD_ranks(char *param)
{
	if (strlen(param) < 1)
	{
		addMessageToChatWindow("/ranks [название фракции]");
		addMessageToChatWindow("Фракции: PD, Army, FBI, Medic, Instr, News");
		addMessageToChatWindow("Фракции: Bikers, LCN, Yakuza, RM, Rifa, Grove, Ballas, Vagos, Aztec");
		return;
	}

	if (strcmpi(param, "PD") == 0)
	{
		addMessageToChatWindow("{FFFF00}Ранги полиции:");
		addMessageToChatWindow("1 ранг - Кадет");
		addMessageToChatWindow("2 ранг - Офицер");
		addMessageToChatWindow("3 ранг - Мл.Сержант");
		addMessageToChatWindow("4 ранг - Сержант");
		addMessageToChatWindow("5 ранг - Прапорщик");
		addMessageToChatWindow("6 ранг - Ст.Прапорщик");
		addMessageToChatWindow("7 ранг - Мл.Лейтенант");
		addMessageToChatWindow("8 ранг - Лейтенант");
		addMessageToChatWindow("9 ранг - Ст.Лейтенант");
		addMessageToChatWindow("10 ранг - Капитан");
		addMessageToChatWindow("11 ранг - Майор");
		addMessageToChatWindow("12 ранг - Подполковник");
		addMessageToChatWindow("13 ранг - Полковник");
		addMessageToChatWindow("Лидер - Шериф");
	}
	else if (strcmpi(param, "Army") == 0)
	{
		addMessageToChatWindow("{FFFF00}Ранги армии:");
		addMessageToChatWindow("1 ранг - Рядовой");
		addMessageToChatWindow("2 ранг - Ефрейтор");
		addMessageToChatWindow("3 ранг - Мл.Сержант");
		addMessageToChatWindow("4 ранг - Сержант");
		addMessageToChatWindow("5 ранг - Ст. Сержант");
		addMessageToChatWindow("6 ранг - Старшина");
		addMessageToChatWindow("7 ранг - Прапорщик");
		addMessageToChatWindow("8 ранг - Мл.Лейтенант");
		addMessageToChatWindow("9 ранг - Лейтенант");
		addMessageToChatWindow("10 ранг - Ст.Лейтенант");
		addMessageToChatWindow("11 ранг - Капитан");
		addMessageToChatWindow("12 ранг - Майор");
		addMessageToChatWindow("13 ранг - Подполковник");
		addMessageToChatWindow("14 ранг - Полковник");
		addMessageToChatWindow("Лидер - Генерал");
	}
	else if (strcmpi(param, "FBI") == 0)
	{
		addMessageToChatWindow("{FFFF00}Ранги ФБР:");
		addMessageToChatWindow("1 ранг - Стажер");
		addMessageToChatWindow("2 ранг - Дежурный");
		addMessageToChatWindow("3 ранг - Младший агент");
		addMessageToChatWindow("4 ранг - Агент GNK");
		addMessageToChatWindow("5 ранг - Агент CID");
		addMessageToChatWindow("6 ранг - Глава GNK");
		addMessageToChatWindow("7 ранг - Глава CID");
		addMessageToChatWindow("8 ранг - Инспектор");
		addMessageToChatWindow("9 ранг - Зам. Директора");
		addMessageToChatWindow("Лидер - Директор");
	}
	else if (strcmpi(param, "Medic") == 0)
	{
		addMessageToChatWindow("{FFFF00}Ранги медиков:");
		addMessageToChatWindow("1 ранг - Интерн");
		addMessageToChatWindow("2 ранг - Санитар");
		addMessageToChatWindow("3 ранг - Мед. брат");
		addMessageToChatWindow("4 ранг - Спасатель");
		addMessageToChatWindow("5 ранг - Нарколог");
		addMessageToChatWindow("6 ранг - Доктор");
		addMessageToChatWindow("7 ранг - Психолог");
		addMessageToChatWindow("8 ранг - Хирург");
		addMessageToChatWindow("9 ранг - Зам. глав. врача");
		addMessageToChatWindow("Лидер - Глав. врач");
	}
	else if (strcmpi(param, "Instr") == 0)
	{
		addMessageToChatWindow("{FFFF00}Ранги инструкторов:");
		addMessageToChatWindow("1 ранг - Стажер");
		addMessageToChatWindow("2 ранг - Консультант");
		addMessageToChatWindow("3 ранг - Экзаменатор");
		addMessageToChatWindow("4 ранг - Мл.Инструктор");
		addMessageToChatWindow("5 ранг - Инструктор");
		addMessageToChatWindow("6 ранг - Координатор");
		addMessageToChatWindow("7 ранг - Мл. менеджер");
		addMessageToChatWindow("8 ранг - Ст. менеджер");
		addMessageToChatWindow("9 ранг - Директор");
		addMessageToChatWindow("Лидер - Управляющий");
	}
	else if (strcmpi(param, "News") == 0)
	{
		addMessageToChatWindow("{FFFF00}Ранги новостей:");
		addMessageToChatWindow("1 ранг - Стажер");
		addMessageToChatWindow("2 ранг - Звукооператор");
		addMessageToChatWindow("3 ранг - Репортер");
		addMessageToChatWindow("4 ранг - Режисер");
		addMessageToChatWindow("5 ранг - Ведущий");
		addMessageToChatWindow("6 ранг - Редактор");
		addMessageToChatWindow("7 ранг - Гл. редактор");
		addMessageToChatWindow("8 ранг - Тех. директор");
		addMessageToChatWindow("9 ранг - Програмный директор");
		addMessageToChatWindow("Лидер - Директор");
	}
	else if (strcmpi(param, "Bikers") == 0)
	{
		addMessageToChatWindow("{FFFF00}Ранги новостей:");
		addMessageToChatWindow("1 ранг - Support");
		addMessageToChatWindow("2 ранг - Hang around");
		addMessageToChatWindow("3 ранг - Prospect");
		addMessageToChatWindow("4 ранг - Member");
		addMessageToChatWindow("5 ранг - Road capitain");
		addMessageToChatWindow("6 ранг - Sergeant-at-arms");
		addMessageToChatWindow("7 ранг - Treasurer");
		addMessageToChatWindow("8 ранг - Вице президент");
		addMessageToChatWindow("Лидер - Президент");
	}
	else if (strcmpi(param, "LCN") == 0)
	{
		addMessageToChatWindow("{FFFF00}Ранги LCN:");
		addMessageToChatWindow("1 ранг - Новицио");
		addMessageToChatWindow("2 ранг - Ассоциато");
		addMessageToChatWindow("3 ранг - Сомбаттенте");
		addMessageToChatWindow("4 ранг - Солдато");
		addMessageToChatWindow("5 ранг - Боец");
		addMessageToChatWindow("6 ранг - Сотто капо");
		addMessageToChatWindow("7 ранг - Капо");
		addMessageToChatWindow("8 ранг - Младший босс");
		addMessageToChatWindow("9 ранг - Консильере");
		addMessageToChatWindow("Лидер - Дон");
	}
	else if (strcmpi(param, "Yakuza") == 0)
	{
		addMessageToChatWindow("{FFFF00}Ранги Yakuza:");
		addMessageToChatWindow("1 ранг - Вакасю");
		addMessageToChatWindow("2 ранг - Сятэй");
		addMessageToChatWindow("3 ранг - Кёдай");
		addMessageToChatWindow("4 ранг - Фуку-хомбуте");
		addMessageToChatWindow("5 ранг - Вакагасира");
		addMessageToChatWindow("6 ранг - Со-хомбуте");
		addMessageToChatWindow("7 ранг - Камбу");
		addMessageToChatWindow("8 ранг - Сайко-комон");
		addMessageToChatWindow("9 ранг - Оядзи");
		addMessageToChatWindow("Лидер - Кумите");
	}
	else if (strcmpi(param, "RM") == 0)
	{
		addMessageToChatWindow("{FFFF00}Ранги Russian Mafia:");
		addMessageToChatWindow("1 ранг - Шнырь");
		addMessageToChatWindow("2 ранг - Фраер");
		addMessageToChatWindow("3 ранг - Бык");
		addMessageToChatWindow("4 ранг - Барыга");
		addMessageToChatWindow("5 ранг - Блатной");
		addMessageToChatWindow("6 ранг - Свояк");
		addMessageToChatWindow("7 ранг - Браток");
		addMessageToChatWindow("8 ранг - Вор");
		addMessageToChatWindow("9 ранг - Вор в законе");
		addMessageToChatWindow("Лидер - Авторитет");
	}
	else if (strcmpi(param, "Rifa") == 0)
	{
		addMessageToChatWindow("{FFFF00}Ранги Rifa:");
		addMessageToChatWindow("1 ранг - Ладрон");
		addMessageToChatWindow("2 ранг - Новато");
		addMessageToChatWindow("3 ранг - Амиго");
		addMessageToChatWindow("4 ранг - Мачо");
		addMessageToChatWindow("5 ранг - Джуниор");
		addMessageToChatWindow("6 ранг - Эрмано");
		addMessageToChatWindow("7 ранг - Бандидо");
		addMessageToChatWindow("8 ранг - Ауторидид");
		addMessageToChatWindow("9 ранг - Аджунто");
		addMessageToChatWindow("Лидер - Падре");
	}
	else if (strcmpi(param, "Grove") == 0)
	{
		addMessageToChatWindow("{FFFF00}Ранги Grove:");
		addMessageToChatWindow("1 ранг - Плэйя");
		addMessageToChatWindow("2 ранг - Хастла");
		addMessageToChatWindow("3 ранг - Килла");
		addMessageToChatWindow("4 ранг - Юонг Г");
		addMessageToChatWindow("5 ранг - Гангста");
		addMessageToChatWindow("6 ранг - О. Г.");
		addMessageToChatWindow("7 ранг - Мобста");
		addMessageToChatWindow("8 ранг - Де кинг");
		addMessageToChatWindow("9 ранг - Легенд");
		addMessageToChatWindow("Лидер - Мэд дог");
	}
	else if (strcmpi(param, "Ballas") == 0)
	{
		addMessageToChatWindow("{FFFF00}Ранги Ballas:");
		addMessageToChatWindow("1 ранг - Блайд");
		addMessageToChatWindow("2 ранг - Бастер");
		addMessageToChatWindow("3 ранг - Крэкер");
		addMessageToChatWindow("4 ранг - Гун бро");
		addMessageToChatWindow("5 ранг - Ап бро");
		addMessageToChatWindow("6 ранг - Гангстер");
		addMessageToChatWindow("7 ранг - Федерал блок");
		addMessageToChatWindow("8 ранг - Фолкс");
		addMessageToChatWindow("9 ранг - Райч нигга");
		addMessageToChatWindow("Лидер - Биг вилли");
	}
	else if (strcmpi(param, "Vagos") == 0)
	{
		addMessageToChatWindow("{FFFF00}Ранги Vagos:");
		addMessageToChatWindow("1 ранг - Новито");
		addMessageToChatWindow("2 ранг - Ординарио");
		addMessageToChatWindow("3 ранг - Локал");
		addMessageToChatWindow("4 ранг - Верификадо");
		addMessageToChatWindow("5 ранг - Бандито");
		addMessageToChatWindow("6 ранг - V.E.G.");
		addMessageToChatWindow("7 ранг - Ассесино");
		addMessageToChatWindow("8 ранг - Лидер V.E.G");
		addMessageToChatWindow("9 ранг - Падрино");
		addMessageToChatWindow("Лидер - Падре");
	}
	else if (strcmpi(param, "Aztec") == 0)
	{
		addMessageToChatWindow("{FFFF00}Ранги Aztec:");
		addMessageToChatWindow("1 ранг - Перро");
		addMessageToChatWindow("2 ранг - Тирадор");
		addMessageToChatWindow("3 ранг - Геттор");
		addMessageToChatWindow("4 ранг - Лас Геррас");
		addMessageToChatWindow("5 ранг - Мириндо");
		addMessageToChatWindow("6 ранг - Сабио");
		addMessageToChatWindow("7 ранг - Инвасор");
		addMessageToChatWindow("8 ранг - Тесореро");
		addMessageToChatWindow("9 ранг - Нестро");
		addMessageToChatWindow("Лидер - Падре");
	}
	else
		addMessageToChatWindow("Ошибка: \"%s\" не найдено в списке фракций", param);

	return;
}

void ACMD_changeKeyCombo(char *par)
{
    if (par != nullptr) {
        uint8_t tId;
        if (sscanf_s(par, "%hhu", &tId) == 1) {
            if (tId < A_Set.keycombo.size()) {
                parAdminSetting.keycomboId = tId;
                if (hhKeyKook == nullptr)
                {
                    hhKeyKook = SetWindowsHookExA(WH_KEYBOARD_LL, LLKeyProc, NULL, 0);
                    if (hhKeyKook == nullptr)
                        return addMessageToChatWindow("[!!!] Error set hook 0xX", GetLastError());
                }
                addMessageToChatWindow("Вы устанавливаете новые клавиши для \"%s\". Для завершения установки бинда нажмите ESC или ENTER.", A_Set.keycombo[tId].first.c_str());
                addMessageToChatWindow("Текущий бинд: \"%s\"", keycombo2String(A_Set.keycombo[tId].second).c_str());
            }
            else {
                addMessageToChatWindow("Выход за пределы!");
            }
        }
        else {
            addMessageToChatWindow("/changekey [index]");
        }
    }
}

void ACMD_SaveGangZones(char *param)
{
    if (param[0] == 0) {
        param = "gangs.log";
    }
    addMessageToChatWindow("Сохраняем данные в файл \"%s\"", param);
    FILE *fGangLog = fopen((".\\" M0D_FOLDER "gangZones\\" + std::string(param)).c_str(), "w");
    if (fGangLog) {
        for (short index = 0; index <= 129; ++index) {
            if (g_SAMP->pPools->pGangzone->iIsListed[index]) {
                auto zone = g_SAMP->pPools->pGangzone->pGangzone[index];
                //fprintf_s(fGangLog, "%.1f\t%.1f\t%.1f\t%.1f\t%08X\n", zone->fPosition[0], zone->fPosition[1], zone->fPosition[2], zone->fPosition[3], zone->dwColor);
                fprintf_s(fGangLog, "%08X\n", zone->dwColor);//??можно и без позиций
            }
        }
        SYSTEMTIME	time;
        GetLocalTime(&time);
        fprintf(fGangLog, "[%02d-%02d-%02d | %02d:%02d]", time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute);
        fclose(fGangLog);
    }
    else {
        addMessageToChatWindow("Ошибка записи");
    }
}

#include <fstream>
void ACMD_CompareGangZones(char *param)
{
    if (param[0] == 0) {
        param = "gangs.log";
    }
    addMessageToChatWindow("Берём данные из файла \"%s\"", param);
    std::ifstream fGangLog(".\\" M0D_FOLDER "gangZones\\" + std::string(param));
    if (fGangLog.is_open()) {
        int id = 0;
        bool flag = false;
        std::string line;
        while (std::getline(fGangLog, line) && id < 130) {
            if (g_SAMP->pPools->pGangzone->iIsListed[id]) {
                DWORD color;
                if (sscanf_s(line.c_str(), "%8X", &color)) {
                    if (color != g_SAMP->pPools->pGangzone->pGangzone[id]->dwColor) {
                        flag = true;
                        g_SAMP->pPools->pGangzone->pGangzone[id]->dwAltColor = color | 0xF6000000;
                    }
                }
            }
            ++id;
        }
        if (line[0] == '[' && line.back() == ']') {
            addMessageToChatWindow("Данные файла актуальны на: %s", line.c_str());
        }
        if (flag)
            addMessageToChatWindow("Есть различия в зонах, они отображены на карте!");
        else
            addMessageToChatWindow("Зоны идентичны!");
        fGangLog.close();
    }
    else {
        addMessageToChatWindow("Файл \"%s\" не может быть открыт", param);
    }
}

void ACMD_clearDifferenceGangZones(char*)
{
    for (short index = 0; index <= 129; ++index) {
        if (g_SAMP->pPools->pGangzone->iIsListed[index]) {
            auto zone = g_SAMP->pPools->pGangzone->pGangzone[index];
            if (zone->dwColor != zone->dwAltColor)
                zone->dwAltColor = zone->dwColor;
        }
    }
    addMessageToChatWindow("Отображение различий убрано с карты");
}

void ACMD_changeFontName(char*)
{
    ShowLocalSampDialog(523, DIALOG_STYLE_INPUT, "Изменение фона", "Введите имя шрифта, который вы хотите установить", "Save", "Cancel");
}

void adminFunctions_cmds()
{
	addAdminCommand("masshp", ACMD_MassHP);
	addAdminCommand("leader", ACMD_leader);
	addAdminCommand("gobj", ACMD_gobj);
	addAdminCommand("ahelp", ACMD_ahelp);
	addAdminCommand("massw", ACMD_GiveGuns);
	addAdminCommand("ranks", ACMD_ranks);
	addAdminCommand("skill", ACMD_SkillGuns);
	addAdminCommand("starttp", ACMD_PlayerTP);
	addAdminCommand("iip", ACMD_IpInfo);
	addAdminCommand("tr", ACMD_trace);
	addAdminCommand("endtp", ACMD_PlayerTPBreak);
    addAdminCommand("changekey", ACMD_changeKeyCombo);
    addAdminCommand("savegz", ACMD_SaveGangZones);
    addAdminCommand("cmpgz", ACMD_CompareGangZones);
    addAdminCommand("clrgz", ACMD_clearDifferenceGangZones);
    addAdminCommand("setfont", ACMD_changeFontName);
}