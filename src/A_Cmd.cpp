#include "main.h"

#include <wininet.h>
#include <vector>  

#pragma comment ( lib, "Wininet.lib" )

struct vehiclesGTA
{
	char	*name;
	int		id;
};

static struct vehiclesGTA vehs[] =
{
	{ "Landstalker", 400 },
	{ "Bravura", 401 },
	{ "Buffalo", 402 },
	{ "Linerunner", 403 },
	{ "Perenniel", 404 },
	{ "Sentinel", 405 },
	{ "Dumper", 406 },
	{ "Firetruck", 407 },
	{ "Trashmaster", 408 },
	{ "Stretch", 409 },
	{ "Manana", 410 },
	{ "Infernus", 411 },
	{ "Vodoo", 412 },
	{ "Pony", 413 },
	{ "Mule", 414 },
	{ "Cheetah", 415 },
	{ "Ambulance", 416 },
	{ "Levetian", 417 },
	{ "Moonbeam", 418 },
	{ "Esperanto", 419 },
	{ "Taxi", 420 },
	{ "Washington", 421 },
	{ "Bobcat", 422 },
	{ "Mr. Whoopee", 423 },
	{ "BF Injection", 424 },
	{ "Hunter", 425 },
	{ "Premier", 426 },
	{ "Enforcer", 427 },
	{ "Securicar", 428 },
	{ "Banshee", 429 },
	{ "Predator", 430 },
	{ "Bus", 431 },
	{ "Rhino", 432 },
	{ "Barracks", 433 },
	{ "Hotknife", 434 },
	{ "Artic Trailer", 435 },
	{ "Previon", 436 },
	{ "Coach", 437 },
	{ "Cabbie", 438 },
	{ "Stallion", 439 },
	{ "Rumpo", 440 },
	{ "RC Bandit", 441 },
	{ "Romero", 442 },
	{ "Packer", 443 },
	{ "Monster", 444 },
	{ "Admiral", 445 },
	{ "Squalo", 446 },
	{ "Seasparrow", 447 },
	{ "Pizza Boy", 448 },
	{ "Tram", 449 },
	{ "Artic Trailer 2", 450 },
	{ "Turismo", 451 },
	{ "Spider", 452 },
	{ "Reefer", 453 },
	{ "Tropic", 454 },
	{ "Flatbed", 455 },
	{ "Yankee", 456 },
	{ "Caddy", 457 },
	{ "Solair", 458 },
	{ "Top Fun", 459 },
	{ "Skimmer", 460 },
	{ "PCJ-600", 461 },
	{ "Faggio", 462 },
	{ "Freeway", 463 },
	{ "RC Baron", 464 },
	{ "RC Raider", 465 },
	{ "Glendale", 466 },
	{ "Oceanic", 467 },
	{ "Sanchez", 468 },
	{ "Sparrow", 469 },
	{ "Patriot", 470 },
	{ "Quad", 471 },
	{ "Costguard", 472 },
	{ "Dighy", 473 },
	{ "Hermes", 474 },
	{ "Sabre", 475 },
	{ "Rustler", 476 },
	{ "ZR-350", 477 },
	{ "Walton", 478 },
	{ "Regina", 479 },
	{ "Comet", 480 },
	{ "BMX", 481 },
	{ "Burrito", 482 },
	{ "Camper", 483 },
	{ "Marquis", 484 },
	{ "Baggage", 485 },
	{ "Dozer", 486 },
	{ "Maverick", 487 },
	{ "SAN Maverick", 488 },
	{ "Rancher", 489 },
	{ "FBI Rancher", 490 },
	{ "Virgo", 491 },
	{ "Greenwood", 492 },
	{ "Jetmax", 493 },
	{ "Hotring", 494 },
	{ "Sandking", 495 },
	{ "Blista Compact", 496 },
	{ "Police Maverick", 497 },
	{ "Boxville", 498 },
	{ "Benson", 499 },
	{ "Mesa", 500 },
	{ "RC Goblin", 501 },
	{ "Hotring A", 502 },
	{ "Hotring B", 503 },
	{ "Bloodring Banger", 504 },
	{ "Rancher (lure)", 505 },
	{ "Super GT", 506 },
	{ "Elegant", 507 },
	{ "Journey", 508 },
	{ "Bike", 509 },
	{ "Mountain bike", 510 },
	{ "Beagle", 511 },
	{ "Cropduster", 512 },
	{ "Stuntplane", 513 },
	{ "Petrol", 514 },
	{ "Roadtrain", 515 },
	{ "Nebula", 516 },
	{ "Majestic", 517 },
	{ "Buccaneer", 518 },
	{ "Shamal", 519 },
	{ "Hydra", 520 },
	{ "FCR-900", 521 },
	{ "NRG-500", 522 },
	{ "HPV-1000", 523 },
	{ "Cement Truck", 524 },
	{ "TowTruck", 525 },
	{ "Fortune", 526 },
	{ "Cardona", 527 },
	{ "FBI Truck", 528 },
	{ "Williard", 529 },
	{ "Forklift", 530 },
	{ "Tractor", 531 },
	{ "Combine", 532 },
	{ "Feltzer", 533 },
	{ "Remington", 534 },
	{ "Slamvan", 535 },
	{ "Blade", 536 },
	{ "Freight", 537 },
	{ "Streak", 538 },
	{ "Vortex", 539 },
	{ "Vincent", 540 },
	{ "Bullet", 541 },
	{ "Clover", 542 },
	{ "Sadler", 543 },
	{ "Firetruck LS", 544 },
	{ "Hustler", 545 },
	{ "Intruder", 546 },
	{ "Primo", 547 },
	{ "Cargobob", 548 },
	{ "Tampa", 549 },
	{ "Sunrise", 550 },
	{ "Merit", 551 },
	{ "Utility Van", 552 },
	{ "Nevada", 553 },
	{ "Yosemite", 554 },
	{ "Windsor", 555 },
	{ "Monster A", 556 },
	{ "Monster B", 557 },
	{ "Uranus", 558 },
	{ "Jester", 559 },
	{ "Sultan", 560 },
	{ "Stratum", 561 },
	{ "Elegy", 562 },
	{ "Raindance", 563 },
	{ "RC Tiger", 564 },
	{ "Flash", 565 },
	{ "Tahoma", 566 },
	{ "Savanna", 567 },
	{ "Bandito", 568 },
	{ "Freight Flat", 569 },
	{ "Streak", 570 },
	{ "Kart", 571 },
	{ "Mower", 572 },
	{ "Duneride", 573 },
	{ "Sweeper", 574 },
	{ "Broadway", 575 },
	{ "Tornado", 576 },
	{ "AT-400", 577 },
	{ "DFT-30", 578 },
	{ "Huntley", 579 },
	{ "Stafford", 580 },
	{ "BF-400", 581 },
	{ "Newsvan", 582 },
	{ "Tug", 583 },
	{ "Petrol Tanker", 584 },
	{ "Emperor", 585 },
	{ "Wayfarer", 586 },
	{ "Euros", 587 },
	{ "Hotdog", 588 },
	{ "Club", 589 },
	{ "Foreight Box", 590 },
	{ "Artic Trailer", 591 },
	{ "Andromada", 592 },
	{ "Dodo", 593 },
	{ "RC Cam", 594 },
	{ "Launch", 595 },
	{ "Cop Car LS", 596 },
	{ "Cop Car SF", 597 },
	{ "Cop Car LV", 598 },
	{ "Ranger", 599 },
	{ "Picador", 600 },
	{ "SwatTank", 601 },
	{ "Alpha", 602 },
	{ "Phoenix", 603 },
	{ "Glendale (damaged)", 604 },
	{ "Sadler (damaged)", 605 },
	{ "Bag Box A", 606 },
	{ "Bag Box B", 607 },
	{ "Stairs", 608 },
	{ "Boxville (black)", 609 },
	{ "Farm Trailer", 610 },
	{ "Utility Trailer", 611 },
	{ NULL, -1 }
};


