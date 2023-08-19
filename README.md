Kernel driver utilisant les IOCTL ( I/O Control codes ) recu depuis un controleur en user mode.

Les fonctions principales sont la lecture et l'écriture de la mémoire des process externes en ne passant par aucune fonctions de l'API de Windows,
ce qui rends sa detection plus compliquée.

TODO :
Hacks logics ( ESP, humanized aimbot, snaplines, ect....) just a noflash available now for testing purpose :)
Anti-debug & anti-dump tricks for the driver and controller
Custom driver mapper, it can be loaded/unloaded with GDRVLoader for now.
Add IMGui support to build a GUI and toggle hack functions directly from the game
a lot i'm gonna think of later...


Tuto : 
1. Compiler le driver avec Visual Studio, vous aurez besoin du DDK (Driver Dev Kit) et du SDK de Windows pour ça.
2. Trouvez vous GDRVLoader ( Le driver n'est pas signé ), et chargé le.
3. Bootez le controleur qui enverra automatiquement les control codes au driver et desactivera l'effet de la grenade flash.


ATTENTION : Ce driver n'A PAS POUR BUT d'etre utilisé en multi ! Tricher c'est bad, je n'ai codé ça que par interêt de la sécurité informatique et d'apprendre le fonctionnement des driver au niveau du kernel de Windows bref faites pas les cons, si vous vous faites VAC ban c'est votre problème. Ne l'utilisez que pour des tests sur un serveur local
même si ca devrais passer VAC easy vu que lui n'opère qu'au niveau user.

How to use :

1. Compile the driver, you will need Visual Studio and the Driver Developement kit with the Windows SDK.
2. Get GDRVLoader ( driver is unsigned ) and load the driver.
3. Launch the controller who will automatically send the codes to the driver and disable the grenade flash effect in-game.

WARNING : This is NOT intended to be used in multiplayer games ! Cheating is bad and this code should only be used for learning purpose,
on a local server for testing. If you're an idiot and get VAC banned, that's on you. Even if that shoudn't happen since VAC is a user mode
anti-cheat, but still, don't do it.
