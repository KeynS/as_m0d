#pragma once

struct AdminSetting
{
	/*4 bytes*/
	struct CheckerPosition
	{
		long x, y;
	} ACheckPos, PCheckPos, KillListPos;
	/*2 bytes*/
	unsigned short usSetLeaderID;
	/*1 bytes*/
	unsigned char byteFrackID;
};

extern struct AdminSetting A_Set;