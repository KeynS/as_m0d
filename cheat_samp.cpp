﻿/*

	PROJECT:		mod_sa
	LICENSE:		See LICENSE in the top level directory
	COPYRIGHT:		Copyright we_sux, BlastHack

	mod_sa is available from https://github.com/BlastHackNet/mod_s0beit_sa/

	mod_sa is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	mod_sa is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with mod_sa.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "main.h"

#define D3DCOLOR_COMPARE(color,r,g,b) \
    (color >> 8)==((D3DCOLOR)((((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define D3DCOLOR_RGBX(r,g,b) \
    ((D3DCOLOR)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|(0xff)))
#define D3DCOLOR_RGBX(color) \
    ((D3DCOLOR)(color << 8)|0xff)

void changeColorClientMsg(BitStream* bitStream, DWORD dwNewColor, DWORD dwLen, const char* msg)
{
	bitStream->ResetWritePointer();
	bitStream->Write(dwNewColor);
	bitStream->Write(dwLen);
	bitStream->Write(msg, dwLen);
}

int			g_iJoiningServer = 0;
int			iClickWarpEnabled = 0;
int			g_iNumPlayersMuted = 0;
bool		g_bPlayerMuted[SAMP_MAX_PLAYERS];

void sampMainCheat(void)
{
	traceLastFunc("sampMainCheat()");

	// g_Vehicles & g_Players pointers need to be refreshed or nulled
	if (isBadPtr_writeAny(g_SAMP->pPools, sizeof(stSAMPPools)))
	{
		g_Vehicles = NULL;
		g_Players = NULL;
	}
	else if (g_Vehicles != g_SAMP->pPools->pVehicle || g_Players != g_SAMP->pPools->pPlayer)
	{
		if (isBadPtr_writeAny(g_SAMP->pPools->pVehicle, sizeof(stVehiclePool)))
			g_Vehicles = NULL;
		else
			g_Vehicles = g_SAMP->pPools->pVehicle;
		if (isBadPtr_writeAny(g_SAMP->pPools->pPlayer, sizeof(stPlayerPool)))
			g_Players = NULL;
		else
			g_Players = g_SAMP->pPools->pPlayer;
	}

	// update GTA to SAMP translation structures
	update_translateGTASAMP_vehiclePool();
	update_translateGTASAMP_pedPool();

	sampAntiHijack();

	// start chatbox logging
	if (set.chatbox_logging)
	{
		static int	chatbox_init;
		if (!chatbox_init)
		{
			SYSTEMTIME	time;
			GetLocalTime(&time);
			LogChatbox(false, "Session started at %02d/%02d/%02d", time.wDay, time.wMonth, time.wYear);
			chatbox_init = 1;
		}
	}

	if (KEYCOMBO_PRESSED(set.key_rejoin))
	{
		restartGame();
		disconnect(500);
		cheat_state_text("Rejoining in %d seconds...", set.rejoin_delay / 1000);
		cheat_state->_generic.rejoinTick = GetTickCount();
	}

	if (KEYCOMBO_PRESSED(set.key_respawn))
		playerSpawn();
	
	if (KEYCOMBO_DOWN(set.chat_secondary_key))
	{
		int			i, key, spam;
		const char	*msg;
		for (i = 0; i < INI_CHATMSGS_MAX; i++)
		{
			struct chat_msg *msg_item = &set.chat[i];
			if (msg_item->key == NULL)
				continue;
			if (msg_item->msg == NULL)
				continue;
			if (msg_item->key != key_being_pressed)
				continue;
			key = msg_item->key;
			msg = msg_item->msg;
			spam = msg_item->spam;
			if (spam)
			{
				if (msg)
					if (KEY_DOWN(key))
						say("%s", msg);
			}
			else
			{
				if (msg)
					if (KEY_PRESSED(key))
						say("%s", msg);
			}
		}
	}
	if (set.clickwarp_enabled && iIsSAMPSupported)
	{
		if (KEYCOMBO_PRESSED(set.key_clickwarp_enable))
		{
			g_iCursorEnabled ^= 1;
			toggleSAMPCursor(g_iCursorEnabled);
		}
		if (g_iCursorEnabled && KEYCOMBO_PRESSED(set.key_clickwarp_click))
		{
			iClickWarpEnabled = 1;
		}
	}

	static int	iSAMPHooksInstalled;
	if (!iSAMPHooksInstalled)
	{
		installSAMPHooks();
		iSAMPHooksInstalled = 1;
	}

	if (cheat_state->_generic.rejoinTick && cheat_state->_generic.rejoinTick < (GetTickCount() - set.rejoin_delay))
	{
		g_SAMP->iGameState = GAMESTATE_WAIT_CONNECT;
		cheat_state->_generic.rejoinTick = 0;
	}

	if (g_iJoiningServer == 1)
	{
		restartGame();
		disconnect(500);
		cheat_state_text("Joining server in %d seconds...", set.rejoin_delay / 1000);
		cheat_state->_generic.join_serverTick = GetTickCount();
		g_iJoiningServer = 2;
	}

	if (g_iJoiningServer == 2
		&& cheat_state->_generic.join_serverTick
		&&	 cheat_state->_generic.join_serverTick < (GetTickCount() - set.rejoin_delay))
	{
		g_SAMP->iGameState = GAMESTATE_WAIT_CONNECT;
		g_iJoiningServer = 0;
		cheat_state->_generic.join_serverTick = 0;
	}

	adminMainThread();
}

void sampAntiHijack(void)
{
	if (g_SAMP == NULL) return;
	traceLastFunc("sampAntiHijack()");

	vehicle_info *veh = vehicle_info_get(VEHICLE_SELF, VEHICLE_ALIVE);
	if (set.anti_carjacking && veh == NULL)
	{
		if (cheat_state->_generic.got_vehicle_id)
			cheat_state->_generic.got_vehicle_id = false;
		if (cheat_state->_generic.anti_carjackTick
			&&	 cheat_state->_generic.anti_carjackTick < (GetTickCount() - 500)
			&& cheat_state->_generic.car_jacked)
		{
			if (cheat_state->_generic.car_jacked_last_vehicle_id == 0)
			{
				GTAfunc_showStyledText("~r~Unable To Unjack~w~!", 1000, 5);
				cheat_state->_generic.anti_carjackTick = 0;
				cheat_state->_generic.car_jacked = false;
				return;
			}

			cheat_state->_generic.anti_carjackTick = 0;
			cheat_state->_generic.car_jacked = false;
			GTAfunc_PutActorInCar(GetVehicleByGtaId(cheat_state->_generic.car_jacked_last_vehicle_id));

			//struct vehicle_info *veh = GetVehicleByGtaId(cheat_state->_generic.car_jacked_last_vehicle_id);
			//if ( veh != NULL )
			//	vect3_copy( cheat_state->_generic.car_jacked_lastPos, &veh->base.matrix[4 * 3] );
			GTAfunc_showStyledText("~r~Car Unjacked~w~!", 1000, 5);
			return;
		}
	}
	else if (set.anti_carjacking)
	{
		if (veh->passengers[0] == actor_info_get(ACTOR_SELF, 0))
		{
			if (!cheat_state->_generic.got_vehicle_id)
			{
				cheat_state->_generic.car_jacked_last_vehicle_id = getPlayerVehicleGTAScriptingID(ACTOR_SELF);
				if (cheat_state->_generic.car_jacked_last_vehicle_id > 0)
					cheat_state->_generic.got_vehicle_id = true;
			}
		}
	}
}

void HandleRPCPacketFunc(unsigned char id, RPCParameters *rpcParams, void(*callback) (RPCParameters *))
{
	if (!isCheatPanicEnabled())
	{
		if (set.netPatchAssoc[id][INCOMING_RPC] != nullptr && set.netPatchAssoc[id][INCOMING_RPC]->enabled)
			return;
	}
	if (rpcParams != nullptr && rpcParams->numberOfBitsOfData >= 8)
	{
		switch (id)
		{
			case RPC_ClientMessage:
			{
                if (cheat_state->_generic.cheat_panic_enabled)
                    break;

				BitStream		bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
				uint32_t		dwStrLen, dwColor;
				char			szMsg[256];

				bsData.Read(dwColor);
				bsData.Read(dwStrLen);
				if (dwStrLen >= sizeof(szMsg)) 
                    dwStrLen = sizeof(szMsg) - 1;
				bsData.Read(szMsg, dwStrLen);
				szMsg[dwStrLen] = '\0';

				if (strstr(szMsg, "Nik ["))
				{
					if (strstr(szMsg, "   R-IP [") && strstr(szMsg, "   L-IP [") && strstr(szMsg, "   IP ["))
					{
						StringFind(szMsg, "   R-IP [", ']', A_Set.IP[0]);
						StringFind(szMsg, "   IP [", ']', A_Set.IP[1]);
						StringFind(szMsg, "Nik [", ']', A_Set.IP[2]);
						A_Set.lastip = 1;
					}
					else if (strstr(szMsg, "Register-IP [") && strstr(szMsg, "Last-IP ["))
						{
							StringFind(szMsg, "   Register-IP [", ']', A_Set.IP[0]);
							StringFind(szMsg, "   Last-IP [", ']', A_Set.IP[1]);
							StringFind(szMsg, "Nik [", ']', A_Set.IP[2]);
							A_Set.lastip = 1;
						}
				}
				for (int p = 0; p <= g_Players->ulMaxPlayerID; ++p)
				{
					if (!g_Players->iIsListed[p])
						continue;

					if (strstr(szMsg, "<Warning>") && strstr(szMsg, getPlayerName(p)))
					{
						A_Set.warningid = p;
						A_Set.warningvalid = 1;
					}

					char search[40];
					sprintf(search, "на %s[%d]: ", getPlayerName(p), p);

					if (strstr(szMsg, search) && !strstr(szMsg, "Убил транспортом"))
					{
						A_Set.reportid = p;
						A_Set.reportvalid = 1;
					}
				}
				if (strstr(szMsg, "[забанил: ") && strstr(szMsg, "[забанен: ") && strstr(szMsg, "[причина: "))
				{
					if (strstr(szMsg, "IOffBan") || strstr(szMsg, "OffBan"))
					{
						A_Set.ipoffban = 1;
						StringFind(szMsg, "[забанил: ", ']', A_Set.banIP[0]);
						StringFind(szMsg, "[забанен: ", ']', A_Set.banIP[1]);
					}
				}
                if (strstr(szMsg, "Администратор: ")) {
                    if (A_Set.bLogBan && strstr(szMsg, " забанил "))
                        adminLog(A_Set.fLogBan, szMsg);

                    if (A_Set.bLogWarn && strstr(szMsg, " выдал warn "))
                        adminLog(A_Set.fLogWarn, szMsg);
                }

				if (A_Set.bMassTP && A_Set.usMaxPlayerTP <= g_Players->ulMaxPlayerID && strstr(szMsg, "Отправитель: "))
				{
					std::string Msg = szMsg;
					auto pos = Msg.find_last_of('[');
					pos++;
					USHORT id = (USHORT)std::stoi(Msg.substr(pos, Msg.length() - pos - 1));
					if (g_Players->sLocalPlayerID != id && id <= g_Players->ulMaxPlayerID && g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor == nullptr)
					{
						if (std::find(A_Set.PlayersIDForTP.begin(), A_Set.PlayersIDForTP.end(), id) == A_Set.PlayersIDForTP.end())
						{
							A_Set.PlayersIDForTP.push_back(id);
							A_Set.usMaxPlayerTP--;
						}
					}
				}

				if (A_Set.bIpInfo)
				{
					if (strstr(szMsg, "Nik"))
					{
						std::string MSg = szMsg;
						auto start = MSg.find('[', 8), end = MSg.find(']',start);
						std::string r_ip = MSg.substr(start + 1, end - 1 - start);
						start = MSg.find_last_of('[');
						std::string l_ip = MSg.substr(start + 1, MSg.length() - 2 - start);
						SravnenieIP(r_ip, l_ip);
						A_Set.bIpInfo = false;
					}
					else
						if (strstr(szMsg, "Произошла ошибка."))
							A_Set.bIpInfo = false;
				}
				if (A_Set.bChatID)
				{
					bool	change = false;
					if (g_Players->iLocalPlayerNameLen && dwStrLen >= g_Players->iLocalPlayerNameLen)
					{
						char *found = strstr(szMsg, (char*)getPlayerName(g_Players->sLocalPlayerID));
						if (found)
						{
							if (found[g_Players->iLocalPlayerNameLen] != '[' && ( found[g_Players->iLocalPlayerNameLen + 1] != '[' || dwColor == 0xAAF79FAA))
							{
								change = true;
								found += g_Players->iLocalPlayerNameLen;
								strcpy((char*)&szMsg[dwStrLen - strlen(found)], std::string("[" + std::to_string(g_Players->sLocalPlayerID) + "]" + std::string(found)).c_str());
								dwStrLen = strlen(szMsg);
							}
						}
					}

					char	*player_name;
					for (int p = 0; p <= g_Players->ulMaxPlayerID && dwStrLen < 250; ++p)
					{
						if (!g_Players->iIsListed[p])
							continue;
						player_name = (char*)getPlayerName(p);
						uint32_t n_len = strlen(player_name);
						if (dwStrLen >= n_len)
						{
							char *found = strstr(szMsg, player_name);
							if (found)
							{
								if (found[n_len] != '[' && ( found[n_len + 1] != '[' || dwColor == 0xAAF79FAA))
								{
									change = true;
									found += n_len;//sprintf(szMsg, "%s[%d]%s", std::string(szMsg).substr(dwStrLen - strlen(found)).c_str(), p, found);
									strcpy((char*)&szMsg[dwStrLen - strlen(found)], std::string("[" + std::to_string(p) + "]" + std::string(found)).c_str());
									dwStrLen = strlen(szMsg);
								}
							}
						}
					}

					if (change)
					{
						rpcParams->numberOfBitsOfData = BYTES_TO_BITS(dwStrLen + 8);
						bsData.SetNumberOfBitsAllocated(rpcParams->numberOfBitsOfData);
						bsData.SetWriteOffset(32);
						bsData.Write(dwStrLen);
						bsData.Write(szMsg, dwStrLen);
					}
				}

				if (A_Set.bChatcolor)
				{
					if (D3DCOLOR_COMPARE(dwColor, 217, 119, 0))
					{
						if (A_Set.bChatcolorsReport && strstr(szMsg, "Жалоба от ") && strstr(szMsg, " на "))
						{
							changeColorClientMsg(&bsData, D3DCOLOR_RGBX(A_Set.dwColorReport), dwStrLen, szMsg);
							break;
						}
						else
                            if (A_Set.bChatcolorsFeedback && strstr(szMsg, "Репорт от"))
							{
                                changeColorClientMsg(&bsData, D3DCOLOR_RGBX(A_Set.dwColorFeedback), dwStrLen, szMsg);
								break;
							}
							else
                                if (A_Set.bChatcolorsReportr && strstr(szMsg, "<-Ответ К"))
								{
                                    changeColorClientMsg(&bsData, D3DCOLOR_RGBX(A_Set.dwColorReportr), dwStrLen, szMsg);
									break;
								}
					}
					else
						if (D3DCOLOR_COMPARE(dwColor, 255, 165, 0))
						{
                            if (A_Set.bChatcolorsSupport)
								if (strstr(szMsg, "<SUPPORT-CHAT> ") || strstr(szMsg, "<-") && strstr(szMsg, " to ")
									&& strstr(szMsg, ": ") || strstr(szMsg, "->Вопрос") && strstr(szMsg, ": "))
								{
                                    changeColorClientMsg(&bsData, D3DCOLOR_RGBX(A_Set.dwColorSupport), dwStrLen, szMsg);
									break;
								}
						}
						else
							if (D3DCOLOR_COMPARE(dwColor, 255, 255, 0))
							{
                                if (A_Set.bChatcolorsSms)
									if (strstr(szMsg, "SMS: ") && (strstr(szMsg, "Отправитель: ") || strstr(szMsg, "Получатель: ")))
									{
                                        changeColorClientMsg(&bsData, D3DCOLOR_RGBX(A_Set.dwColorSms), dwStrLen, szMsg);
										break;
									}
							}
				}

				break;
			}
            case RPC_DeathMessage:
            {
                if (isCheatPanicEnabled() || !A_Set.bLogKillList)
                    break;
                BitStream		bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);

                int16_t killerId, playerId;
                int8_t reason;

                bsData.Read(killerId);
                bsData.Read(playerId);
                bsData.Read(reason);
                const char *name = gta_weapon_name(reason);
                adminLog(A_Set.fLogKillList, "KILLER: %s[%hd] || PLAYER: %s[%hd] || GUN: %s", killerId == -1 ? "None" : getPlayerName(killerId), killerId, getPlayerName(playerId), playerId, name);
                break;
            }
			case RPC_PlayerSpectatePlayer:
			{
				BitStream		bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8 + 1, false);
				bsData.Read(A_Set.reconID);
				break;
			}
            case RPC_ServerJoin:
            {
                if (isCheatPanicEnabled())
                    break;
                BitStream		bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
                uint16_t playerId;
                BYTE byteNameLen;
                char szPlayerName[24];

                bsData.Read(playerId);
                if (playerId > SAMP_MAX_PLAYERS)
                    return;

                bsData.IgnoreBits(40);//color(dword) + npc_byte(byte)
                bsData.Read(byteNameLen);
                if (byteNameLen > 20) return;
                bsData.Read(szPlayerName, byteNameLen);
                szPlayerName[byteNameLen] = '\0';

                if (A_Set.bConnectLog && !gta_menu_active()) {
                    A_Set.connectLog.clear();
                    A_Set.connectLog.append(szPlayerName);
                    A_Set.connectLog.append("[" + std::to_string(playerId) + "]");
                    A_Set.connectLog.append(" подключается к серверу.");
                    A_Set.connectTime = time_get();
                }

                if (!A_Set.AdminChecker.empty()) {
                    if (std::find(A_Set.AdminChecker.cbegin(), A_Set.AdminChecker.cend(), szPlayerName) != A_Set.AdminChecker.cend()) {
                        if (A_Set.AdminsOnline.empty())
                            A_Set.aCheckerMsg.clear();
                        A_Set.AdminsOnline.push_back(playerId);//connect admin
                        char nameAdd[32];
                        sprintf_s(nameAdd, "\n%s[%hu]", szPlayerName, playerId);
                        A_Set.aCheckerMsg.append(nameAdd);
                        break;
                    }
                }

                if (!A_Set.PlayerChecker.empty()) {
                    std::vector<std::pair<std::string, std::string> >::const_iterator it;
                    if ((it = std::find_if(A_Set.PlayerChecker.cbegin(), A_Set.PlayerChecker.cend(), [&szPlayerName](const std::pair<std::string, std::string> &pair) {return (pair.first == szPlayerName); })) != A_Set.PlayerChecker.cend()) {
                        if (A_Set.PlayersOnline.empty())
                            A_Set.pCheckerMsg.clear();
                        A_Set.PlayersOnline.push_back(playerId);//connect player
                        char nameAdd[42];
						sprintf_s(nameAdd, "\n{FFFFFF}%s[%hu]%s ", szPlayerName, playerId, szColorEnable);
						A_Set.pCheckerMsg.append(nameAdd);
                        A_Set.pCheckerMsg.append(it->second);
                    }
                }
                break;
            }
            case RPC_ServerQuit:
            {
                if (isCheatPanicEnabled())
                    break;
                BitStream		bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8 + 1, false);
                uint16_t playerId;

                bsData.Read(playerId);

                if (playerId > g_Players->ulMaxPlayerID) return;

                const char	*szPlayerName = getPlayerName(playerId);

                if (A_Set.bDisconnectLog && !gta_menu_active()) {
                    A_Set.disconnectLog.clear();
                    A_Set.disconnectLog.append(szPlayerName);
                    A_Set.disconnectLog.append("[" + std::to_string(playerId) + "]");
                    A_Set.disconnectLog.append(" отключился от сервера.");
                    A_Set.disconnectTime = time_get();
                }

                std::vector<uint16_t>::iterator it;
                if ((it = std::find(A_Set.AdminsOnline.begin(), A_Set.AdminsOnline.end(), playerId)) != A_Set.AdminsOnline.end()) {
                    A_Set.AdminsOnline.erase(it);
                    if (A_Set.AdminsOnline.empty())
                        A_Set.aCheckerMsg = "\nНет админов в сети";
                    else
                        A_Set.aCheckerMsg.erase(A_Set.aCheckerMsg.find(szPlayerName) - 1, 1 + strlen(szPlayerName) + 2 + std::to_string(playerId).length());
                }
                else
                    if ((it = std::find(A_Set.PlayersOnline.begin(), A_Set.PlayersOnline.end(), playerId)) != A_Set.PlayersOnline.end()) {
                        A_Set.PlayersOnline.erase(it);
                        if (A_Set.PlayersOnline.empty()) {
                            A_Set.pCheckerMsg = "\nНет игроков в сети";
                        }
                        else {
                            auto pos = A_Set.pCheckerMsg.find(szPlayerName);
                            A_Set.pCheckerMsg.erase(pos - 1, A_Set.pCheckerMsg.find('\n', pos));
                        }
                    }
                break;
            }
		} // switch
	}
	callback(rpcParams);
}

bool OnSendRPC(int uniqueID, BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	if (!isCheatPanicEnabled())
	{
		if (set.netPatchAssoc[uniqueID][OUTCOMING_RPC] != nullptr && set.netPatchAssoc[uniqueID][OUTCOMING_RPC]->enabled)
			return false;
	}
	if (uniqueID == RPC_Chat && g_Players != nullptr)
	{
		uint8_t byteTextLen;
		char szText[256];

		parameters->Read(byteTextLen);
		parameters->Read(szText, byteTextLen);
		szText[byteTextLen] = '\0';

		if (set.chatbox_logging)
			LogChatbox(false, "%s: %s", getPlayerName(g_Players->sLocalPlayerID), szText);
	}

	// prevent invulnerability detection
	if (uniqueID == RPC_ClientCheck && cheat_state && cheat_state->_generic.hp_cheat)
	{
		uint8_t type = 0;
		parameters->Read(type);
		if (type == 2)
		{
			uint32_t arg = 0;
			uint8_t response = 0;
			parameters->Read(arg);
			parameters->Read(response);

			// remove invulnerability flags from our real flags
			uint32_t fakeFlags = arg & (0xFF00FFFF | ((~ACTOR_FLAGS_INVULNERABLE) << 16));

			// reform packet data
			parameters->SetWriteOffset(0);
			parameters->Write(type);
			parameters->Write(fakeFlags);
			parameters->Write(response);
		}
	}
	return true;
}

bool OnSendPacket(BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	if (!isCheatPanicEnabled())
	{
		uint8_t packetId;
		parameters->Read(packetId);
		if (set.netPatchAssoc[packetId][OUTCOMING_PACKET] != nullptr && set.netPatchAssoc[packetId][OUTCOMING_PACKET]->enabled)
			return false;
	}
	return true;
}

bool OnReceivePacket(Packet *p)
{
	if (p->data == nullptr || p->length == 0)
		return true;
	if (!isCheatPanicEnabled())
	{
		if (set.netPatchAssoc[p->data[0]][INCOMING_PACKET] != nullptr && set.netPatchAssoc[p->data[0]][INCOMING_PACKET]->enabled)
			return false;
	}
    traceLastFunc("OnReceivePacket");
	if (p->data[0] == ID_MARKERS_SYNC) // packetId
	{
        traceLastFunc("OnReceivePacket::MARKER");
		BitStream	bs(p->data, p->length, false);
		int			iNumberOfPlayers = 0;
		uint16_t	playerID = uint16_t(-1);
		short		sPos[3] = { 0, 0, 0 };
		bool		bIsPlayerActive = false;

		bs.IgnoreBits(8);
		bs.Read(iNumberOfPlayers);
		if (iNumberOfPlayers < 0 || iNumberOfPlayers > SAMP_MAX_PLAYERS)
			return true;

		for (int i = 0; i < iNumberOfPlayers; i++)
		{
			bs.Read(playerID);
			bs.ReadCompressed(bIsPlayerActive);
			if (bIsPlayerActive == 0 || isBadSAMPPlayerID(playerID))
				continue;
			bs.Read(sPos);
			g_stStreamedOutInfo.iPlayerID[playerID] = playerID;
			g_stStreamedOutInfo.fPlayerPos[playerID][0] = sPos[0];
			g_stStreamedOutInfo.fPlayerPos[playerID][1] = sPos[1];
			g_stStreamedOutInfo.fPlayerPos[playerID][2] = sPos[2];
		}
	}
	else
		if (p->data[0] == ID_PLAYER_SYNC)
		{
            traceLastFunc("OnReceivePacket::PLAYER");
			BitStream	bsData(p->data, p->length, false);
			static DWORD dwTime[SAMP_MAX_PLAYERS], dwTimeGM;
			bsData.ResetReadPointer();
			short pId;
			bool bVal;
			float fVec;
			short surf_id = -1;
			float fpos[3];
			bsData.IgnoreBits(8);

			bsData.Read(pId);
			bsData.Read(bVal);
			if (bVal)
				bsData.IgnoreBits(16);
			bsData.Read(bVal);
			if (bVal)
				bsData.IgnoreBits(16);
			bsData.IgnoreBits(16);
			bsData.Read(fpos);
			bsData.IgnoreBits(76);
			bsData.Read(fVec);
			if (fVec != 0.f)
			bsData.IgnoreBits(48);
			bsData.Read(bVal);
			if (bVal)
			{
				bsData.Read(surf_id);
				if (surf_id == 1 && GetTickCount() - dwTimeGM > 3000)
				{
					float offs = g_Players->pRemotePlayer[pId]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[14] - fpos[2];
					if (abs(offs - 15) < 0.6 || abs(offs - 175) < 0.6)
					{
						addMessageToChatWindow("<Warning> Игрок: %s[%d] использует паблик ГМ.", getPlayerName(pId), pId);
						dwTimeGM = GetTickCount();
                        return true;
					}
				}
				int fOffs[3];
				bsData.Read(fOffs);
				if (surf_id != -1 && (fOffs[0] >= 0xFF800000 || fOffs[1] >= 0xFF800000 || fOffs[2] >= 0xFF800000))
				{
					if (GetTickCount() - dwTime[pId] > 15000)
					{
						addMessageToChatWindow("<Warning>  Игрок: %s[%d] использует крашер.", getPlayerName(pId), pId);
						dwTime[pId] = GetTickCount();
					}
					bsData.SetWriteOffset(bsData.GetReadOffset() - 112);
					bsData.Write((short)0);
					bsData.Write((float)0.0f);
					bsData.Write((float)0.0f);
					bsData.Write((float)0.0f);
				}
			}
		}
		else
			if (A_Set.bTraces && p->data[0] == ID_BULLET_SYNC)
			{
                traceLastFunc("OnReceivePacket::BULLET");
				BitStream	bsData(p->data, p->length, false);
				bsData.ResetReadPointer();
				bsData.IgnoreBits(8);
				if (!A_Set.bTraceAll)
				{
					USHORT pID;
					bsData.Read(pID);
					if (pID != A_Set.usTraceID)
						return true;
				}
				else
					bsData.IgnoreBits(16);
				if (A_Set.Tracers.size() >= A_Set.usTraceMaxCount)
				{
					A_Set.Tracers.pop_back();
				}
				stBulletData data;
				memset(&data, 0, sizeof(stBulletData));
				bsData.Read((PCHAR)&data, sizeof(stBulletData));
				A_Set.Tracers.insert(A_Set.Tracers.begin(), Trace(data.fOrigin, data.fTarget, (data.byteType == 1 ? A_Set.dwColorTracerHit : A_Set.dwColorTracer), GetTickCount()));
			}
	return true;
}

void cmd_warp(char *params)
{
	if (params[0] == '\0')
		return addMessageToChatWindow("USAGE: /mod_warp <player id>");

	int playerid = atoi(params);
	if (isBadSAMPPlayerID(playerid) || g_Players->iIsListed[playerid] != 1)
		return addMessageToChatWindow("Player does not exist.");

	float pos[3];
	actor_info *actor = nullptr;
	if (g_Players->pRemotePlayer[playerid]->pPlayerData == nullptr
		|| g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor == nullptr)
	{
		if (vect3_near_zero(g_stStreamedOutInfo.fPlayerPos[playerid]))
			return addMessageToChatWindow("Player is not streamed in.");

		vect3_copy(g_stStreamedOutInfo.fPlayerPos[playerid], pos);
		pos[1] += 1.0f;
		cheat_teleport(pos, 0);
		return;
	}

	if (!getPlayerPos(playerid, pos) ||
		g_Players->pRemotePlayer[playerid]->pPlayerData == nullptr ||
		g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor == nullptr ||
		(actor = g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor->pGTA_Ped) == nullptr)
	{
		return addMessageToChatWindow("Bad player info.");
	}

	pos[1] += 1.0f;
	cheat_teleport(pos, actor->base.interior_id);
}

void cmd_showCMDS(char *)
{
	for (int i = 0; i < g_m0dCmdNum; i++)
	{
		addMessageToChatWindow("%s", g_m0dCmdlist[i]);
	}
}

void initChatCmds(void)
{
	if (g_m0dCommands == true)
		return;

	cheat_state_text("initiated modcommands");
	g_m0dCommands = true;

	addClientCommand("mod_show_cmds", cmd_showCMDS);
	addClientCommand("mod_warp", cmd_warp);
}
