#ifndef OFFSET_H
#define OFFSET_H

#include <Windows.h>

//struct with all offsets provide by Y3t1y3t 'dumper TY!
struct Entity
{
	//localPlayer
	DWORD localPlayer = 0xA7AFBC;
	DWORD iCrossHairID = 0x2410;
	DWORD forceAttack = 0x2E8F2B4;

	//entity
	DWORD entityBase = 0x4A1D354;
	DWORD loopDistance = 0x10;
	DWORD dormant = 0xE9;

	//comuns
	DWORD index = 0x64;
	DWORD ihealth = 0xFC;
	DWORD iTeam = 0xF0;
	DWORD fFlags = 0x100;
	DWORD vecOrigin = 0x134;
	DWORD boneMatrix = 0xA78;

	//aimbot
	DWORD shotsFired = 0x1D6C;
	DWORD viewAngle = 0x4CE0;
	DWORD vecPunch = 0x13E8;
	DWORD engineBase = 0x5D2294;
};

extern Entity entity;

#endif
