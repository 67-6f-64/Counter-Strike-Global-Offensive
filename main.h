#include "main.h"

//#include "offset.h" in main.h and extern it here so every cpp file have access to it
Entity entity;

Memory* mem = new Memory(); //create new object of memory class

int Menu()
{
	int option = 0;
	system("cls");
	std::cout << "MENU: choose a number and type [ENTER]" << std::endl;
	std::cout << "(1) Only Read Memory " << mem->reading <<std::endl;
	std::cout << "(2) TriggerBot inCrossHairId " << mem->trigger << std::endl;

	std::cout << "(0) EXIT" << std::endl;
	std::cin >> option;
	switch (option)
	{
	case 1:			
		if (!mem->reading){
			mem->StartReadMemory();
			mem->reading = true;
		}		
		Menu();	
		break;
	case 2:			
		if (!mem->trigger)
		{
			mem->StartTrigger();
			mem->trigger = true;
		}							
		Menu();
		break;		
	case 0:
		return 0;
		break;
	default:
		Menu();
		break;
	}
}

int main()
{
	int option = 0;
	system("Color 1B");

	// to get health use mem->GetHealth() e.g

	std::cout << "-----------ADDRESS'S CLIENT.DLL ENGINE.DL----------------------------" << std::endl;
	std::cout << "client.dll: " << mem->GetClientDll() << " engine.dll: " << mem->GetEngineDll() << std::endl << std::endl;

	Menu();

	delete mem;

	return 0;
}
