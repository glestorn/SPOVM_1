#pragma once
class Pharmacy {
private:
	int penicilinCost;
	int aspirinCost;
public:
    Pharmacy(char* subj, char* amount);
    ~Pharmacy();

    void check_medicine(char* medicine, char* coins);
    void give_medicine(int coins_amount, char* medicine);
};
