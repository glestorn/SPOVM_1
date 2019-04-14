#include<iostream>
#include<string>
#include<fstream>
#ifdef __linux__
#include <unistd.h>
#include <sys/wait.h>
#elif _WIN32 | _WIN64
#include<windows.h>
#include<conio.h>
#endif

#include"Pharmacy.h"

Pharmacy::Pharmacy(char* medicine, char* coins) 
{
    check_medicine(medicine, coins);
}

Pharmacy::~Pharmacy(){}

void Pharmacy::check_medicine(char* medicine, char* coins) 
{
        if (((std::string)medicine == "Penicilin" || (std::string)medicine == "Aspirin")) {
            give_medicine(atoi(coins));
        }
        else {
            std::cout << "There is no such medicine in the pharmacy" << std::endl;
			Sleep(2000);
        }
}

void Pharmacy::give_medicine(int coins_amount) 
{
    if (coins_amount != 0) {
        for (coins_amount; coins_amount > 0; coins_amount--) {
            #ifdef __linux__
            if (_kbhit() != 0) {
                break;
            }
            std::cout << ".";
            Sleep(1000);
            #elif _WIN32 | _WIN64
            if (_kbhit() != 0) {
                break;
            }
            std::cout << ".";
            Sleep(1000);
            #endif
        }
        
        std::fstream file("status.txt", std::ios::out | std::ios::trunc);

        if (!file.is_open()) {
            std::cout << "/* Some problems with file */" << '\n';
        } 
        else {
            file << coins_amount;
            file.close();
            std::cout << "Medicines were given" << std::endl;
            Sleep(2000);
        }
    }
    else {
        std::cout << "No labs" << std::endl;
        Sleep(2000);
    }
}