void ACMD_MassHP(char *par)
{
	USHORT hp;
	int		p = 0;
	int		player_count = 0;
	if (sscanf_s(par, "%hu", &hp) < 0) return addMessageToChatWindow("Использование: /masshp [кол-во HP]");

	if (sscanf_s(par, "%hu", &hp) > 0)
	{
		if (hp > 0 && hp < 256)
		{
			A_Set.bMassHP = true;
			A_Set.iHpCount = hp;
			A_Set.process = 4;
			addMessageToChatWindow("Выдача HP начата");
			MessageBeep(MB_ICONEXCLAMATION);
		}
	}
}

void ACMD_ahelp(char *par)
{
		ShowLocalSampDialog(4, DialogStyle::DIALOG_STYLE_LIST, "Помощь по собейту", "Команды собейта\nКлавиши собейта\nКоманды администрации\nИнформация об обновлениях", "OK", "Cancel");
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
	if (sscanf_s(par, "%hhu %hu", &weapon, &ammo) < 0) return addMessageToChatWindow("Использование: /massgun [id оружия][кол-во пуль]");

	if (sscanf_s(par, "%hhu %hu", &weapon, &ammo) > 1)
	{
		if (ammo > 0 && ammo < 30000 && weapon < 54)
		{
			A_Set.bGiveGuns = true;
			A_Set.byteWeaponID = weapon;
			A_Set.iAmmoCount = ammo;
			A_Set.process = 4;
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

void massobj()
{
	char	filename[MAX_PATH];
	FILE	*file;
	int		p, j, lines = 0;
	int		player[1004];
	int		player_count = 0;
	float	pos[3];
	char	arr[100], content[100][100];

	snprintf(filename, sizeof(filename), "%s\\mod_sa\\Objects\\%s.txt", g_szWorkingDirectory, A_Set.massobjname);
	file = fopen(filename, "r");

	for (p = 0; p < SAMP_MAX_PLAYERS; p++)
	{
		if (!g_Players->iIsListed[p])
			continue;

		if (!getPlayerPos(p, pos))
			continue;

		player[player_count] = p;
		player_count++;
	}

	if (player_count > 0)
	{
		A_Set.mass_players_left = player_count;

		if (file)
		{
			for (j = 0; fgets(arr, 100, file) != NULL; j++)
			{
				strcpy(content[j], arr);
				lines++;
			}

			fclose(file);

			A_Set.process = 4;
			addMessageToChatWindow("Выдача объектов начата");
			MessageBeep(MB_ICONEXCLAMATION);

			for (p = 0; p < player_count; p++)
			{
				if (A_Set.process == 0)
					break;

				for (j = 0; j < lines; j++)
				{
					if (A_Set.process == 0)
						break;

					say("/hbject %d %s", player[p], content[j]);
					Sleep(1150);
				}
				addMessageToChatWindow("Игроку %s[%d] выдан комплект объектов \"%s\"", getPlayerName(player[p]), player[p], A_Set.massobjname);
				A_Set.mass_players_left--;
				Sleep(1150);
			}

			A_Set.process = 0;
			addMessageToChatWindow("Выдача объектов окончена");
			MessageBeep(MB_ICONEXCLAMATION);
		}
		else
			addMessageToChatWindow("Ошибка: файл %s.txt не найден в папке mod_sa\\Objects", A_Set.massobjname);
	}
	else
		addMessageToChatWindow("Ошибка: в зоне прорисовки не найдено ни одного игрока");

	ExitThread(0);
}

void ACMD_massobj(char *param)
{
	if (A_Set.process != 0) return addMessageToChatWindow("Ошибка: процесс выдачи оружия/HP/объектов/телепортации/увольнения игроков уже запущен, дождитесь его завершения");

	if (sscanf(param, "%s", &A_Set.massobjname) < 1)
	{
		addMessageToChatWindow("Использование: /massobj [название]");
		addMessageToChatWindow("Примечание: в названии пишем название текстового файла с объектами из папки mod_sa/Objects (без .txt)");
		addMessageToChatWindow("Пример: /massobj зомби");
		return;
	}

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)massobj, 0, 0, 0);
}

void ACMD_stop(char *param)
{
	if (A_Set.process == 0) return addMessageToChatWindow("Ошибка: на данный момент нет активных процессов");

	if (A_Set.process != 0)
	{
		A_Set.process = 0;
	}
	return;
}


void ACMD_PlayerTPBreak(char *)
{
	A_Set.usMaxPlayerTP = 0;
	A_Set.bMassTP = false;
	A_Set.PlayersIDForTP.clear();
	addMessageToChatWindow("Телепортирование прекращено");
}

void ACMD_astats(char *param)
{
	int ID;
	if (sscanf(param, "%d", &ID) < 1)
	{
		addMessageToChatWindow("Использование: /astats [id игрока]");
		addMessageToChatWindow("Будет показан agetstats (оффлайн статистика) игрока с указанным id");
		return;
	}

	say("/agetstats %s", getPlayerName(ID));
}

void ACMD_IpInfo(char *par)
{
	char nickname[30];
	if (sscanf(par, "%s%d", &nickname, &A_Set.Vivod) < 1)
	{
		addMessageToChatWindow("Использование: /ip [id или Nick_Name] [место вывода результатов проверки]");
		addMessageToChatWindow("Место вывода: 1 - в чат");
		addMessageToChatWindow("Место вывода: 2 - в админ чат");
		return;
	}
	
	if (strlen(nickname) > 3)
	{
		say("/agetip %s", &nickname);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SravnenieIP, 0, 0, 0);
	}
	else
	{
		say("/getip %s", &nickname);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SravnenieIP, 0, 0, 0);
	}
}


