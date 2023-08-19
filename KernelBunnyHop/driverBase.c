// https://learn.microsoft.com/en-us/windows-hardware/drivers/kernel/irp-major-function-codes
// https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-iocreatedevice
// https://www.ired.team/miscellaneous-reversing-forensics/windows-kernel-internals/sending-commands-from-userland-to-your-kernel-driver-using-ioctl


#include <ntifs.h>
#include "driverBase.h"
#include "DebugMessages.h"
#include "driverEvents.h"
#include "data.h"
#include "driverComms.h"
#include <errno.h>


#pragma warning(disable: 4142 4047)

//Point d'entrée du driver(main) *** Driver entry point.
NTSTATUS DriverEntry(PDRIVER_OBJECT ptrDriverObject, PUNICODE_STRING ptrRegistryPath)
{

	NTSTATUS stat = STATUS_SUCCESS;
	// UNICODE_STRING dev,dos;
	// PDEVICE_OBJECT ptrDriverObject = NULL;

	(void)ptrDriverObject;
	(void)ptrRegistryPath;
	
	// Rawr!!
	RtlInitUnicodeString(&dev, L"\\Device\\kernelR4ptor");
	RtlInitUnicodeString(&dos, L"\\DosDevices\\kernelR4ptor");
	
	ptrDriverObject->DriverUnload = driverUnload;
	

	
	message("RAWR ! I'm a kernel dinosaure !");

	// Fonction qui va notifier le driver chaque fois qu'un module specifique est chargé en mémoire.
	// *** Function to notify the driver that the module we are looking for has been loaded into memory.
	PsSetLoadImageNotifyRoutine((PLOAD_IMAGE_NOTIFY_ROUTINE)imgCallBack);

	if (!NT_SUCCESS(stat))
	{

		message("Unable to retrive image from memory ! ");

		return stat;
	}

	

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
	
	// Trop d'etats possible, probablement inutile de tous les gerer. *** Too much states, error handling could be really tedious, probably
	// not usefull to handle all the cases .

	if (!NT_SUCCESS(stat))
	{
		message("Could not create the object for the driver (Status : 0x%X)\n",stat);

		return STATUS_UNSUCCESSFUL;
	}

	else if (stat == STATUS_INSUFFICIENT_RESOURCES)
	{
		message("Unable to allocate ressources for the driver object ! (Status : 0x%X\n",stat);

	}

	else if (stat == STATUS_INVALID_PARAMETER)
	{

		// 
	}


	// Creation du lien symbolique 
	// *** Symlink to device creation
	IoCreateSymbolicLink(&dos, &dev);
	
	if (!NT_SUCCESS(stat))
	{
		message("Could not create the symlink ! Freeing ressources now...");
		IoDeleteDevice(pDeviceObject);

		return stat;
	}



	// Les 3 fonctions IRP majeurs, voir la doc pour plus de detail.
	// *** 3 majors IRP functions, see doc for more details
	ptrDriverObject->MajorFunction[IRP_MJ_CREATE] = Call;
	ptrDriverObject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
	ptrDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IOControl;


	// utilisation d'op bitwise pour les flags de la struct de l'objet du driver, DO_DIRECT_IO donne un accès I/O direct à l'hardware sans passer par le cache système
	// et DO_DEVICE_INITIALIZING est set a 0 indiquant que le driver a finis son process d'init.
	ptrDriverObject->Flags |= DO_DIRECT_IO;
	ptrDriverObject->Flags &= ~DO_DEVICE_INITIALIZING;




	return STATUS_SUCCESS;
	
};


// Unloading function
NTSTATUS driverUnload(PDRIVER_OBJECT ptrDriverObject)
{

	NTSTATUS  SymLinkStat = IoDeleteSymbolicLink(&dos);


	if (!NT_SUCCESS(SymLinkStat))
	{
		message("Symlink was not delete properly !");
		return STATUS_UNSUCCESSFUL;
	}

	// Impossible d'utiliser NTSTATUS pour gerer l'erreur ici vu que le type de ioDeleteDevice est vide et que NTSTATUS ne peux pas être init avec un void.
	// L'objet devrait être null une fois détruit donc on peux check comme ça.

	// *** Unable to use NTSTATUS for errors handling here since ioDeleteDevice func is a void and NTSTATUS doesn't take void types.
	// Will be handled by checking if the object has been nulled since ut's supposed to be once destroyed.

	IoDeleteDevice(ptrDriverObject->DeviceObject);

	if (ptrDriverObject->DeviceObject != NULL)
	{
		message("Unable to destroy driver object properly!");
		return STATUS_UNSUCCESSFUL;

	}


	IoCancelIrp();
	return STATUS_SUCCESS;
}