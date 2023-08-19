#pragma once
#pragma warning (disable : 4047 4024)

#include <ntifs.h>

// Copy memory from a process to another process
NTSTATUS NTAPI MmCopyVirtualMemory
(
    PEPROCESS SourceProcess,
    PVOID SourceAddress,
    PEPROCESS TargetProcess,
    PVOID TargetAddress,
    SIZE_T BufferSize,
    KPROCESSOR_MODE PreviousMode,
    PSIZE_T ReturnSize
);


// Read
NTSTATUS KernelReadVirtualMemory(PEPROCESS process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size);


// Write
NTSTATUS KernelWriteVirtualMemory(PEPROCESS process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size);

