
#include "driverEvents.h"
#include "DebugMessages.h"
#include "data.h"

#pragma warning(disable: 4142 4047 4311 4459 4242 4244)

// Cette partie du code gêre les fonctions/hacks a executer selon le control code reçu
// This part will handle all functions/hacks called by a control code

PLOAD_IMAGE_NOTIFY_ROUTINE imgCallBack(PUNICODE_STRING imgName, HANDLE processId, PIMAGE_INFO imgInfo)

{

	message("DLL loaded -> %ls \n", imgName->Buffer);
	
	if (wcsstr(imgName->Buffer, L"\\Counter-Strike Global Offensive\\csgo\\bin\\client.dll") != NULL)
	{
		message("Image is OK!\n");

		CSGODllAddress = (ULONG_PTR)imgInfo->ImageBase;
		processID = (ULONG)processID;

		message("ProcessID -> %d\n", processId);
	}


	else
	{
		return STATUS_UNSUCCESSFUL	;
	}

	return STATUS_SUCCESS;
}