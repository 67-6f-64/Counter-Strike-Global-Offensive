# Counter-Strike-Global-Offensive

CS:GO EXTERNAL CHEAT ( Console app)

* Template (RPM, WPM)
* Typedef Vector
* Threads


Threads:

a) ReadMemory (every 5000 ms):  
* localPlayer: Health, Team, Flags, vecPos(x,y,z), crosshairId, playerID;
* -> Weapon info: weaponId, weaponAmmo, weaponReloading;
* entityLoop: Health, Team, Flags, vecPos(x,y,z), entityID;

b) Triggerbot (my own code):  based in team and crosshairId
* works fast with high ping like 90 in net_graph, to test use net_fakelag 40 in command and fakeloss 20
* Tweaked punch again to : -0.09f
* Added ammo count (clip1)
* fixed problem whe new target join team, based in targets id
* added type of host based in distance: long rage Tap-Tap, medium range 2 shots, close range burst(3 shots)

c) Aimbot (my own code): based in target distance
* works fast with high ping like 90 in net_graph, to test use net_fakelag 40 in command and fakeloss 20
* Tweaked punch again to : -0.09f
* Added ammo count (clip1)
* removed useless angle check

d) Noflash: based in color
* need fix when turn off

Work in progress: i will update it alot

* Visual Studio Community 2013 Update 5
* C++
* Win api
* Offset dumper cs:go by Y3t1y3t at: http://www.unknowncheats.me/forum/counterstrike-global-offensive/100856-cs-go-offset-dumper-small-one.html
* Offset dumper cs:go by Zat's at: http://www.unknowncheats.me/forum/counterstrike-global-offensive/129976-zats-csgo-dumper.html
* Configure porjects for Directx: http://www.directxtutorial.com/lessonarticle.aspx?id=4
