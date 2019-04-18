#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
#ifdef __linux__
#include <unistd.h>
#include <sys/wait.h>
#include <thread>
#include <chrono>
#include <ncurses.h>
#elif _WIN32 | _WIN64
#include<windows.h>
#include<conio.h>
#endif

#include"Pharmacy.h"

Pharmacy::Pharmacy(char* medicine, char* coins) 
{
    penicilinCost = 15;
    aspirinCost = 5;
    check_medicine(medicine, coins);
}

Pharmacy::~Pharmacy(){}

void Pharmacy::check_medicine(char* medicine, char* coins) 
{
        if (((std::string)medicine == "Penicilin" || (std::string)medicine == "Aspirin")) {
            give_medicine(atoi(coins), medicine);
        }
        else {
            std::cout << "There is no such medicine in the pharmacy" << std::endl;
        }
}

void Pharmacy::give_medicine(int coins_amount, char* medicine) 
{
	int cost;
	if (!strcmp(medicine,"Penicilin")) {
		cost = penicilinCost;
	}
	else {
		cost = aspirinCost;
	}
    if (coins_amount < cost) {
        std::cout << "You gave not enough money for this medicine" << std::endl;
#ifdef _WIN32
        Sleep(2000);
#endif
        return;
    }

    for (int i = 0; i < 5; i++) {
        #ifdef __linux__
        napms(1000);
        #elif _WIN32 | _WIN64
        if (_kbhit() != 0) {
            break;
        }
        std::cout << ".";
        Sleep(1000);
        #endif
    }
#ifdef __linux__
    std::fstream file("/home/glestorn/CLionProjects/SPOVM_1/Status.txt", std::ios::out | std::ios::trunc);
#elif _WIN32 | _WIN64
	std::fstream file("status.txt", std::ios::out | std::ios::trunc);
#endif
    if (!file.is_open()) {
        std::cout << "/* Some problems with file */" << std::endl;
    }
    else {
        file << (coins_amount - cost);
        file.close();
        std::cout << "Medicine was given" << std::endl;
#ifdef _WIN32
        sleep(2000);
#endif
    }
}