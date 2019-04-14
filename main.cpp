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
			Pharmacy request(argv[1],argv[2]);
        }
    }
    catch (...) {
        return 1;
    }

    return 0;
}