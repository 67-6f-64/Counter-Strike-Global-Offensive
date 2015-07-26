#include "main.h"
#include "offset.h"


//since our thread is a static one inside a class we need to call the class object here to access functions
Memory memory;


void Memory::StartNoFlash()
{
	memory.noflash = true;
	snF = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)NoFlash, NULL, 0, NULL);

}

DWORD Memory::NoFlash(LPVOID lParam)
{

	DWORD localPlayer = RPM<DWORD>(memory.proc, (memory.clientDll + entity.localPlayer), sizeof(DWORD));

	while (memory.noflash)
	{



		if (memory.GetFlashColor() > 0.0f && memory.GetFlashColor() != 0.0f)
		{
			float newFlashColor = 0.0f;
			WPM<float>(memory.Getproc(), (localPlayer + entity.flFlashMaxAlpha), newFlashColor);
		}


		if (memory.GetFlashColor() == 0.0f && memory.GetFlashColor() != 255.0f)
		{
			float newFlashColor = 255.0f;
			WPM<float>(memory.Getproc(), (localPlayer + entity.flFlashMaxAlpha), newFlashColor);
		}

		Sleep(16);
	}

	return 0;
}


void Memory::StartAim()
{
	sA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Aim, NULL, 0, NULL);
	aim = true;
}

/*
MY AIMBOT LOGIC, you can find other in UC forum, don't forget to credit if using
*/
DWORD Memory::Aim(LPVOID lpParam)
{

	int targets = 0; //number of targets
	int distance = 61; //start value to check distance
	Vector angle; //angle to write to target heads 
	Vector mPos;
	Vector boneP;
	//int shoots = 0;
	while (true)
	{

		/*                                    FIND CLOSETS TARGET                                                   */
		
		//just to test 'F'
		if (GetAsyncKeyState(0x46)) 
		{
			//loop to get enemy's
			for (int i = 0; i < 64; ++i) 
			{
				memory.entityLoop = RPM<DWORD>(memory.proc, ((memory.clientDll + entity.entityBase) + ((i - 1)*entity.loopDistance)), sizeof(DWORD));

				if (memory.entityLoop == NULL) //if entity is not valid
					continue;

				//check for varius things
				if (memory.GetEntDormant(memory.entityLoop) && memory.GetEntTeam(memory.entityLoop) == 0
					|| memory.GetEntTeam(memory.entityLoop) == memory.GetmyTeam() || memory.GetEntHealth(memory.entityLoop) == 0)
					continue;

				//dist myPos and targetHead - bone 10 is head, 2 is cheast
				mPos = memory.GetmyPos();
				boneP = memory.BonePos(memory.entityLoop, entity.boneMatrix, 10);
				int dist = (int)memory.Distance(mPos, boneP, true);

				//find closest target
				if (dist < distance)
				{
					distance = dist;
					angle = memory.CalcAngle(mPos, boneP);
					targets++;
				}
			}

			///* WE HAVE A TARGET LETS SET ANGLE AND SHOOT */

			if (targets > 0) // we have a target?
			{
				//	First we write viewangle to target'head position
				memory.ClampAngle(angle);

				WPM<Vector>(memory.proc, (memory.GetEngPointer() + entity.viewAngle), angle);

				//	now to shoot we check vPunch, well we don't want to shoot like retards
				if (memory.GetmyaPunch().x > -0.09f && memory.GetweaponAmmo() > 0)
				{
					WPM<int>(memory.proc, (memory.clientDll + entity.forceAttack), 1);
					Sleep(25); //need to find better sleep
					WPM<int>(memory.proc, (memory.clientDll + entity.forceAttack), 0);

					//std::cout << "Angle to Write: " << angle.x << "," << angle.y << "," << angle.y << std::endl;
				}
				//reset to find new target
				distance = 61;
				targets = 0;
			}
		}
		else
		{
			distance = 61;
			targets = 0;
		}
		Sleep(16);
	} 
	return 0;
}

void Memory::StartTrigger()
{

	sT = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Trigger, NULL, 0, NULL);
	memory.trigger = true;
}

