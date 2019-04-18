#pragma once
//#include <string>
class Person {
public:
    Person();
    ~Person();

    void start_menu();
    void add_amount_of_coins();
    void choose_medicine();
    int  show_amount_of_coins();
    #ifdef __linux__
    void new_process(const char* param1, int param2);
    void showTime();
    #elif _WIN32 | _WIN64
    void new_process(std::string param);
    #endif
};