void ACMD_trace(char *par)
{
	if (par[0] < 1)
	{
		addMessageToChatWindow("Использование: /tr [параметр]");
		addMessageToChatWindow("Параметр: id игрока - будут выводится только трейсеры пуль выбранного игрока");
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
		else if (!strncmp(par, "off", 3))
		{
			A_Set.Tracers.clear();
			A_Set.bTraces = false;
			addMessageToChatWindow("[Трейсеры]: Выключены.");
		}
		else if (!strncmp(par, "on", 2))
		{
			A_Set.bTraces = true;
			addMessageToChatWindow("[Трейсеры]: Включены.");
		}
		else if (!strncmp(par, "clear", 5))
		{
			A_Set.Tracers.clear();
			addMessageToChatWindow("[Трейсеры]: Все трейсеры были удалены.");
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
	}
}

void gobj()
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
			if (A_Set.process == 0)
				break;

			for (j = 0; j < lines; j++)
			{
				if (A_Set.process == 0)
					break;

				say("/hbject %d %s", A_Set.ids[i], content[j]);
				Sleep(1150);
			}
			addMessageToChatWindow("Игроку %s[%d] выдан комплект объектов \"%s\"", getPlayerName(A_Set.ids[i]), A_Set.ids[i], A_Set.objname);
			A_Set.players_left--;
			Sleep(1150);
		}

		A_Set.process = 0;
		addMessageToChatWindow("Выдача объектов окончена");
		MessageBeep(MB_ICONEXCLAMATION);
		memset(A_Set.ids, 0, sizeof(A_Set.ids));
	}
	else
		addMessageToChatWindow("Ошибка: файл %s.txt не найден в папке mod_sa\\Objects", A_Set.massobjname);

	ExitThread(0);
}

void ACMD_gobj(char *param)
{
	int params = sscanf(param, "%s%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d", &A_Set.objname, &A_Set.ids[0], &A_Set.ids[1], &A_Set.ids[2], &A_Set.ids[3], &A_Set.ids[4],
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
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)gobj, 0, 0, 0);
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

void ghp()
{
	A_Set.process = 1;
	addMessageToChatWindow("Выдача HP начата");
	MessageBeep(MB_ICONEXCLAMATION);

	A_Set.players_left = A_Set.gplayercount;

	for (int i = 0; i < A_Set.gplayercount; i++)
	{
		if (A_Set.process == 0)
			break;

		say("/sethp %d %d", A_Set.ids[i], A_Set.hpcount);
		A_Set.players_left--;
		Sleep(1150);
	}

	A_Set.process = 0;
	addMessageToChatWindow("Выдача HP окончена");
	MessageBeep(MB_ICONEXCLAMATION);
	memset(A_Set.ids, 0, sizeof(A_Set.ids));

	ExitThread(0);
}

void ACMD_ghp(char *param)
{
	int params = sscanf(param, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d", &A_Set.hpcount, &A_Set.ids[0], &A_Set.ids[1], &A_Set.ids[2], &A_Set.ids[3], &A_Set.ids[4],
		&A_Set.ids[5], &A_Set.ids[6], &A_Set.ids[7], &A_Set.ids[8], &A_Set.ids[9], &A_Set.ids[10], &A_Set.ids[11], &A_Set.ids[12], &A_Set.ids[13], &A_Set.ids[14]);

	if (A_Set.process != 0) return addMessageToChatWindow("Ошибка: процесс выдачи оружия/HP/объектов/телепортации/увольнения игроков уже запущен, дождитесь его завершения");

	if (params < 2)
	{
		addMessageToChatWindow("Использование: /ghp [кол-во HP] [id'ы игроков через пробел]");
		addMessageToChatWindow("Пример: /ghp 100 10 20 30 40 50");
		addMessageToChatWindow("Примечание: максимальное кол-во игроков - 15");
		return;
	}

	A_Set.gplayercount = params - 1;
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ghp, 0, 0, 0);
}

