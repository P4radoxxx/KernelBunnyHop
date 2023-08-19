#pragma once

#include "comms.hpp"

// Interface vers le driver
class KeInterface {

public:
    HANDLE hR4ptor;

    KeInterface(LPCSTR registryPath) 
    
    {
        hR4ptor = CreateFileA(registryPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

        if (hR4ptor == INVALID_HANDLE_VALUE)
        {

            std::cout << " Error ! Connection to the driver could be established :( Make sure it's loaded !" << std::endl;
        }
    }

    DWORD getClientAdress() 
    
    {
        if (hR4ptor == INVALID_HANDLE_VALUE) 
        
        {
            std::cout << "Error ! Driver Connection could not be established !" << std::endl;
            return 0;
        }

        ULONG address;
        DWORD Bytes;

        if (DeviceIoControl(hR4ptor, GET_CLIENT_ADDRESS, &address, sizeof(address), &address, sizeof(address), &Bytes, NULL))
        
        {
            return address;
        }


        return 0;   
  
    }
};
