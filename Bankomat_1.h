//
// Created by kravets on 24/11/2020.
//
#include <string>
#include <vector>
#include <map>
#include "Bank_1.h"
using namespace std;

class Bankomat: public Bank{
    int MAXN = 2500;
    string card = "Not inside";
    bool open = false;
    string password = "2312";
    map<int, int> bills;
    map<string, int> operations;
    string printCheck();
    string getTime();
public:
    Bankomat();
    Bankomat(const string &bank);
    Bankomat(const string &bank, const string &pass);
    Bankomat(Bankomat &bankomat);
    Bankomat(Bankomat &&bankomat);
    bool open_bankomat(const string &pass);
    bool close_bankomat();
    bool top_up_an_ATM(map<int, int>*money);
    bool withdraw_money_from_ATM(map<int, int>*money);
    bool insert_card(const string &number, int pin);
    int give_out_money(int number);
    bool put_money(int *money, int n);
    bool make_payment(const string &card, int money);
//    for uloha 5
    string finish_work(bool print_check);

    void finish_work() { card = "Not inside";};
    int balance();
    string NameBank() { return GetNameOfBank();};
    string printATM();
};

