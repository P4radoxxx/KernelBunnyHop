#pragma once
#include <ntifs.h>

PLOAD_IMAGE_NOTIFY_ROUTINE imgCallBack(PUNICODE_STRING imgName, HANDLE processId, PIMAGE_INFO imgInfo);

