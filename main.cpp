#include "main.h"

//#include "offset.h" in main.h and extern it here so every cpp file have access to it
Entity entity;

Memory* mem = new Memory(); //create new object of memory class

int Menu()
{
	int option = 0;	
	std::cout << "MENU: choose a number and type [ENTER]"						<< std::endl;
	std::cout << "(1) Only Read Memory "					<< mem->reading		<< std::endl;
	std::cout << "(2) TriggerBot inCrossHairId "			<< mem->trigger		<< std::endl;
	std::cout << "(3) Aimbot (No Vish Check yet) "			<< mem->aim			<< std::endl;
	std::cout << "(4) Remove Flash "						<< mem->noflash		<< std::endl;
	std::cout << "(0) EXIT" << std::endl;
	std::cin >> option;
	switch (option)
	{
	case 1:			
		if (!mem->reading){
			mem->StartReadMemory();
			mem->reading = true;
		}
		else
			mem->reading = false;
		system("cls");
		Menu();
		break;
	case 2:			
		if (!mem->trigger)
		{
			mem->StartTrigger();
			mem->trigger = true;
		}
		else
			mem->trigger = false;
		system("cls");
		Menu();
		break;
	case 3:
		if (!mem->aim){
			mem->StartAim();
			mem->aim = true;
		}
		else
			mem->aim = false;
		system("cls");
		Menu();
		break;

	case 4:
		if (!mem->noflash){
			mem->StartNoFlash();
			mem->noflash = true;
		}
		else
			mem->noflash = false;
		system("cls");
		Menu();
		break;
	case 0:
		delete mem;
		ExitProcess(0);
		break;
	default:
		Menu();
		break;
	}

	return 0;
}

int main()
{	
	system("Color 1B");

	// to get health use mem->GetHealth() e.g

	std::cout << "-----------ADDRESS'S CLIENT.DLL ENGINE.DL----------------------------" << std::endl;
	std::cout << "client.dll: " << mem->GetClientDll() << " engine.dll: " << mem->GetEngineDll() << std::endl << std::endl;

	Menu();

	delete mem;

	return 0;
}