/* Works with high ping, set net_fakelag 40 to produce ping 90 in net_graph, it shoot fast not like others
a) Check teams
a.1) Create list of targets checking vaid entity an team
a.2) Store target's address and target's ID (2 vectors)

b) Check is we are in same team yet
b.1) Loop only valid targets
b.2) loop target and check crosshair id and target id and target's health
b.3) shoot
IF YOU WANT TO USE PUT CREDITS ty creditc to dmThread or dm0000
*/
DWORD Memory::Trigger(LPVOID lParam)
{
	std::vector<DWORD> enemys;
	std::vector<int> enemysId;
	int oldTeam = 9; //random number, can't be 1,2,3 these are spec tr and ct
	while (true)
	{

		//a) get all targets
		if (memory.GetmyTeam() != oldTeam)
		{
			oldTeam = memory.GetmyTeam(); // since we are in a differnt team set the old to actual

			enemys.clear(); //clear to get new enemys address's
			enemysId.clear(); //clear targets id, used to check crosshair

			//a.1)//loop to get targets
			for (int i = 0; i < 64; ++i)
			{
				memory.entityLoop = RPM<DWORD>(memory.proc, ((memory.clientDll + entity.entityBase) + ((i - 1)*entity.loopDistance)), sizeof(DWORD));

				if (memory.entityLoop == NULL) //if entity is not valid
					continue;

				if (memory.GetEntTeam(memory.entityLoop) != 0 && memory.GetmyTeam() != memory.GetEntTeam(memory.entityLoop)) //if entity is not 0 and is not our team add to vector
				{
					enemys.push_back(memory.entityLoop); //store target address
					enemysId.push_back(memory.GetEntId(memory.entityLoop)); //store target id
				}
			}
			//we have all targets don't need to reload get again

		}

		//b)i'm in the same team yet, so i don't need to get all entitys again (loop/RPM 64 times again)
		if (memory.GetmyTeam() == oldTeam)
		{	
			//b.1) internal loop of targets, vector loop is more fast in c++11/14
			for (std::vector<DWORD>::size_type i = 0; i != enemys.size(); ++i)
			{	
				//b.2) entity id is equal to our crosshairId? if not let's get all targets again, this will prevent a new target wihout address's				
				//if new target enter in enemy team we need to reset the list and find the new target
				//we check for crossHair id contains in list of target's id, if not get targets again.
				if (std::find(enemysId.begin(), enemysId.end(), memory.GetmyCrossId()) == enemysId.end())
				{
					oldTeam = 9;
					break;
				}				

				if (memory.GetEntId(enemys[i]) != memory.GetmyCrossId() || memory.GetweaponAmmo() == 0)
					continue;		
			
				//added punch test to not shoot like idiot , need add check if reloading
				if (memory.GetmyaPunch().x > -0.09f)
				{
					//b.3) shoot: write to the memory +attack / -attack
					//memory.Wpm = true; // check to use aimbot and trigger together
					WPM<int>(memory.proc, (memory.clientDll + entity.forceAttack), 5);

					//shoot logic based in distance
					Vector mPos = memory.GetmyPos();
					Vector boneP = memory.BonePos(enemys[i], entity.boneMatrix, 10);
					
					//SHORT RANGE burst fire ( 3 shots)
					if (memory.Distance(mPos, boneP, true) <= 15)
					{
						Sleep(250); //250 seens fine for ak-47 brust
					}
					//MEDIUN RANGE , 2 shots
					if (memory.Distance(mPos, boneP, true) >= 16 && memory.Distance(mPos, boneP, true) <= 30)
					{
						Sleep(150); //150 seens like 2 shots
					}
					//LONG RANGE - tap tap
					if (memory.Distance(mPos, boneP, true) >= 31)
					{
						Sleep(25); //need to find better sleep
					}


					//Sleep(25); //need to find better sleep
					WPM<int>(memory.proc, (memory.clientDll + entity.forceAttack), 4);
					//memory.Wpm = false;
				} //check to shoot
			} //loop targets
		}// myteam = oldteam


		Sleep(16);
	}//while(true)
	memory.trigger = false;
	return 0;
}

void Memory::StartReadMemory() //call this function to start ReadMemory thread
{
	sRM = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReadMemory, NULL, 0, NULL);
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
		std::cout << "-> Currectly Ammo: " << memory.GetweaponAmmo() << std::endl;
		std::cout << "-> localPlayer Position X: " << memory.GetmyPos().x
			<< " Y: " << memory.GetmyPos().y
			<< " Z: " << memory.GetmyPos().z << std::endl << std::endl;
		std::cout << "My Player weapon info:" << std::endl;
		std::cout << "-> Ammo: " << memory.GetweaponAmmo() << std::endl;
		std::cout << "-> WeaponId: " << memory.GetweaponId() << std::endl;
		std::cout << "-> IsReloading: " << memory.IsWeaponReloading() << std::endl;

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

		if (GetAsyncKeyState(VK_ESCAPE))
		{
			memory.reading = false;
			system("pause");
			ExitProcess(0);
			break;
		}

		if (!memory.reading)
			break;

		Sleep(5000);
	}
	return 0;
}
