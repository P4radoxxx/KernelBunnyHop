#pragma once

#include <iostream> // For std::cout
#include <windows.h> // For HANDLE, DWORD, INVALID_HANDLE_VALUE
#include <winioctl.h> // For DeviceIoControl
#include "comms.hpp"

// Interface vers le driver
class KeInterface {
public:
    HANDLE hR4ptor;

    KeInterface(LPCSTR registryPath) {
        hR4ptor = CreateFileA(registryPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

        if (hR4ptor == INVALID_HANDLE_VALUE) {
            std::cout << "Error! Connection to the driver could not be established :( Make sure it's loaded!" << std::endl;
        }
    }

    DWORD getClientAdress() {
        if (hR4ptor == INVALID_HANDLE_VALUE) {
            std::cout << "Error! Driver connection could not be established!" << std::endl;
            return 0;
        }

        ULONG address = 0;
        DWORD Bytes = 0;

        if (DeviceIoControl(hR4ptor, GET_CLIENT_ADDRESS, &address, sizeof(address), &address, sizeof(address), &Bytes, NULL)) {
            return address;
        }

        return 0;
    }

    DWORD GetProcessID() {
        if (hR4ptor == INVALID_HANDLE_VALUE) {
            return 0;
        }

        ULONG processID;
        DWORD bytes;

        if (DeviceIoControl(hR4ptor, IO_REQUEST_PROCID, &processID, sizeof(processID), &processID, sizeof(processID), &bytes, NULL)) {
            return processID;
        }
        return 0;
    }


    // Thanks MPGH.net for the templates 
    template <typename T>
    T ReadVirtualMemory(ULONG ProcessID, ULONG readAddress, SIZE_T size) {
        T buffer;
        KERNEL_READ_REQUEST readRequest;

        readRequest.processID = ProcessID;
        readRequest.address = readAddress;
        readRequest.pBuffer = &buffer;
        readRequest.size = size;

        DWORD Bytes;

        if (DeviceIoControl(hR4ptor, IO_READ, &readRequest, sizeof(readRequest), &buffer, sizeof(buffer), &Bytes, NULL))
        {
            return buffer;
        }

        return T();
    }


    template <typename T>
    bool WriteVirtualMemory(ULONG ProcessID, ULONG writeAddress, T writeVal, SIZE_T size)
    {
        if (hR4ptor == INVALID_HANDLE_VALUE)
        {
            return false;
        }

        DWORD Bytes;
        KERNEL_WRITE_REQUEST writeRequest;

        writeRequest.processID = ProcessID;
        writeRequest.address = writeAddress;
        writeRequest.pBuffer = reinterpret_cast<PVOID>(&writeVal);
        writeRequest.size = size;

        if (DeviceIoControl(hR4ptor, IO_WRITE, &writeRequest, sizeof(writeRequest), NULL, 0, &Bytes, NULL))
        {
            return true;
        }

        return false;
    }
};
