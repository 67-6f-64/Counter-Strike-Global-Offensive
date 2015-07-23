#ifndef MAIN_H_
#define MAIN_H_

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <regex>
#include <string>

template<typename TYPE>
TYPE RPM(HANDLE proc, DWORD address, SIZE_T size){
	TYPE buffer = TYPE();
	::ReadProcessMemory(proc, (LPCVOID)address, &buffer, size, 0);
	return buffer;
}

template<typename TYPE>
BOOL WPM(HANDLE proc, DWORD address, TYPE dataToWrite){
	TYPE buffer = dataToWrite;
	return ::WriteProcessMemory(proc, (LPVOID)address, &buffer, sizeof(buffer), 0);
}

typedef struct
{
	float   x;
	float   y;
	float   z;
}Vector, *PVector;

class cheat{
public:
	HWND game;
	DWORD gamePid;
	HANDLE gameHandle;

	DWORD GetModule(LPCSTR processName, int processPid);
	void GetAddress();

	bool aim = false;
	void startAimbot();
	static DWORD Aimbot(LPVOID lpParam);
	double Distance(Vector a, Vector b, bool metters);
	Vector GetBone(int iBone);
	Vector BonePos(DWORD target, DWORD address, int boneId);
	bool WorldToScreen(Vector vStart, Vector &vOut, float *flMatrix);
	float DistanceBetweenCross(float X, float Y);
	Vector CalcAngle(Vector& src, Vector& dst);

	bool glow = false;
	void startGlow();
	static DWORD Glow(LPVOID lpParam);

	bool radar = false;
	void startRadar();
	static DWORD Radar(LPVOID lpParam);

	bool norecoil = false;
	void startNoRecoil();
	static DWORD NoRecoil(LPVOID lpParam);
	bool IsRifle(int id);
	float NormalX(float angle);
	float NormalY(float angle);

	bool readmemory = false;
	void startReadMemory();
	static DWORD ReadMemory(LPVOID lpParam);
	void WriteGlow(HANDLE proc, float r, float g, float b, float a, bool Occluded, bool Unoccluded);

	//dlls
	DWORD clientDll;
	DWORD engineDll;
	//pointers
	DWORD myPlayer;
	DWORD entityBase;
	DWORD entity;
	DWORD engine;
	DWORD glowBs;
	DWORD weaponEntity;
	DWORD weaponBaseIndex;
	DWORD myPlayerBoneBase;

	//vars
	int myPlayerHealth;
	int myPlayerTeam;
	int entityHealth;
	int entityTeam;
	bool entityDormant;
	int glowIndex;
	int shotsFired;
	Vector aPunch;
	Vector oldAngle;
	int weaponId;
	int weaponAmmo;
	bool weaponReloading;
	Vector vMatrix;
};

class others{
public:
	int option;

	bool isNumber(int input);
	void Menu();

};

extern cheat Cheat;
extern others Others;

#endif
