#include "main.h"
#include "offset.h"

//Constructor where we find the game, get HWND, process ID, HANDLE and get client.dll/engine.dll address's
Memory::Memory()
{
	std::cout << "Searching Counter-Strike: Global Offensive..." << std::endl << std::endl;
	do
	{
		gameHwnd = FindWindow(NULL, "Counter-Strike: Global Offensive");
		Sleep(16);
	} while (gameHwnd == NULL);
	system("cls");
	std::cout << "Game Found! Working..." << std::endl << std::endl;

	if (!proc)
	{
		gameHwnd = FindWindow(NULL, "Counter-Strike: Global Offensive");		
		GetWindowThreadProcessId(gameHwnd, &gamePID); 		
		proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, gamePID); //need change PROCESS_ALL_ACCELL to read only
	}		
	
	clientDll = Module("client.dll", gamePID);
	engineDll = Module("engine.dll", gamePID);
	std::cout << "-----------GENERAL INFO---------------------------------------------" << std::endl;
	std::cout << "Game Hwnd: " << gameHwnd << " gamePID: " << gamePID << " Handle: " << proc << std::endl << std::endl;	
}


//destructor where we set NULL to clientDll and engineDll and CloseHandle of OpenProcess 
Memory::~Memory()
{
	if (clientDll && engineDll)
	{
		clientDll = NULL;
		engineDll = NULL;
	}
	if (proc)
		CloseHandle(proc);
}

DWORD Memory::GetlocalPlayer()
{
	localPlayerBase = RPM<DWORD>(proc, (GetClientDll() + entity.localPlayer), sizeof(DWORD));
	return localPlayerBase;
}

DWORD Memory::GetEntity()
{
	entityLoop = RPM<DWORD>(proc, (GetClientDll() + entity.entityBase), sizeof(DWORD));
	return entityLoop;
}

int Memory::GetmyHealth()
{
	health = RPM<int>(proc, (GetlocalPlayer() + entity.ihealth), sizeof(int));
	return health;
}

int Memory::GetmyTeam()
{
	team = RPM<int>(proc, (GetlocalPlayer() + entity.iTeam), sizeof(int));
	return team;
}

int Memory::GetmyFlags()
{
	flags = RPM<int>(proc, (GetlocalPlayer() + entity.fFlags), sizeof(int));
	return flags;
}

Vector Memory::GetmyPos()
{
	myPos = RPM<Vector>(proc, (GetlocalPlayer() + entity.vecOrigin), sizeof(Vector));
	return myPos;
}

DWORD Memory::GetClientDll()
{
	if (clientDll != NULL)
		return clientDll;
	return 0;
}

DWORD Memory::GetEngineDll()
{
	if (engineDll != NULL)
		return engineDll;
	return 0;
}

DWORD Memory::Module(LPCSTR moduleName, DWORD pId)
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