void IPinfo()
{
	HINTERNET	hInternet = NULL,
		hConnect = NULL,
		hRequest = NULL;

	DWORD		dwByteRead;

	wchar_t		*wsValid;

	int			size;
	int			i;
	int			distance;
	int			results[2][2];
	int			countryValid[2];
	int			cityValid[2];
	int			providerValid[2];
	int			distanceValid[2];
	int			distanceCalculated = 0;
	int			errorCode;

	double		longitude[2];
	double		latitude[2];

	char		req[100];
	char		szData[1024];
	char		temp[100];
	char		country[2][100];
	char		city[2][100];
	char		lat[2][100];
	char		lng[2][100];
	char		provider[2][100];
	char		outputName[30];

	A_Set.IPinfo = 1;
	A_Set.IPinfo_progress = 0;

	hInternet = ::InternetOpen(TEXT("WinInet"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	if (hInternet != NULL)
	{
		A_Set.IPinfo_progress += 5;

		hConnect = ::InternetConnect(hInternet, "api.2ip.ua", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);

		if (hConnect != NULL)
		{
			A_Set.IPinfo_progress += 5;

			for (i = 0; i < 2; i++)
			{
				A_Set.IPinfo_progress += 5;

				// geo request
				sprintf(req, "/geo.xml?ip=%s", A_Set.IP[i]);
				hRequest = ::HttpOpenRequest(hConnect, "GET", req, NULL, NULL, 0, INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_CACHE_WRITE, 1);

				if (hRequest != NULL)
				{
					A_Set.IPinfo_progress += 5;

					if (::HttpSendRequest(hRequest, NULL, 0, NULL, 0))
					{
						A_Set.IPinfo_progress += 5;

						dwByteRead = 0;

						while (::InternetReadFile(hRequest, szData, sizeof(szData) - 1, &dwByteRead) && dwByteRead)
						{
							szData[dwByteRead] = 0;
							OutputDebugStringA(szData);
							dwByteRead = 0;
						}

						results[i][0] = 1;

						size = strlen(szData) + 1;
						wsValid = new wchar_t[size];

						MultiByteToWideChar(CP_UTF8, 0, szData, -1, wsValid, size);
						WideCharToMultiByte(CP_ACP, NULL, wsValid, -1, szData, size, NULL, NULL);

						delete[] wsValid;

						StringFind(szData, "<country_rus>", '<', country[i]);

						if (strlen(country[i]) > 1)
							countryValid[i] = 1;
						else
							countryValid[i] = 0;

						StringFind(szData, "<city_rus>", '<', city[i]);

						if (strlen(city[i]) > 1)
							cityValid[i] = 1;
						else
							cityValid[i] = 0;

						StringFind(szData, "<latitude>", '<', lat[i]);
						StringFind(szData, "<longitude>", '<', lng[i]);

						if (strlen(lat[i]) > 1 && strlen(lng[i]) > 1)
							distanceValid[i] = 1;
						else
							distanceValid[i] = 0;
					}
					::InternetCloseHandle(hRequest);
				}

				// provider request
				sprintf(req, "/provider.xml?ip=%s", A_Set.IP[i]);
				hRequest = ::HttpOpenRequest(hConnect, "GET", req, NULL, NULL, 0, INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_CACHE_WRITE, 1);

				if (hRequest != NULL)
				{
					A_Set.IPinfo_progress += 5;

					if (::HttpSendRequest(hRequest, NULL, 0, NULL, 0))
					{
						A_Set.IPinfo_progress += 5;

						dwByteRead = 0;

						while (::InternetReadFile(hRequest, szData, sizeof(szData) - 1, &dwByteRead) && dwByteRead)
						{
							szData[dwByteRead] = 0;
							OutputDebugStringA(szData);
							dwByteRead = 0;
						}

						results[i][1] = 1;

						size = strlen(szData) + 1;
						wsValid = new wchar_t[size];

						MultiByteToWideChar(CP_UTF8, 0, szData, -1, wsValid, size);
						WideCharToMultiByte(CP_ACP, NULL, wsValid, -1, szData, size, NULL, NULL);

						delete[] wsValid;

						StringFind(szData, "<name_rus>", '<', temp);

						if (strlen(temp) < 1)
						{
							StringFind(szData, "<name_ripe>", '<', temp);

							if (strlen(temp) > 1)
							{
								if (strstr(temp, "&quot;"))
									StringReplace(temp, "&quot;", "\"", provider[i]);
								else
									strcpy(provider[i], temp);

								providerValid[i] = 1;
							}
							else
								providerValid[i] = 0;
						}
						else
						{
							StringReplace(temp, "&quot;", "\"", provider[i]);
							providerValid[i] = 1;
						}
					}
					::InternetCloseHandle(hRequest);
				}
			}
			::InternetCloseHandle(hConnect);
		}
		::InternetCloseHandle(hInternet);
	}

	if (distanceValid[0] && distanceValid[1])
	{
		double radLat1, radLat2, radLon1, radLon2, radLonDif, atan2top, atan2bottom, deltaAngle;
		double earthRadius = 6372.795, pi = 3.141592653589793238463;

		latitude[0] = atof(lat[0]);
		longitude[0] = atof(lng[0]);
		latitude[1] = atof(lat[1]);
		longitude[1] = atof(lng[1]);

		radLat1 = latitude[0] * (pi / 180);
		radLon1 = longitude[0] * (pi / 180);
		radLat2 = latitude[1] * (pi / 180);
		radLon2 = longitude[1] * (pi / 180);

		radLonDif = radLon2 - radLon1;

		atan2top = sqrt(pow(cos(radLat2) * sin(radLonDif), 2) + pow(cos(radLat1) * sin(radLat2) - sin(radLat1) * cos(radLat2) * cos(radLonDif), 2));
		atan2bottom = sin(radLat1) * sin(radLat2) + cos(radLat1) * cos(radLat2) * cos(radLonDif);

		deltaAngle = atan2(atan2top, atan2bottom);
		distance = earthRadius * deltaAngle;

		distanceCalculated = 1;
	}

	A_Set.IPinfo_progress = 70;

	for (i = 0; i < 2; i++)
	{
		sprintf(outputName, "%s IP", i == 0 ? "Рег" : "Последний");

		if (results[i][0] && results[i][1] && countryValid[i] && cityValid[i] && providerValid[i])
		{
			if (A_Set.outmethod == 1)
				addMessageToChatWindow("%s — Страна: %s — Город: %s — Провайдер: %s", outputName, country[i], city[i], provider[i]);
			else
			{
				say("/a %s — Страна: %s — Город: %s — Провайдер: %s", outputName, country[i], city[i], provider[i]);
				Sleep(1150);
			}
		}
		else if (results[i][0] && countryValid[i] && cityValid[i])
		{
			if (A_Set.outmethod == 1)
				addMessageToChatWindow("%s — Страна: %s — Город: %s", outputName, country[i], city[i]);
			else
			{
				say("/a %s — Страна: %s — Город: %s", outputName, country[i], city[i]);
				Sleep(1150);
			}
		}
		else if (results[i][0] && countryValid[i])
		{
			if (A_Set.outmethod == 1)
				addMessageToChatWindow("%s — Страна: %s", outputName, country[i]);
			else
			{
				say("/a %s — Страна: %s", outputName, country[i]);
				Sleep(1150);
			}
		}
		else
		{
			if (!results[i][0] && !results[i][1]) errorCode = 1;
			else if (!results[i][0]) errorCode = 2;
			else if (!countryValid[i]) errorCode = 3;

			if (A_Set.outmethod == 1)
				addMessageToChatWindow("%s — Данные не получены — Код ошибки: %d", outputName, errorCode);
			else
			{
				say("/a %s — Данные не получены — Код ошибки: %d", outputName, errorCode);
				Sleep(1150);
			}
		}

		A_Set.IPinfo_progress += 10;
	}

	if (distanceCalculated)
	{
		if (A_Set.outmethod == 1)
			addMessageToChatWindow("Примерное расстояние (по прямой): %d км", distance);
		else
			say("/a Примерное расстояние (по прямой): %d км", distance);
	}

	A_Set.IPinfo_progress += 10;

	A_Set.IPinfo = 0;

	ExitThread(0);
}

void ACMD_ipinfo(char *param)
{
	char nickname[30];

	if (A_Set.IPinfo) return addMessageToChatWindow("Ошибка: проверка уже начата");
	if (sscanf(param, "%s%d", &nickname, &A_Set.outmethod) < 1)
	{
		addMessageToChatWindow("Использование: /iip [id или Nick_Name] [место вывода результатов проверки]");
		addMessageToChatWindow("Место вывода: 1 - в чат");
		addMessageToChatWindow("Место вывода: 2 - в админ чат");
		return;
	}

	if (strlen(nickname) > 3)
	{
		say("/agetip %s", &nickname);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)IPinfo, 0, 0, 0);
	}
	else
	{
		say("/getip %s", &nickname);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)IPinfo, 0, 0, 0);
	}
}

