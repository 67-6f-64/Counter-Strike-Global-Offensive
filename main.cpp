#include "main.h"

int main()
{
	int option = 0;
	system("Color 1B");

	Memory* mem = new Memory(); //create new object of memory class

	// to get health use mem->GetHealth() e.g

	std::cout << "-----------ADDRESS'S CLIENT.DLL ENGINE.DL----------------------------" << std::endl;
	std::cout << "client.dll: " << mem->GetClientDll() << " engine.dll: " << mem->GetEngineDll() << std::endl << std::endl;
	std::cout << "Start Thread to Read Memory? (1) to yes, (2) to no" << std::endl;
	std::cin >> option;
	if (option == 1)
		mem->StartReadMemory();
	
	delete mem; //delete object created

	system("pause");

	return 0;
}
