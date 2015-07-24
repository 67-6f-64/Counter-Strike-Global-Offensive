# Counter-Strike-Global-Offensive

CS:GO EXTERNAL CHEAT ( Console app)

* Template (RPM, WPM)
* Typedef Vector
* Threads


Threads:

a) ReadMemory:  
* localPlayer: Health, Team, Flags, vecPos(x,y,z), crosshairId, playerID;
* entityLoop: Health, Team, Flags, vecPos(x,y,z), entityID;

b) Triggerbot (my own code):  based in team and crosshairId
* Tested with net_faklag 40 (90 in net_graph) and seens work fast yet
* WriteProcessMemory to shoot: need to fix delays but it's working nice already.

c) Aimbot (my own code): based in target distance
* Not working correctly with high pings, possibly fix remove crossId check
* Need fix, not working correctly at all.


Work in progress: i will update it alot

* Visual Studio Community 2013 Update 5
* C++
* Offset dumper cs:go by Y3t1y3t at: http://www.unknowncheats.me/forum/counterstrike-global-offensive/100856-cs-go-offset-dumper-small-one.html