void ACMD_guns(char *param)
{
	addMessageToChatWindow("{FFFF00}Список оружия (id - название):");
	addMessageToChatWindow("1 - Brass Knuckles, 2 - Golf Club, 3 - Nightstick, 4 - Knife, 5 - BaseballBat, 6 - Shovel, 7 - Pool Cue");
	addMessageToChatWindow("8 - Katana, 10 - Purple Dildo, 11 - Dildo, 12 - Vibrator, 13 - Silver Vibrator, 14 - Flowers, 15 - Cane");
	addMessageToChatWindow("23 - 9mm, 24 - Deagle, 25 - Shotgun, 29 - MP5, 30 - AK47, 31 - M4, 33 - Rifle, 43 - Camera, 46 - Parachute");
	return;
}

void ACMD_SaveGangZones(char *param)	
{
    if (param[0] == 0) {
        param = "gangs.log";
    }
    addMessageToChatWindow("Сохраняем данные в файл \"%s\"", param);
    FILE *fGangLog = fopen((".\\" M0D_FOLDER "GangZones\\" + std::string(param)).c_str(), "w");
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

void ACMD_startlist(char *param)
{
	if (A_Set.process == 3) return addMessageToChatWindow("Ошибка: идёт процесс телепортации");
	if (A_Set.started == 1) return addMessageToChatWindow("Ошибка: сбор списка игроков уже начат");

	if (sscanf(param, "%d", &A_Set.tplimit) < 1)
	{
		addMessageToChatWindow("Использование: /startlist [лимит игроков]");
		addMessageToChatWindow("Лимит игроков: 0 - начать сбор списка без лимита");
		addMessageToChatWindow("Лимит игроков: больше нуля - кол-во игроков, при достижении которого необходимо остановить сбор списка");
		return;
	}

	if (A_Set.tplimit < 0 || A_Set.tplimit > 1004) return;

	memset(A_Set.listed, 0, sizeof(A_Set.listed));
	A_Set.teleportlist = true;
	A_Set.tpcount = 0;
	A_Set.process = 2;
	A_Set.started = 1;
	A_Set.stopped = 0;

	if (A_Set.phonestate == 1) say("/togphone");
	addMessageToChatWindow("Сбор списка игроков для телепорта начат");
	addMessageToChatWindow("Каждый игрок, отправший вам смс автоматически попадает в список");
	addMessageToChatWindow("Используйте /stoplist чтобы остановить сбор");
}

void ACMD_stoplist(char *param)
{
	if (A_Set.started == 0) return addMessageToChatWindow("Ошибка: сбор списка игроков для телепорта не начат. Используйте /startlist");
	if (A_Set.stopped == 1) return addMessageToChatWindow("Ошибка: сбор списка игроков уже остановлен");

	A_Set.process = 0;
	A_Set.teleportlist = false;
	A_Set.stopped = 1;
	A_Set.started = 0;

	if (A_Set.phonestate == 0) say("/togphone");
	addMessageToChatWindow("Сбор списка игроков для телепорта остановлен");
	addMessageToChatWindow("Используйте /starttp чтобы начать телепортацию игроков из списка");
}

void starttp()
{
	A_Set.process = 3;

	addMessageToChatWindow("Телепортация игроков из списка начата");
	addMessageToChatWindow("Игроков в списке: %d", A_Set.tpcount);
	MessageBeep(MB_ICONEXCLAMATION);

	A_Set.tpcount_left = A_Set.tpcount;

	for (int i = 0; i < A_Set.tpcount; i++)
	{
		if (!A_Set.process)
			break;

		say("/gethere %d", A_Set.tpid[i]);
		Sleep(1150);

		if (A_Set.tphp)
		{
			say("/sethp %d 100", A_Set.tpid[i]);
			Sleep(1150);
		}

		A_Set.tpcount_left--;
	}

	A_Set.process = 0;
	A_Set.started = 0;
	A_Set.stopped = 0;

	addMessageToChatWindow("Телепортация игроков из списка законечена");
	MessageBeep(MB_ICONEXCLAMATION);

	ExitThread(0);
}

void ACMD_starttp(char *param)
{
	if (A_Set.process != 0) return addMessageToChatWindow("Ошибка: процесс выдачи оружия/HP/объектов/телепортации/увольнения игроков уже запущен, дождитесь его завершения");
	if (A_Set.stopped == 0) return addMessageToChatWindow("Ошибка: список для телепорта не собран. Используйте /startlist");
	if (A_Set.tpcount == 0) return addMessageToChatWindow("Ошибка: в списке телепорта нет ни одного игрока");

	if (sscanf(param, "%d", &A_Set.tphp) < 1)
	{
		addMessageToChatWindow("Использование: /starttp [выдача HP]");
		addMessageToChatWindow("Примечание: 0 - без выдачи HP, 1 - с выдачей HP (выдаёт 100 HP после телепорта)");
		return;
	}

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)starttp, 0, 0, 0);
}

void ACMD_vehid(char *param)
{
	int		i = 0;
	int		result = 0;

	if (strlen(param) < 1)
	{
		addMessageToChatWindow("Использование: /vehid [название (регистр букв не учитывается)]");
		addMessageToChatWindow("Примеры: /vehid Infernus, /vehid police maverick");
		return;
	}

	if (!strncmp(param, "LSPD", 4))
		param = "Cop Car LS";
	if (!strncmp(param, "SFPD", 4))
		param = "Cop Car SF";
	if (!strncmp(param, "LVPD", 4))
		param = "Cop Car LV";
	if (!strncmp(param, "Tank", 4))
		param = "Rhino";

	while (vehs[i].name != NULL)
	{
		if (strcmpi(vehs[i].name, param) == 0)
		{
			result = 1;
			break;
		}

		i++;
	}

	if (result == 1)
		addMessageToChatWindow("Vehicle: %s — ID: %d", vehs[i].name, vehs[i].id);
	else
		addMessageToChatWindow("Ошибка: \"%s\" не найден в списке транспорта", param);
}

