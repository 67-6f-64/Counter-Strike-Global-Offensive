#include "main.h"
#include "offset.h"

//since our thread is a static one inside a class we need to call the class object here to access functions
Memory memory;

void Memory::StartTrigger()
{
	HANDLE start = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Trigger, NULL, 0, NULL);
}

//THIS TRIGGER ONLY WORKS AFTER ALL ENEMYS JOIN THE ENEMY TEAM
//checking team first
//create a list with all target adress's
//loop target and check crosshair id and target id
//shoot

DWORD Memory::Trigger(LPVOID lParam)
{
	memory.trigger = true;
	std::vector<DWORD> enemys;
	int oldTeam = 0;
	while (true)
	{
		/*
		a) check if we are in the same team yet.
		b) if not get new targets else avoid read everything again and use what we have
		*/
		if (memory.GetmyTeam() != oldTeam) 
		{
			oldTeam = memory.GetmyTeam(); // since we are in a differnt team set the old to actual

			enemys.clear(); //clear to get new enemys address's

			for (int i = 0; i < 64; ++i) //loop to get enemy's
			{
				memory.entityLoop = RPM<DWORD>(memory.proc, ((memory.clientDll + entity.entityBase) + ((i - 1)*entity.loopDistance)), sizeof(DWORD));
				
				if (memory.entityLoop == NULL) //if entity is not valid
					continue;				

				if (memory.GetEntTeam(memory.entityLoop) != 0 && memory.eteam != memory.team) //if entity is not 0 and is not our team add to vector
				{
					enemys.push_back(memory.entityLoop);
				}
			}

		}

		
		if (memory.GetmyTeam() == oldTeam) //i'm in the same team yet, so i don't need to get all entitys again
		{			
			for (std::vector<DWORD>::size_type i = 0; i != enemys.size(); ++i) //loop enemys/targets
			{				
				if (memory.GetEntId(enemys[i]) == memory.GetmyCrossId() && memory.GetEntHealth(enemys[i]) > 0) //entity id is equal to our crosshairId?
				{
					//shoot: write to the memory +attack / -attack
					WPM<int>(memory.proc, (memory.clientDll + entity.forceAttack), 5);
					Sleep(25);
					WPM<int>(memory.proc, (memory.clientDll + entity.forceAttack), 4);
					Sleep(70);
				}
			}
		}

		

		if (!memory.trigger)
			break;

		Sleep(16);
	}

	return 0;
}

void Memory::StartReadMemory() //call this function to start ReadMemory thread
{
	HANDLE start = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReadMemory, NULL, 0, NULL);
}

DWORD Memory::ReadMemory(LPVOID lParam) // thread: ReadMemory where we get data from memory's game
{
	memory.reading = true;
	while (true)
	{
		system("cls");
		/*                      LOCALPLAYER INFO                                       */
		std::cout << "My Player->[" << memory.GetmyId() << "]" << std::endl << std::endl;
		std::cout << "-> Health: " << memory.GetmyHealth() << std::endl;
		std::cout << "-> Team: " << memory.GetmyTeam() << std::endl;
		std::cout << "-> Flags: " << memory.GetmyFlags() << std::endl;
		std::cout << "-> Crosshair Id: " << memory.GetmyCrossId() << std::endl;
		std::cout << "-> localPlayer Position X: " << memory.GetmyPos().x 
			<< " Y: " << memory.GetmyPos().y 
			<< " Z: " << memory.GetmyPos().z << std::endl << std::endl;
		
		/*                      LIST LOCALPLAYER ENEMYS                                  */
		for (int i = 0; i < 64; i++)
		{
			memory.entityLoop = RPM<DWORD>(memory.proc, ((memory.clientDll + entity.entityBase) + ((i - 1)*entity.loopDistance)), sizeof(DWORD));
			if (memory.entityLoop == NULL)
				continue;

			if (memory.GetEntTeam(memory.entityLoop) != memory.GetmyTeam() && memory.GetEntHealth(memory.entityLoop) > 0)
			{
				std::cout << "Enemy->[" << memory.GetEntId(memory.entityLoop) << "]" << std::endl << std::endl;
				std::cout << "-> Health: " << memory.GetEntHealth(memory.entityLoop) << std::endl;
				std::cout << "-> Team: " << memory.GetEntTeam(memory.entityLoop) << std::endl;
				std::cout << "-> Flags: " << memory.GetEntFlags(memory.entityLoop) << std::endl;
				std::cout << "-> Enemy's Position X: " << memory.GetEntPos(memory.entityLoop).x 
					<< " Y: " << memory.GetEntPos(memory.entityLoop).y 
					<< " Z: " << memory.GetEntPos(memory.entityLoop).z << std::endl << std::endl;
			}

		}

		
		if (!memory.reading)
			break;

		Sleep(5000);
	}
	return 0;
}
