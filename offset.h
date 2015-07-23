#ifndef OFFSET_H
#define OFFSET_H

#include <Windows.h>

//struct with all offsets provide by Y3t1y3t 'dumper TY!
struct Entity
{
	//localPlayer
	DWORD localPlayer = 0xA77D2C;
	DWORD iCrossHairID = 0x2410;
	DWORD forceAttack = 0x2E8BCE4;

	//entity
	DWORD entityBase = 0x4A19D84;
	DWORD loopDistance = 0x10;

	//comuns
	DWORD index = 0x64;
	DWORD ihealth = 0xFC;
	DWORD iTeam = 0xF0;
	DWORD fFlags = 0x100;
	DWORD vecOrigin = 0x134;
};

extern Entity entity;

#endif
