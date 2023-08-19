#include "driverComms.h"
#include "DebugMessages.h"
#include "data.h"
#include "memoryManagement.h"

#pragma warning(disable: 4142 4047 4022)


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



	// Custom control codes logic
	if (controlCode == GET_CLIENT_ADDRESS)
	{
		message("Test control code received! Getting module address now...\n");
		PULONG_PTR output = (PULONG_PTR)irp->AssociatedIrp.SystemBuffer;
		*output = (ULONG_PTR)CSGODllAddress;

		dataFlowControl = STATUS_SUCCESS;
		bytesIO = sizeof(*output);
	}


	else if (controlCode == IO_READ)
	{
		PKERNEL_READ_REQUEST readMemory = (PKERNEL_READ_REQUEST)irp->AssociatedIrp.SystemBuffer;
		PEPROCESS process;

		if (NT_SUCCESS(PsLookupProcessByProcessId(readMemory->processID, &process)))
		{
			// Vu qu'on va lire la valeur retournée depuis le controller en user mode, l'adresse de stockage est le buffer puis le controller recuperera l'adresse du buffer et son contenu.
		    KernelReadVirtualMemory(process, readMemory->address, readMemory->pBuffer, readMemory->size);
			dataFlowControl = STATUS_SUCCESS;
			bytesIO = sizeof(KERNEL_READ_REQUEST);
		}
	}


	else if (controlCode == IO_WRITE)
	{
		PKERNEL_WRITE_REQUEST writeMemory = (PKERNEL_WRITE_REQUEST)irp->AssociatedIrp.SystemBuffer;
		PEPROCESS process;

		if (NT_SUCCESS(PsLookupProcessByProcessId(writeMemory->processID, &process)))
		{
	
	     	KernelWriteVirtualMemory(process, writeMemory->pBuffer, writeMemory->address, writeMemory->size);
			dataFlowControl = STATUS_SUCCESS;
			bytesIO = sizeof(KERNEL_READ_REQUEST);
		}


	}


	else if (controlCode == IO_REQUEST_PROCID)
	{
		

		PULONG output = (PULONG)irp->AssociatedIrp.SystemBuffer;
		*output = processID;

		message("Control code received, getting process ID...");

		dataFlowControl = STATUS_SUCCESS;
		bytesIO = sizeof(*output);



	}







	else
	{
		bytesIO = NULL;
	}



	irp->IoStatus.Status = dataFlowControl;
	irp->IoStatus.Information = bytesIO;
	IoCompleteRequest(irp, IO_NO_INCREMENT);

	
	
	

	return dataFlowControl;
}