void ACMD_gunlist(char *param)
{
	int	list = sscanf(param, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d", &A_Set.gunid[0], &A_Set.gunbullets[0], &A_Set.gunid[1], &A_Set.gunbullets[1],
		&A_Set.gunid[2], &A_Set.gunbullets[2], &A_Set.gunid[3], &A_Set.gunbullets[3], &A_Set.gunid[4], &A_Set.gunbullets[4], &A_Set.gunid[5], &A_Set.gunbullets[5],
		&A_Set.gunid[6], &A_Set.gunbullets[6], &A_Set.gunid[7], &A_Set.gunbullets[7]);

	if (list == 2 || list == 4 || list == 6 || list == 8 || list == 10 || list == 12 || list == 14 || list == 16)
		A_Set.gunlist = list / 2;
	else
	{
		addMessageToChatWindow("Использование: /gunlist [id оружия] [патроны]");
		addMessageToChatWindow("Примечание: список возможно составлять одновременно из нескольких оружий, лимит - 8");
		addMessageToChatWindow("Пример: /gunlist 24 5000 25 1000 31 999");
		addMessageToChatWindow("После составления списка можете использовать /ggun для начала выдачи");
		return;
	}

	addMessageToChatWindow("Список оружия успешно составлен:");

	for (int i = 0; i < A_Set.gunlist; i++)
		addMessageToChatWindow("%d. %d оружие - %d патрон", i + 1, A_Set.gunid[i], A_Set.gunbullets[i]);

	addMessageToChatWindow("Можете использовать /ggun или /massgun для начала выдачи");
}

void ggun()
{
	int	bullets;

	A_Set.process = 1;
	addMessageToChatWindow("Выдача оружия начата");
	MessageBeep(MB_ICONEXCLAMATION);

	A_Set.players_left = A_Set.gplayercount;

	for (int i = 0; i < A_Set.gplayercount; i++)
	{
		if (A_Set.process == 0)
			break;

		for (int j = 0; j < A_Set.gunlist; j++)
		{
			if (A_Set.process == 0)
				break;

			bullets = A_Set.gunbullets[j];

			while (bullets > 999)
			{
				if (A_Set.process == 0)
					break;

				say("/givegun %d %d 999", A_Set.ids[i], A_Set.gunid[j]);
				bullets = bullets - 999;
				Sleep(1150);
			}
			say("/givegun %d %d %d", A_Set.ids[i], A_Set.gunid[j], bullets);
			Sleep(1150);
		}

		addMessageToChatWindow("Игроку %s[%d] выдано оружие из составленного вами списка", getPlayerName(A_Set.ids[i]), A_Set.ids[i]);
		A_Set.players_left--;
		Sleep(1150);
	}

	A_Set.process = 0;
	addMessageToChatWindow("Выдача оружия окончена");
	MessageBeep(MB_ICONEXCLAMATION);
	memset(A_Set.ids, 0, sizeof(A_Set.ids));

	ExitThread(0);
}

void ggun_skills()
{
	int	bullets;
	int	gunid[4];
	int	gunbullets[4];
	int	gunlist = 4;

	gunid[0] = 31;
	gunbullets[0] = 5500;
	gunid[1] = 24;
	gunbullets[1] = 3500;
	gunid[2] = 25;
	gunbullets[2] = 3500;
	gunid[3] = 29;
	gunbullets[3] = 5500;

	A_Set.process = 1;
	addMessageToChatWindow("Выдача оружия начата");
	MessageBeep(MB_ICONEXCLAMATION);

	A_Set.players_left = A_Set.gplayercount;

	for (int i = 0; i < A_Set.gplayercount; i++)
	{
		if (A_Set.process == 0)
			break;

		for (int j = 0; j < gunlist; j++)
		{
			if (A_Set.process == 0)
				break;

			bullets = gunbullets[j];

			while (bullets > 999)
			{
				if (A_Set.process == 0)
					break;

				say("/givegun %d %d 999", A_Set.ids[i], gunid[j]);
				bullets = bullets - 999;
				Sleep(1150);
			}
			say("/givegun %d %d %d", A_Set.ids[i], gunid[j], bullets);
			Sleep(1150);
		}
		addMessageToChatWindow("Игроку %s[%d] выдано оружие из составленного вами списка", getPlayerName(A_Set.ids[i]), A_Set.ids[i]);
		A_Set.players_left--;
		Sleep(1150);
	}

	A_Set.process = 0;
	addMessageToChatWindow("Выдача оружия окончена");
	MessageBeep(MB_ICONEXCLAMATION);
	memset(A_Set.ids, 0, sizeof(A_Set.ids));

	ExitThread(0);
}

void ACMD_ggun(char *param)
{
	int type = 0;
	char firstpar[30];

	int params = sscanf(param, "%s%d%d%d%d%d%d%d%d%d%d%d%d%d%d", &firstpar, &A_Set.ids[1], &A_Set.ids[2], &A_Set.ids[3], &A_Set.ids[4], &A_Set.ids[5],
		&A_Set.ids[6], &A_Set.ids[7], &A_Set.ids[8], &A_Set.ids[9], &A_Set.ids[10], &A_Set.ids[11], &A_Set.ids[12], &A_Set.ids[13], &A_Set.ids[14]);

	if (params < 1)
	{
		addMessageToChatWindow("Использование: /ggun [id'ы игроков через пробел]");
		addMessageToChatWindow("Пример: /ggun 24 5 3 10 20 30 40 50");
		addMessageToChatWindow("Примечание: максимальное кол-во игроков - 15");
		addMessageToChatWindow("Игрокам будет выдано оружие из составленного вами списка (/gunlist)");
		addMessageToChatWindow("Чтобы выдать комплект оружия для прокачки скиллов используйте /ggun skills [id'ы игроков через пробел]");
		return;
	}

	if (strcmpi(firstpar, "skills") == 0)
	{
		for (int i = 0; i < params; i++)
			A_Set.ids[i] = A_Set.ids[i + 1];

		type = 1;
	}
	else
	{
		int len = strlen(firstpar);
		int checked = 0;

		for (int i = 0; i < len; i++)
			if (firstpar[i] >= '0' && firstpar[i] <= '9')
				checked++;

		if (checked == len)
		{
			A_Set.ids[0] = atoi(firstpar);
			type = 2;
		}
	}

	if (type == 0) return;
	if (type == 2 && A_Set.gunlist == 0) return addMessageToChatWindow("Ошибка: для начала составьте список оружия для выдачи - /gunlist");
	if (A_Set.process != 0) return addMessageToChatWindow("Ошибка: процесс выдачи оружия/HP/объектов/телепортации/увольнения игроков уже запущен, дождитесь его завершения");

	if (type == 1)
	{
		A_Set.gplayercount = params - 1;
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ggun_skills, 0, 0, 0);
	}

	if (type == 2)
	{
		A_Set.gplayercount = params;
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ggun, 0, 0, 0);
	}
}

