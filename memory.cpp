#include "main.h"
#include "offset.h"

//Constructor where we find the game, get HWND, process ID, HANDLE and get client.dll/engine.dll address's
Memory::Memory()
{
	std::cout << "Searching Counter-Strike: Global Offensive..." << std::endl << std::endl;
	do
	{
		//find window of game "Counter-Strike: Global Offsenfive, you can use "Valve001" in className
		gameHwnd = FindWindow(NULL, "Counter-Strike: Global Offensive");
		Sleep(16);
	} while (gameHwnd == NULL);

	std::cout << "Game Found! Working..." << std::endl << std::endl;

	if (!proc)
	{				
		GetWindowThreadProcessId(gameHwnd, &gamePID); // get gameHwnd PID		
		proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, gamePID); //need change PROCESS_ALL_ACCELL to read only, needed to readmemory
	}		
	
	do
	{
		clientDll = Module("client.dll", gamePID); // get client.dll module address
		engineDll = Module("engine.dll", gamePID); // get engine.dll module address
		Sleep(16);
	} while (!clientDll || !engineDll);
	

	std::cout << "-----------GENERAL INFO---------------------------------------------" << std::endl;
	std::cout << "Game Hwnd: " << gameHwnd << " gamePID: " << gamePID << " Handle: " << proc << std::endl << std::endl;	
}


//destructor where we set NULL to clientDll and engineDll and CloseHandle of OpenProcess 
Memory::~Memory()
{
	//shoutdown threads
	if (aim)
		aim = false;

	if (reading)
		reading = false;

	if (trigger && !Wpm)
		trigger = false;

	if (noflash)
		noflash = false;

	if (clientDll && engineDll)
	{
		clientDll = NULL;
		engineDll = NULL;
	}

	if (proc)
		CloseHandle(proc);
}


/*

localPlayer function
You can get:
health, team, flags, position, crosshair, index

*/

DWORD Memory::GetlocalPlayer() //address of localPlayer
{	
	localPlayerBase = RPM<DWORD>(proc, (GetClientDll() + entity.localPlayer), sizeof(DWORD));
	return localPlayerBase;
}

int Memory::GetmyHealth() //int with localPlayer health
{
	health = RPM<int>(proc, (GetlocalPlayer() + entity.ihealth), sizeof(int));
	return health;
}

int Memory::GetmyTeam() //int with localPlayer team
{
	team = RPM<int>(proc, (GetlocalPlayer() + entity.iTeam), sizeof(int));
	return team;
}

int Memory::GetmyFlags() //int with localPlayer flags, jump, crounch etc
{
	flags = RPM<int>(proc, (GetlocalPlayer() + entity.fFlags), sizeof(int));
	return flags;
}

int Memory::GetmyCrossId() //int with localPlayer crosshair id
{
	crossId = RPM<int>(proc, (GetlocalPlayer() + entity.iCrossHairID), sizeof(int));
	return crossId;
}

int Memory::GetmyId() //int with localPlayer index id
{
	index = RPM<int>(proc, (GetlocalPlayer() + entity.index), sizeof(int));
	return index;
}

Vector Memory::GetmyPos() //vector with localPlayer position x, y, z
{
	myPos = RPM<Vector>(proc, (GetlocalPlayer() + entity.vecOrigin), sizeof(Vector));
	return myPos;
}

Vector Memory::GetmyaPunch()
{
	aPunch = RPM<Vector>(proc, (GetlocalPlayer() + entity.vecPunch), sizeof(Vector));
	return aPunch;
}

Vector Memory::GetmyViewangle()
{
	myViewangle = RPM<Vector>(proc, (GetlocalPlayer() + entity.viewAngle), sizeof(Vector));
	return myViewangle;
}

/*

entity function
You can get:
health, team, flags, position, index

*/

int Memory::GetEntHealth(DWORD entAddress)//get data health
{
	ehealth = RPM<int>(proc, (entAddress + entity.ihealth), sizeof(int));
	return ehealth;
}

int Memory::GetEntTeam(DWORD entAddress) //get data team
{
	eteam = RPM<int>(proc, (entAddress + entity.iTeam), sizeof(int));
	return eteam;
}

int Memory::GetEntFlags(DWORD entAddress) //get data Flags
{
	eflags = RPM<int>(proc, (entAddress + entity.fFlags), sizeof(int));
	return eflags;
}

int Memory::GetEntId(DWORD entAddress) // get data index
{
	eindex = RPM<int>(proc, (entAddress + entity.index), sizeof(int));
	return eindex;
}

Vector Memory::GetEntPos(DWORD entAddress) //get data pos: x, y, z
{
	ePos = RPM<Vector>(proc, (entAddress + entity.vecOrigin), sizeof(Vector));
	return ePos;
}

bool Memory::GetEntDormant(DWORD entAddress)
{
	eDormant = RPM<bool>(proc, (entAddress + entity.dormant), sizeof(bool));
	return eDormant;
}

Vector Memory::GetEntbonePos(DWORD entAddress)
{
	bonePos = RPM<Vector>(proc, (entAddress + entity.boneMatrix), sizeof(Vector));
	return bonePos;
}

/*

ENGINE

*/

DWORD Memory::GetEngPointer()
{
	enginePointer = RPM<DWORD>(proc, (engineDll + entity.engineBase), sizeof(DWORD));
	return enginePointer;
}

/*

FLASH

*/

float Memory::GetflashDuration()
{
	flashDurantion = RPM<float>(proc, (clientDll + entity.flFlashDuration), sizeof(float));
	return flashDurantion;
}

float Memory::GetFlashColor()
{
	flashColor = RPM<float>(proc, (clientDll + entity.flFlashMaxAlpha), sizeof(float));
	return flashColor;
}

DWORD Memory::GetClientDll() //client.dll 
{
	if (clientDll != NULL)
		return clientDll;
	return 0;
}

DWORD Memory::GetEngineDll() //engine.dll
{
	if (engineDll != NULL)
		return engineDll;
	return 0;
}

DWORD Memory::Module(LPCSTR moduleName, DWORD pId) //function to get module address csgo.exe/client.dll/engine.dll/xxx.dll with pid
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pId);
	MODULEENTRY32  allinfo;
	BOOL haveProcess = Module32First(hSnapShot, &allinfo);
	while (haveProcess)
	{
		if (!strcmp(moduleName, allinfo.szModule))
		{
			return (DWORD)allinfo.modBaseAddr;
		}
		haveProcess = Module32Next(hSnapShot, &allinfo);
	}
	return 0;
}
