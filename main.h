#ifndef HEADER_H
#define HEADER_H

#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "offset.h"

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

	bool reading = false;
	void StartReadMemory();
	static DWORD ReadMemory(LPVOID lParam);

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

	//entityLoop functions	
	int GetEntHealth(DWORD entAddress); //get data health
	int GetEntTeam(DWORD entAddress); //get data team
	int GetEntFlags(DWORD entAddress); //get data Flags
	int GetEntCrossId(DWORD entAddress); // get data crossairId
	int GetEntId(DWORD entAddress); // get data index	
	Vector GetEntPos(DWORD entAddress); //get data pos: x, y, z

protected:
	HWND gameHwnd;
	HANDLE proc;
	DWORD gamePID;
	DWORD clientDll;
	DWORD engineDll;

	//localplayer
	DWORD localPlayerBase;
	int health;
	int team;
	int flags;
	int crossId;
	int index;
	Vector myPos;

	//entity
	DWORD entityLoop;
	int ehealth;
	int eteam;
	int eflags;
	int eindex;
	Vector ePos;
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
