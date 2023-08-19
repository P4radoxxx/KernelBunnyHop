Kernel driver utilisant les IOCTL ( I/O Control codes ) recu depuis un controleur en user mode.

Les fonctions principales sont la lecture et l'écriture de la mémoire des process externes en ne passant par aucune fonctions de l'API de Windows,
ce qui rends sa detection plus compliquée.

TODO :
Hacks logics ( ESP, humanized aimbot, snaplines, ect....) just a noflash available now for testing purpose :)
Anti-debug & anti-dump tricks for the driver and controller
Custom driver mapper, it can be loaded/unloaded with GDRVLoader for now.
Add IMGui support to build a GUI and toggle hack functions directly from the game
a lot i'm gonna think of later...


How to use :

1. Compile the driver, you will need Visual Studio and the Driver Developement kit with the Windows SDK.
2. Get GDRVLoader and load the driver.
3. Launch the controller who will automatically send the codes to the driver and disable the grenade flash effect in-game.

WARNING : This is NOT intended to be used in multiplayer games ! Cheating is bad and this code should only be used for learning purpose,
on a local server for testing. If you're an idiot and get VAC banned, that's on you. Even if that shoudn't happen since VAC is a user mode
anti-cheat, but still, don't do it.
