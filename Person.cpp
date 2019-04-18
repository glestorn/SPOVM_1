#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include"Person.h"
#ifdef __linux__
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include<cstring>
#include<ncurses.h>
#elif _WIN32 | _WIN64
#include<windows.h>
#endif



Person::Person() {
    start_menu();
}

Person::~Person() {}

void Person::start_menu() {
    do {
        #ifdef __linux__
        system("clear");
        #elif _WIN32 | _WIN64
        system("CLS");
        #endif
        std::cout << "Choose action:" << std::endl
            << "1 - Add amount of coins" << std::endl
            << "2 - Choose medicine" << std::endl
            << "3 - Show amount of coins" << std::endl
            << "4 - Quit" << std::endl;
        int choose;
        std::cin >> choose;
        switch (choose) {
			case 1: add_amount_of_coins();  break;
			case 2: choose_medicine();      break;
			case 3: show_amount_of_coins(); break;
			case 4: exit(0);
			default: std::cout << "Incorrect input" << std::endl; break;
        }
        #ifdef __linux__
        std::cout << "Press any key to continue..." << '\n';
        char ch;
        std::cin >> ch;
        #elif _WIN32 | _WIN64
        system("pause");
        #endif
    } while (true);
}



void Person::add_amount_of_coins() 
{
	#ifdef __linux__
    system("clear");
    #elif _WIN32 | _WIN64
    system("CLS");
    #endif
	int num_of_coins;
	int file_buff = 0;
	std::cout << "Enter amount of coins to add: ";
	std::cin >> num_of_coins;

	std::fstream file("/home/glestorn/CLionProjects/SPOVM_1/Status.txt", std::ios::in);
	if (!file.is_open()) {
		perror("Impossible to open file\n");
		return;
	}

	try {
		file >> file_buff;
	}
	catch (...) {
		printf("No data");
	}
	file.close();
	file_buff += num_of_coins;
	file.open("/home/glestorn/CLionProjects/SPOVM_1/Status.txt", std::ios::out | std::ios::trunc);
	if (!file.is_open()) {
		perror("Impossible to open file\n");
		return;
	}
	file << file_buff;
	std::cout << "Successfully added" << std::endl;
	file.close();
}

void Person::choose_medicine() 
{
    #ifdef __linux__
    system("clear");
    #elif _WIN32 | _WIN64
    system("CLS");
    #endif
    std::cout << "Choose medicine:" << std::endl
        << "1 - Penicilin (cost 15)" << std::endl
        << "2 - Aspirin (cost 5)" << std::endl
        << "3 - ETC" << std::endl;
    int choose;
    std::cin >> choose;
    const char* peni = "Penicilin";
    const char* asp = "Aspirin";
    const char* etc = "ETC";
    #ifdef __linux__
    switch (choose) {
        case 1:new_process(peni, show_amount_of_coins()); break;
        case 2:new_process(asp, show_amount_of_coins());  break;
        case 3:new_process(etc,show_amount_of_coins());   break;
    }
    #elif _WIN32 | _WIN64
	switch (choose) {
		case 1: {
			std::string peni = "Penicilin " + std::to_string(show_amount_of_coins());
			new_process(peni);
			break;
		}
		case 2: {
			std::string asp = "Aspirin " + std::to_string(show_amount_of_coins());
			new_process(asp);
			break;
		}
		case 3: {
			std::string etc = "ETC " + std::to_string(show_amount_of_coins());
			new_process(etc);
		}
	}
    #endif
}



int Person::show_amount_of_coins() 
{
    #ifdef __linux__
    system("clear");
    #elif _WIN32 | _WIN64
    system("CLS");
    #endif
    std::fstream file("/home/glestorn/CLionProjects/SPOVM_1/Status.txt", std::ios::in);
    if (!file.is_open()) {
        perror("Impossible to open file\n");
        return 0;
    }
    int file_buff;
    try {
        file >> file_buff;
    }
    catch (...) {
		printf("No data");
    }
    file.close();
    std::cout << "Total amount of coins: " << file_buff << std::endl;
    return file_buff;
}

#ifdef __linux__

void Person::new_process(const char* param1, int param2)
{
    system("clear");
    char str[11];
  sprintf(str, "%d", param2);
  pid_t pid = fork();
  initscr();
  noecho();
  curs_set(0);
  int state;
  if (pid < 0) {
      std::cout << "Unlucky attempt!" << std::endl;
      return;
  }
  else if (pid > 0){
      time_t ltime;
      while(true){
          showTime(ltime);

          if(waitpid(pid, &state, WNOHANG) > 0) {
              napms(1000);
              break;
          }
          napms(1);
      }
  }
  else {
    if(execlp("./main", param1, str, NULL) == -1) {
      std::cout << "Error" << '\n';
    }

    exit(0);
  }

  endwin();
}

void Person::showTime(time_t ltime)
{
    refresh();
    time(&ltime);
    move(0, 0);
    printw(ctime(&ltime));
}


#elif _WIN32 | _WIN64
void Person::new_process(std::string param) 
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    std::string cmd_str = "SPOVM_1 " + param;

    if (!CreateProcess(NULL,					// No module name (use command line)
					   (LPSTR)cmd_str.c_str(),	// Command line
					   NULL,					// Process handle not inheritable
					   NULL,					// Thread handle not inheritable
					   FALSE,					// Set handle inheritance to FALSE
					   CREATE_NEW_CONSOLE,		// lol
					   NULL,					// Use parent's environment block
					   NULL,					// Use parent's starting directory 
					   &si,						// Pointer to STARTUPINFO structure
					   &pi)						// Pointer to PROCESS_INFORMATION structure
        ) {
        printf("CreateProcess failed (%d)\n", GetLastError());
    }

    SYSTEMTIME lt;
    clock_t beg, end;
    beg = clock();
    while (WaitForSingleObject(pi.hProcess, 50)) {
        GetLocalTime(&lt);
        printf("Local time: %02d:%02d:%02d \r", lt.wHour, lt.wMinute, lt.wSecond);
    }
    end = clock();
    std::cout << std::endl;
    std::cout << "Child process runtime: " << (double)(end - beg) / CLK_TCK << std::endl;
    CloseHandle(pi.hProcess);
}

#endif