# Counter-Strike-Global-Offensive

CS:GO EXTERNAL CHEAT ( Console app)

* Template (RPM, WPM)
* Typedef Vector
* Threads


Threads:

a) ReadMemory (every 5000 ms):  
* localPlayer: Health, Team, Flags, vecPos(x,y,z), crosshairId, playerID;
* entityLoop: Health, Team, Flags, vecPos(x,y,z), entityID;

b) Triggerbot (my own code):  based in team and crosshairId
* Tested with net_faklag 40 (90 in net_graph) and seens work fast yet
* WriteProcessMemory to shoot: need to fix delays but it's working nice already.
* Added punch.x test to shoot again. And aimbot check to not shoot together.

c) Aimbot (my own code): based in target distance
* Not working correctly with high pings, possibly fix remove crossId check
* Need to make work faster with high ping > 80
* note: after fix client.dll addres seens like it's working normally now, need test more

d) Noflash: based in color

Work in progress: i will update it alot

* Visual Studio Community 2013 Update 5
* C++
* Offset dumper cs:go by Y3t1y3t at: http://www.unknowncheats.me/forum/counterstrike-global-offensive/100856-cs-go-offset-dumper-small-one.html
* Offset dumper cs:go by Zat's at: http://www.unknowncheats.me/forum/counterstrike-global-offensive/129976-zats-csgo-dumper.html