void uninvoffmembers()
{
	char	filename[MAX_PATH];
	FILE	*file;
	int		i, j;
	int		lines = 0;
	int		players = 0;
	char	arr[100];
	char	endcontent[1000][100];

	snprintf(filename, sizeof(filename), "%s\\mod_sa\\UninviteList.txt", g_szWorkingDirectory);
	file = fopen(filename, "r");

	if (file)
	{
		addMessageToChatWindow("Метод чтения: список offmembers (2)");

		for (j = 0; fgets(arr, 100, file) != NULL; j++)
		{
			std::tr1::regex check1("(.*)\\[([A-Z]+[a-z]+_[A-Z]+[a-z]+)\\](.*)\\n");
			std::tr1::regex check2("(.*)\\[([A-Z]+[a-z]+_[A-Z]+[a-z]+)\\](.*)");
			std::string str = arr;
			if (std::regex_match(str, check1) || std::regex_match(str, check2))
			{
				std::tr1::cmatch temp;
				std::tr1::regex rx("\\[([A-Z]+[a-z]+_[A-Z]+[a-z]+)\\]");
				std::tr1::regex_search(str.c_str(), temp, rx);
				std::string tempstring = temp.format("$&");
				tempstring.erase(tempstring.find('['), 1);
				tempstring.erase(tempstring.find(']'), 1);
				std::copy(tempstring.begin(), tempstring.end(), endcontent[players]);
				endcontent[players][tempstring.size()] = '\0';
				players++;
			}
		}

		fclose(file);

		if (players > 0)
		{
			A_Set.uninv_players_left = players;
			A_Set.process = 5;

			addMessageToChatWindow("Увольнение игроков из списка началось");
			addMessageToChatWindow("Игроков найдено в списке: %d", players);
			MessageBeep(MB_ICONEXCLAMATION);

			for (i = 0; i < players; i++)
			{
				if (A_Set.process == 0)
					break;

				say("/offuninvite %s", endcontent[i]);
				A_Set.uninv_players_left--;
				Sleep(1150);
			}

			A_Set.process = 0;

			addMessageToChatWindow("Увольнение игроков из списка закончено");
			MessageBeep(MB_ICONEXCLAMATION);
		}
		else
			addMessageToChatWindow("Ошибка: в списке не найдено ни одного игрока");
	}
	else
		addMessageToChatWindow("Ошибка: файл со списком игроков для увольнения (UninviteList.txt) не найден в папке mod_sa");

	ExitThread(0);
}

void uninvlist()
{
	char	filename[MAX_PATH];
	FILE	*file;
	int		j;
	int		players = 0;
	char	arr[100];
	char	endcontent[100][100];

	snprintf(filename, sizeof(filename), "%s\\mod_sa\\UninviteList.txt", g_szWorkingDirectory);
	file = fopen(filename, "r");

	if (file)
	{
		addMessageToChatWindow("Метод чтения: чистый список (1)");

		for (j = 0; fgets(arr, 100, file) != NULL; j++)
		{
			std::string str = arr;
			std::tr1::regex check1("([A-Z]+[a-z]+_[A-Z]+[a-z]+)\\n");
			std::tr1::regex check2("([A-Z]+[a-z]+_[A-Z]+[a-z]+)");
			if (std::regex_match(str, check1))
			{
				str.erase(str.end() - 1);
				std::copy(str.begin(), str.end(), endcontent[players]);
				endcontent[players][str.size()] = '\0';
				players++;
			}
			else if (std::regex_match(str, check2))
			{
				strcpy(endcontent[players], arr);
				players++;
			}
		}

		fclose(file);

		if (players > 0)
		{
			A_Set.uninv_players_left = players;
			A_Set.process = 5;

			addMessageToChatWindow("Увольнение игроков из списка началось");
			addMessageToChatWindow("Игроков найдено в списке: %d", players);
			MessageBeep(MB_ICONEXCLAMATION);

			for (j = 0; j < players; j++)
			{
				if (A_Set.process == 0)
					break;

				say("/offuninvite %s", endcontent[j]);
				A_Set.uninv_players_left--;
				Sleep(1150);
			}

			A_Set.process = 0;

			addMessageToChatWindow("Увольнение игроков из списка закончено");
			MessageBeep(MB_ICONEXCLAMATION);
		}
		else
			addMessageToChatWindow("Ошибка: в списке не найдено ни одного игрока");
	}
	else
		addMessageToChatWindow("Ошибка: файл со списком игроков для увольнения (UninviteList.txt) не найден в папке mod_sa");

	ExitThread(0);
}

void ACMD_uninv(char *param)
{
	if (A_Set.process != 0) return addMessageToChatWindow("Ошибка: процесс выдачи оружия/HP/объектов/телепортации/увольнения игроков уже запущен, дождитесь его завершения");

	int method;

	if (sscanf(param, "%d", &method) < 1)
	{
		addMessageToChatWindow("Использование: /uninv [метод чтения]");
		addMessageToChatWindow("/uninvhelp - инструкция по использованию команды");
		return;
	}

	if (method == 1)
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)uninvlist, 0, 0, 0);
	else if (method == 2)
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)uninvoffmembers, 0, 0, 0);
}

void ACMD_uninvhelp(char *param)
{
	addMessageToChatWindow("{FFFF00}Инструкция по использованию команды /uninv:");
	addMessageToChatWindow("Используйте \"1\" в методе чтения, если вы имеете чистый список (содержит только ники игроков)");
	addMessageToChatWindow("Используйте \"2\" в методе чтения, если вы имеете список из /offmembers (содержит не только ники игроков)");
	addMessageToChatWindow("Файл со списком игроков для увольнения: mod_sa/UninviteList.txt");
	addMessageToChatWindow("Важно: чтение будет происходить ПОСТРОЧНО - если список скопирован из /offmembers, в строке будет искаться ник игрока");
	addMessageToChatWindow("Важно: если вы используете чистый список, то так же составляйте его ПОСТРОЧНО - каждый ник с новой строки, без запятых и т.д.");
	addMessageToChatWindow("Важно: ники игроков обязательно должны быть написанны по форме Nick_Name");
	addMessageToChatWindow("Важно: не копируйте offmembers из простого чатлога клиента (chatlog.txt) - после сохранения стираются переносы строк");
	addMessageToChatWindow("Важно: offmembers копируйте либо из mod_sa_chatbox.log, либо из mod_sa_chatbox_all.log");
}

void ACMD_changeFontName(char*)
{
    ShowLocalSampDialog(523, DIALOG_STYLE_INPUT, "Изменение фона", "Введите имя шрифта, который вы хотите установить", "Save", "Cancel");
}

