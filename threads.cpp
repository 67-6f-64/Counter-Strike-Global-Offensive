#include "main.h"

Memory memory;

void Memory::StartReadMemory()
{
	HANDLE start = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReadMemory, NULL, 0, NULL);
}

DWORD Memory::ReadMemory(LPVOID lParam)
{
	while (true)
	{
		system("cls");
		std::cout << "My Player->" << std::endl;
		std::cout << "Health: " << memory.GetmyHealth() << " Team: " << memory.GetmyTeam()
			<< " Flags: " << memory.GetmyFlags()
			<< " X: " << memory.GetmyPos().x << " Y: " << memory.GetmyPos().y << " Z: " << memory.GetmyPos().z << std::endl;
		Sleep(250);
	}
	return 0;
}
