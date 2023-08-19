// R4ptorController.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "KernelInterface.hpp"



int main()
{

    KeInterface driver = KeInterface("\\\\.\\kernelR4ptor");

    ULONG address = driver.getClientAdress();

    std::cout << "RAWR!" << address << std::endl;

    
    std::cout << "Hello r4ptor RAWR!\n";
}

