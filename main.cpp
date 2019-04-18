#include <string>
#include<iostream>

#include "Person.h"
#include "Pharmacy.h"

int main(int argc, char* argv[]) 
{
    try {
        if (argc <= 1) {
            Person tmp;
        }
        else {
            //std::cout << "Incorrect inp" << std::endl;
#ifdef __linux__
            Pharmacy request(argv[0],argv[1]);
#elif   _WIN32 | _WIN64
			Pharmacy request(argv[1],argv[2]);
#endif
        }
    }
    catch (...) {
        return 1;
    }

    return 0;
}