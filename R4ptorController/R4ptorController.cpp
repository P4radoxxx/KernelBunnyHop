// R4ptorController.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "KernelInterface.hpp"
#include "GameOffsets.hpp"



int main()
{

    KeInterface driver = KeInterface("\\\\.\\kernelR4ptor");

    ULONG address = driver.getClientAdress();
    ULONG processId = driver.GetProcessID();

    std::cout << "RAWR!" << address << std::endl;

    // No flash hack, easy à faire juste une valeur a reecrire, juste pour les tests.
    while (true)

    {
        // Lecture de l'adresse de la structure du player
        uint32_t localPlayerAddress = driver.ReadVirtualMemory<uint32_t>(processId,address + hazedumper::signatures::dwLocalPlayer,sizeof(uint32_t));

        // Set la couche alpha de l'effet de la grenade flash à 0, complètement transparent.
        driver.WriteVirtualMemory(processId, localPlayerAddress + hazedumper::netvars::m_flFlashMaxAlpha, 0.f, sizeof(float));
    }

}

