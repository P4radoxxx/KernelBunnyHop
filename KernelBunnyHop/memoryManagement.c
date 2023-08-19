#pragma warning (disable : 4047 4024 )
#include "memoryManagement.h"


// Read
NTSTATUS KernelReadVirtualMemory(PEPROCESS process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size)
{
    PSIZE_T BytesReturned;

    return MmCopyVirtualMemory(process, SourceAddress, PsGetCurrentProcess(), TargetAddress, Size, KernelMode, &BytesReturned);
}


// Write
NTSTATUS KernelWriteVirtualMemory(PEPROCESS process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size)
{
    PSIZE_T BytesReturned;

    return MmCopyVirtualMemory(PsGetCurrentProcess(), SourceAddress, process, TargetAddress, Size, KernelMode, &BytesReturned);
}
