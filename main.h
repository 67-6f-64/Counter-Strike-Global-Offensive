#ifndef HEADER_H
#define HEADER_H
#define PI 3.14159265

#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <vector>
#include "offset.h"


#include <d3d9.h>
#include <d3dx9.h>
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")


//VECTOR x,y,z struct for vecOrigin
typedef struct
{
	float   x;
	float   y;
	float   z;
}Vector, *PVector;

//Class to get data from game
class Memory
{
public:
	Memory(); //constructor
	~Memory(); //desctructor

	//tread to read memory every 5s
	bool reading = false;
	HANDLE sRM;
	void StartReadMemory();
	static DWORD ReadMemory(LPVOID lParam);

	//thread triggerbot inCrosshairId 
	bool trigger = false;
	bool Wpm = false;
	HANDLE sT;
	void StartTrigger();
	static DWORD Trigger(LPVOID lParam);

	//thread aimbot no vis check (rage aimbot)
	bool aim = false;
	HANDLE sA;
	void StartAim();
	static DWORD Aim(LPVOID lParam);
	double Distance(Vector a, Vector b, bool metters);
	Vector CalcAngle(Vector& src, Vector& dst);
	void ClampAngle(Vector &angles);
	float AngleBetween(Vector &angleA, Vector &angleB, bool angle);
	bool isInFov(D3DXVECTOR3 forward, D3DXVECTOR3 EnemyPos, D3DXVECTOR3 LocalPos, float fov);
	bool isInMyFov();

	//thread no flash
	bool noflash = false;
	HANDLE snF;
	void StartNoFlash();
	static DWORD NoFlash(LPVOID lParam);
	
	DWORD Module(LPCSTR moduleName, DWORD pId); //module address's .exe .dll
	DWORD GetClientDll(); //client.dll
	DWORD GetEngineDll(); //engine.dll

	//localPlayer functions
	DWORD GetlocalPlayer(); //get localPlayer	
	int GetmyHealth(); //get data health
	int GetmyTeam(); //get data team
	int GetmyFlags(); //get data Flags
	int GetmyCrossId(); // get data crossairId
	int GetmyId(); // get data index
	Vector GetmyPos(); //get data pos: x, y, z
	Vector GetmyaPunch();
	Vector GetmyViewangle();
	Vector GetmyBonePos(int id);

	//entityLoop functions	
	int GetEntHealth(DWORD entAddress); //get data health
	int GetEntTeam(DWORD entAddress); //get data team
	int GetEntFlags(DWORD entAddress); //get data Flags
	int GetEntCrossId(DWORD entAddress); // get data crossairId
	int GetEntId(DWORD entAddress); // get data index
	bool GetEntDormant(DWORD entAddress); //get data dormant
	Vector GetEntPos(DWORD entAddress); //get data pos: x, y, z
	//Vector GetEntbonePos(DWORD entAddress);

	//boneposition, id 10 = head, id 2 = cheast
	Vector BonePos(DWORD target, DWORD address, int boneId);

	//engine
	DWORD GetEngPointer();

	//flash
	float GetflashDuration();
	float GetFlashColor();

	//weapon
	int GetweaponId();
	int GetweaponAmmo();
	bool IsWeaponReloading();

	//
	HANDLE Getproc();

protected:
	HWND gameHwnd;
	HANDLE proc;
	DWORD gamePID;
	DWORD clientDll;
	DWORD engineDll;

	//localplayer
	DWORD localPlayerBase;
	int health = 0;
	int team = 0;
	int flags = 0;
	int crossId = 0;
	int index = 0;
	Vector myPos;
	Vector myViewangle;
	Vector myBonePos;

	//entity
	DWORD entityLoop;
	int ehealth = 0;
	int eteam = 0;
	int eflags = 0;
	int eindex = 0;
	Vector ePos;
	bool eDormant;
	Vector bonePos;

	//aimbot
	int shotsFired;
	Vector aPunch;
	Vector oldAngle;
	DWORD enginePointer;

	//flash
	float flashDurantion = 0;
	float flashColor = 0;

	//weapon
	int weaponAmmo = 0;
	bool weaponReloading;
	int weaponid;
};

//ReadProcessMemory template
template<typename TYPE>
TYPE RPM(HANDLE proc, DWORD address, SIZE_T size){
	TYPE buffer = TYPE();
	::ReadProcessMemory(proc, (LPCVOID)address, &buffer, size, 0);
	return buffer;
}

//WriteProcessMemory template
template<typename TYPE>
BOOL WPM(HANDLE proc, DWORD address, TYPE dataToWrite){
	TYPE buffer = dataToWrite;
	return ::WriteProcessMemory(proc, (LPVOID)address, &buffer, sizeof(buffer), 0);
}


#endif
