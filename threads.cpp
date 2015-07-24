#include "main.h"
#include "offset.h"


//since our thread is a static one inside a class we need to call the class object here to access functions
Memory memory;


void Memory::StartNoFlash()
{
	HANDLE start = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)NoFlash, NULL, 0, NULL);
}

DWORD Memory::NoFlash(LPVOID lParam)
{
	memory.noflash = true;
	DWORD localPlayer = RPM<DWORD>(memory.proc, (memory.clientDll + entity.localPlayer), sizeof(DWORD));
	while (true)
	{

		
		if (memory.GetFlashColor() > 0.0f && memory.GetFlashColor() != 0.0f)
		{
			float newFlashColor = 0.0f;
			WPM<float>(memory.proc, (localPlayer + entity.flFlashMaxAlpha), newFlashColor);
		}


		if (!memory.noflash)
		{
			if (memory.GetFlashColor() == 0.0f && memory.GetFlashColor() != 255.0f)
			{
				float newFlashColor = 255.0f;
				WPM<float>(memory.proc, (localPlayer + entity.flFlashMaxAlpha), newFlashColor);
			}
			break;
		}		
		

		Sleep(16);
	}


	return 0;
}


void Memory::StartAim()
{
	HANDLE start = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Aim, NULL, 0, NULL);
}

/*
MY AIMBOT LOGIC, you can find other in UC forum, don't forget to credit if using
*/
DWORD Memory::Aim(LPVOID lpParam)
{
	memory.aim = true;
	int targets = 0;
	int oldTeam = 0;
	int distance = 100;
	Vector angle;

	while (true)
	{

		if (GetAsyncKeyState(0x46))
		{
			for (int i = 0; i < 64; ++i) //loop to get enemy's
			{
				memory.entityLoop = RPM<DWORD>(memory.proc, ((memory.clientDll + entity.entityBase) + ((i - 1)*entity.loopDistance)), sizeof(DWORD));

				if (memory.entityLoop == NULL) //if entity is not valid
					continue;

				//check for varius things
				if (memory.GetEntDormant(memory.entityLoop) || memory.GetEntTeam(memory.entityLoop) == 0
					|| memory.GetEntTeam(memory.entityLoop) == memory.GetmyTeam() || memory.GetEntHealth(memory.entityLoop) == 0)
					continue;

				//find closest target - 10 is bone head 2 is cheast
				if (memory.Distance(memory.GetmyPos(), memory.BonePos(memory.entityLoop, entity.boneMatrix, 10), true) < distance)
				{
					distance = (int)memory.Distance(memory.GetmyPos(), memory.BonePos(memory.entityLoop, entity.boneMatrix, 10), true);
					angle = memory.CalcAngle(memory.GetmyPos(), memory.BonePos(memory.entityLoop, entity.boneMatrix, 10));
					targets++;
				}

			}
						

			if (targets > 0) // just a overcheck if have targets and press 'F'
			{
				//First we write viewangle to target'head position
				memory.ClampAngle(angle);

				WPM<Vector>(memory.proc, (memory.GetEngPointer() + entity.viewAngle), angle);

				//now to shoot we check vPunch, well we don't want to shoot like retards
				if (memory.GetmyaPunch().x == 0.0f && memory.GetmyCrossId() != 0)
				{
					WPM<int>(memory.proc, (memory.clientDll + entity.forceAttack), 5);
					Sleep(25); //need to find best sleep
					WPM<int>(memory.proc, (memory.clientDll + entity.forceAttack), 4);
					Sleep(70);//maybe add a Sleep here too.
					//wee shoot but we need to reset distance to find next
					distance = 100;	
					targets = 0;
				}
			}

			if (targets == 0)
			{
				distance = 100;
				targets = 0;
			}

		}
		else
		{
			distance = 100;
			targets = 0;
		}

		

		if (!memory.aim)
			break;

		Sleep(1);
	}
	return 0;
}

void Memory::StartTrigger()
{
	HANDLE start = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Trigger, NULL, 0, NULL);
}

/*THIS TRIGGER ONLY WORKS AFTER ALL ENEMYS JOIN THE ENEMY TEAM/IF you change team and a new target join it works too.
SO THIS A TRIGGER BOT FOR MM VERSION or you can wait everybody join and join after
* looking for a solution at thi moment: case same team and enter new target in other team, how update it?
a) Check teams
a.1) Create list of targets checking vaid entity an team
b) Check is we are in same team yet
b.1) Loop only valid targets
b.2) loop target and check crosshair id and target id and target's health
b.3) shoot
*/
DWORD Memory::Trigger(LPVOID lParam)
{
	memory.trigger = true;
	std::vector<DWORD> enemys;
	int oldTeam = 0;
	while (true)
	{
		//a)
		if (memory.GetmyTeam() != oldTeam)
		{
			oldTeam = memory.GetmyTeam(); // since we are in a differnt team set the old to actual

			enemys.clear(); //clear to get new enemys address's
			//a.1)
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

		//b)
		if (memory.GetmyTeam() == oldTeam) //i'm in the same team yet, so i don't need to get all entitys again (loop/RPM 64 times again)
		{	//b.1)	
			for (std::vector<DWORD>::size_type i = 0; i != enemys.size(); ++i) //internal loop enemys/targets
			{	//b.2)	
				if (memory.GetEntId(enemys[i]) == memory.GetmyCrossId() && memory.GetEntHealth(enemys[i]) > 0) //entity id is equal to our crosshairId?
				{
					//added punch test to not shoot like idiot
					if (!memory.aim && memory.GetmyaPunch().x < 0.1f)
					{
						//b.3) shoot: write to the memory +attack / -attack
						memory.Wpm = true;
						Sleep(25);
						WPM<int>(memory.proc, (memory.clientDll + entity.forceAttack), 5);
						Sleep(25); //need to find best sleep
						WPM<int>(memory.proc, (memory.clientDll + entity.forceAttack), 4);
						Sleep(70);//maybe add a Sleep here too.
						memory.Wpm = false;
					}					
				}
			}
		}

		//to stop thread set memory.thread to false
		if (!memory.trigger)
			break;

		Sleep(16);//Sleep(1) is overkill
	}

	return 0;
}

void Memory::StartReadMemory() //call this function to start ReadMemory thread
{
	HANDLE start = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReadMemory, NULL, 0, NULL);
}

DWORD Memory::ReadMemory(LPVOID lParam) // thread: ReadMemory where we get data from memory's game
{
	/*
	Your can use memori.GetmyHealth() e.g to retreive localPlayer health
	*/
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
