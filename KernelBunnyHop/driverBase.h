#pragma once
#include <ntifs.h>


NTSTATUS DriverEntry(PDRIVER_OBJECT ptrDriverObject, PUNICODE_STRING ptrRegistryPath);

NTSTATUS driverUnload(PDRIVER_OBJECT ptrDriverObject);
