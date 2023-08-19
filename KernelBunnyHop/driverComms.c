#include "driverComms.h"
#include "DebugMessages.h"
#include "data.h"

#pragma warning(disable: 4142 4047)


Call(PDEVICE_OBJECT deviceObj, PIRP irp)
{
	UNREFERENCED_PARAMETER(deviceObj);
	
	

	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;

	IoCompleteRequest(irp, IO_NO_INCREMENT);

	message("Call from the usermode received! Connection is OK");

	return STATUS_SUCCESS;
}




CloseCall(PDEVICE_OBJECT deviceObj, PIRP irp)
{

	UNREFERENCED_PARAMETER(deviceObj);
	
	// Check qui va verifier si une requête IRQ est en cours et l'annuler si c'est le cas, fix pour le BSOD  DRIVER_UNLOAD_WITH_PENDING_OPERATIONS
	// quand je decharge le driver.
	KIRQL irql = KeGetCurrentIrql();
	if (irql <= DISPATCH_LEVEL) 
	
	{
		IoReleaseCancelSpinLock(irp->CancelIrql);
	}

	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;

	IoCompleteRequest(irp, IO_NO_INCREMENT);

	message("Connection terminated !");
	

	return STATUS_SUCCESS;


}


IOControl(PDEVICE_OBJECT deviceObj, PIRP irp)
{

	UNREFERENCED_PARAMETER(deviceObj);

	NTSTATUS dataFlowControl = STATUS_UNSUCCESSFUL;
	ULONG bytesIO = 0;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(irp);
	ULONG controlCode = stack->Parameters.DeviceIoControl.IoControlCode;

	// Premier control code custom, cast l'adresse du module dans le pointeur output pour ensuite l'assigner a dllAddress.
	// First custom control code. Cast the address of the module to a pointer, then assign it to dllAddress var
	if (controlCode == GET_CLIENT_ADDRESS)
	{
		message("Test control code received! Getting module address now...\n");
		PULONG_PTR output = (PULONG_PTR)irp->AssociatedIrp.SystemBuffer;
		*output = (ULONG_PTR)dllAddress;

		dataFlowControl = STATUS_SUCCESS;
		bytesIO = sizeof(*output);
	}






	else
	{
		bytesIO = 0;
	}



	irp->IoStatus.Status = dataFlowControl;
	irp->IoStatus.Information = bytesIO;
	IoCompleteRequest(irp, IO_NO_INCREMENT);

	
	
	

	return dataFlowControl;
}