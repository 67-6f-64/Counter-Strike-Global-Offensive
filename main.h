#ifndef HEADER_H
#define HEADER_H

#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>

//Class to get data from game
class Memory
{
public:
	Memory(); //constructor
	~Memory(); //desctructor

	void StartReadMemory();
	static DWORD ReadMemory(LPVOID lParam);

	DWORD Module(LPCSTR moduleName, DWORD pId); //module address's .exe .dll
	DWORD GetClientDll(); //client.dll
	DWORD GetEngineDll(); //engine.dll
	DWORD GetlocalPlayer(); //get localPlayer
	DWORD GetEntity(); //get entityLoop
	int GetmyHealth(); //get data health
	int GetmyTeam(); //get data team
	int GetmyFlags(); //get data Flags
	//Vector GetPos(); //get data pos: x, y, z

protected:
	HWND gameHwnd;
	HANDLE proc;
	DWORD gamePID;
	DWORD clientDll;
	DWORD engineDll;
	DWORD localPlayerBase;
	DWORD entityLoop;
	int health;
	int team;
	float flags;
	//Vector pos = { 0, 0, 0 };
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

//VECTOR x,y,z struct for vecOrigin
typedef struct
{
	float   x;
	float   y;
	float   z;
}Vector, *PVector;



#endif