void ACMD_addadmin(char *param)
{
	uint16_t playerId;
	char szPlayerName[24];
	if (sscanf(param, "%s", &szPlayerName) < 1)
	{
		addMessageToChatWindow("Использование: /addadmin [ник администратора]");
		addMessageToChatWindow("Указанный администратор будет добавлен в список Admins.ini");
		return;
	}

	playerId = getPlayerID(szPlayerName);
	
	if (playerId >= 0 && playerId <= 999)
	{
		addOnlineAdmin(playerId, szPlayerName, true);
		addMessageToChatWindow("%s{FFFFFF} - внесён в чекер администраторов", szPlayerName);
	}
	else
	{
		appendToFile(".\\" M0D_FOLDER "Checkers\\Admins.ini", szPlayerName);
		A_Set.AdminChecker.push_back(szPlayerName);
		addMessageToChatWindow("%s{FFFFFF} - внесён в список администраторов", szPlayerName);
	}
}

void ACMD_addplayer(char *param)
{
	uint16_t playerId;
	char szPlayerName[256];
	char *szReason;
	

	if (sscanf(param, "%s", &szPlayerName) < 1)
	{
		addMessageToChatWindow("Использование: /addplayer [ник игрока][причина добавления]");
		addMessageToChatWindow("Указанный игрок будет добавлен в список Players.ini");
		return;
	}

	param += strlen(szPlayerName) + 1;
	szReason = param;


	playerId = getPlayerID(szPlayerName);

	if (playerId >= 0 && playerId <= 999)
	{
		addOnlinePlayer(playerId, szPlayerName, szReason, true);
		addMessageToChatWindow("%s{FFFFFF} - внесён в чекер игроков", szPlayerName);
	}
	else
	{
		appendToPlayerFile(szPlayerName, szReason);
		A_Set.PlayerChecker.emplace_back(szPlayerName, szReason);
		addMessageToChatWindow("%s{FFFFFF} - внесён в список игроков", szPlayerName);
	}
}

void ACMD_delplayer(char *param)
{
	char szPlayerName[24];
	uint16_t playerId;

	if (sscanf(param, "%s", &szPlayerName) < 1)
	{
		addMessageToChatWindow("Использование: /delplayer [ник игрока]");
		addMessageToChatWindow("Указанный игрок будет удалён из списка Players.ini");
		return;
	}

	playerId = getPlayerID(szPlayerName);

	if (playerId >= 0 && playerId <= 999)
	{
		deleteFromPlayerList(playerId);
		addMessageToChatWindow("%s{FFFFFF} - удалён из чекера игроков", szPlayerName);
	}
	else
	{
		std::string nick = szPlayerName;
		auto iter = std::find_if(A_Set.PlayerChecker.begin(), A_Set.PlayerChecker.end(), [&nick](const std::pair<std::string, std::string> &pair) {return (pair.first == nick); });
		if (iter != A_Set.PlayerChecker.end()) {
			removeInFile(".\\" M0D_FOLDER "Checkers\\Players.ini", std::distance(A_Set.PlayerChecker.begin(), iter));
			A_Set.PlayerChecker.erase(iter);
			addMessageToChatWindow("%s{FFFFFF} - удалён из списка игроков", szPlayerName);
		}
	}
}

void ACMD_deladmin(char *param)
{
	char szPlayerName[24];
	uint16_t playerId;

	if (sscanf(param, "%s", &szPlayerName) < 1)
	{
		addMessageToChatWindow("Использование: /deladmin [ник администратора]");
		addMessageToChatWindow("Указанный администратор будет удалён из списка Admins.ini");
		return;
	}

	playerId = getPlayerID(szPlayerName);
		
	if (playerId >= 0 && playerId <= 999)
	{
		deleteFromAdminList(playerId);
		addMessageToChatWindow("%s{FFFFFF} - удалён из чекера администраторов", szPlayerName);
	}
	else
	{
		std::string nick = szPlayerName;
		auto iter = std::find(A_Set.AdminChecker.begin(), A_Set.AdminChecker.end(), nick);
		if (iter != A_Set.AdminChecker.end()) {
			removeInFile(".\\" M0D_FOLDER "Checkers\\Admins.ini", std::distance(A_Set.AdminChecker.begin(), iter));
			A_Set.AdminChecker.erase(iter);
			addMessageToChatWindow("%s{FFFFFF} - удалён из списка администраторов", szPlayerName);
		}
	}
}


void adminFunctions_cmds()
{
	addAdminCommand("vehid", ACMD_vehid);
	addAdminCommand("ranks", ACMD_ranks);
	addAdminCommand("guns", ACMD_guns);
	addAdminCommand("masshp", ACMD_MassHP);
	addAdminCommand("massgun", ACMD_GiveGuns);
	addAdminCommand("ghp", ACMD_ghp);
	addAdminCommand("gobj", ACMD_gobj);
	addAdminCommand("massobj", ACMD_massobj);
	addAdminCommand("startlist", ACMD_startlist);
	addAdminCommand("stoplist", ACMD_stoplist);
	addAdminCommand("starttp", ACMD_starttp);
	addAdminCommand("ggun", ACMD_ggun);
	addAdminCommand("uninv", ACMD_uninv);
	addAdminCommand("uninvhelp", ACMD_uninvhelp);
	addAdminCommand("gunlist", ACMD_gunlist);
	addAdminCommand("leader", ACMD_leader);
	addAdminCommand("astats", ACMD_astats);
	addAdminCommand("stop", ACMD_stop);
	addAdminCommand("addadmin", ACMD_addadmin);
	addAdminCommand("addplayer", ACMD_addplayer);
	addAdminCommand("delplayer", ACMD_delplayer);
	addAdminCommand("deladmin", ACMD_deladmin);
	addAdminCommand("ahelp", ACMD_ahelp);
	addAdminCommand("skill", ACMD_SkillGuns);
	addAdminCommand("startp", ACMD_PlayerTP);
	addAdminCommand("ip", ACMD_IpInfo);
	addAdminCommand("iip", ACMD_ipinfo);
	addAdminCommand("tr", ACMD_trace);
	addAdminCommand("endtp", ACMD_PlayerTPBreak);
    addAdminCommand("changekey", ACMD_changeKeyCombo);
    addAdminCommand("savegz", ACMD_SaveGangZones);
    addAdminCommand("cmpgz", ACMD_CompareGangZones);
    addAdminCommand("clrgz", ACMD_clearDifferenceGangZones);
    addAdminCommand("setfont", ACMD_changeFontName);
}