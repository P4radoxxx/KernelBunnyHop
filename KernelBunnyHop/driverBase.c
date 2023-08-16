// https://learn.microsoft.com/en-us/windows-hardware/drivers/kernel/irp-major-function-codes
// https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-iocreatedevice
// https://www.ired.team/miscellaneous-reversing-forensics/windows-kernel-internals/sending-commands-from-userland-to-your-kernel-driver-using-ioctl





// TODO :

//
// Anti-debugging and anti-dump functions, need more docs about that... Also obfuscate and crypt the code.
// ALL! errors handlings, crashing an app is fine, crashing a driver nope, BSOD sucks.
// Think about another way to handle module detection/selection ( or make a base that i can re-use for others games ?)
// Control code for hack functions, will start easy with CSGO and try to beat VAC, shoudn't be hard since it's a user-mode anti-cheat.
// A headers for all CSGO offsets.
// User mode app who will send the control codes is still not coded, but that should be fast enough.

#pragma warning (disable : 4100 4024 4047 4142) // Ca ce compile, mais vu que c'est un driver ce serais mieux de virer les warnings au lieu de les ignorer.
                                               // *** Driver compilation is working fine, but since it's a kernel driver it would be better to fix all warnings
											   // instead of ignoring them :3



#include <ntifs.h>
#include "driverBase.h"
#include "DebugMessages.h"
#include "driverEvents.h"
#include "data.h"
#include "driverComms.h"


//Point d'entrée du driver(main) *** Driver entry point.
NTSTATUS DriverEntry(PDRIVER_OBJECT ptrDriverObject, PUNICODE_STRING ptrRegistryPath)
{
	ptrDriverObject->DriverUnload = driverUnload;
	
	message("RAWR ! I'm a kernel dinosaure !");

	// Fonction qui va notifier le driver chaque fois qu'un module specifique est chargé en mémoire.
	// *** Function to notify the driver that the module we are looking for has been loaded into memory.
	PsSetLoadImageNotifyRoutine(imgCallBack);
	

	// In lack of a better name :D
	RtlInitUnicodeString(&dev, L"\\Device\\kernelR4ptor");
	RtlInitUnicodeString(&dos, L"\\DosDevices\\kernelR4ptor");

	// Creation de l'objet pour le driver
	// *** Creating our object for the driver to use
	IoCreateDevice(
		ptrDriverObject,
		0,
		&dev,
		FILE_DEVICE_UNKNOWN,
		FILE_DEVICE_SECURE_OPEN,
		FALSE,
		&pDeviceObject);


	// Creation du lien symbolique 
	// *** Symlink to device creation
	IoCreateSymbolicLink(&dos, &dev);


	// Les 3 fonctions IRP majeurs, voir la doc pour plus de detail.
	// *** 3 majors IRP functions, see doc for more details
	ptrDriverObject->MajorFunction[IRP_MJ_CREATE] = Call;
	ptrDriverObject->MajorFunction[IRP_MJ_CLOSE] = closeCall;
	ptrDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IOControl;


	ptrDriverObject->Flags |= DO_DIRECT_IO;
	ptrDriverObject->Flags &= ~DO_DEVICE_INITIALIZING;




	return STATUS_SUCCESS;
	
};


// Fonction standard de dechargement du driver, delete les symlinks et l'objet une fois le driver dechargé 
// *** Stadard driver unload function, delete symlinks and the device obj once the driver has been unloaded.
NTSTATUS driverUnload(PDRIVER_OBJECT ptrDriverObject)
{
    message("Driver unloaded succesfully ! Goodbye!"); // devrais être à la fin, une fois les checks passé voir si il a bien été dechargé.
	                                                   // *** Should be at the end, when all the checks for unloading are cleared.
	PsRemoveLoadImageNotifyRoutine(imgCallBack);

	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(ptrDriverObject->DeviceObject);
	return STATUS_SUCCESS;
};