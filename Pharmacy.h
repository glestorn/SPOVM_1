#pragma once
class Pharmacy {
public:
    Pharmacy(char* subj, char* amount);
    ~Pharmacy();

    void check_medicine(char* medicine, char* coins);
    void give_medicine(int coins_amount);
};
