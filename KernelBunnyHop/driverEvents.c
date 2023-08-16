
#include "driverEvents.h"
#include "DebugMessages.h"
#include "data.h"
#pragma warning (disable : 4047 4100 6273) 

// Cette partie du code gêre les fonctions a executer selon le control code reçu
// This part will handle all functions called by a control code

PLOAD_IMAGE_NOTIFY_ROUTINE imgCallBack(PUNICODE_STRING imgName, HANDLE processId, PIMAGE_INFO imgInfo)

{

	message("DLL loaded -> %ls \n", imgName->Buffer);
	
	if (wcsstr(imgName->Buffer, L"\\imgPath")) // Bad... Vais garder ça pour le debug et pendant que je construis le driver mais
		                                       // ce serais mieux de pouvoir selectionner le process ou d'avoir un input pour choisir le module
		                                       // *** Bad code, would be better to be able to select the loaded module or have some usr input. 
	{
		message("Image is OK ! \n");
		
		dllAddress = imgInfo->ImageBase;

		message("ProcessID -> %d \n", processId);
		
	}

	else
	{
		return STATUS_UNSUCCESSFUL;
	}

	return STATUS_SUCCESS;
}