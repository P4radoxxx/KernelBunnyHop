
#include "driverEvents.h"
#include "DebugMessages.h"
#include "data.h"

#pragma warning(disable: 4142 4047)

// Cette partie du code gêre les fonctions a executer selon le control code reçu
// This part will handle all functions called by a control code

PLOAD_IMAGE_NOTIFY_ROUTINE imgCallBack(PUNICODE_STRING imgName, HANDLE processId, PIMAGE_INFO imgInfo)

{

	message("DLL loaded -> %ls \n", imgName->Buffer);
	
	if (wcsstr(imgName->Buffer, L"\\imgPath") != NULL)
	{
		message("Image is OK!\n");

		dllAddress = (ULONG_PTR)imgInfo->ImageBase;

		message("ProcessID -> %d\n", processId);
	}


	else
	{
		return STATUS_UNSUCCESSFUL	;
	}

	return STATUS_SUCCESS;
}