//
// Created by krave on 24/11/2020.
//
#include "Bankomat_1.h"
#include <iostream>
Bankomat::Bankomat()
    : Bankomat("KravetsBank"){}

Bankomat::Bankomat(const string &bank)
    : Bankomat(bank, "2312"){}

Bankomat::Bankomat(const string &bank, const string &pass) {
    SetNameOfBank(bank);
    for (int el : {5, 10, 20, 50, 100}) bills[el] = 0;
    password = pass;
}
Bankomat::Bankomat(Bankomat &bankomat) {
    SetNameOfBank(bankomat.NameBank());
    password = bankomat.password;
    bills = bankomat.bills;
    map<string, Account> copy = bankomat.getAccounts();
    for (auto it = copy.begin(); it != copy.end(); ++it){
        add_account(it->first, it->second);
    }
}
Bankomat::Bankomat(Bankomat &&bankomat) {
    SetNameOfBank(bankomat.NameBank());
    bankomat.SetNameOfBank("");
    password = move(bankomat.password);
    bills = move(bankomat.bills);
    map<string, Account> copy = bankomat.getAccounts();
    for (auto it = copy.begin(); it != copy.end(); ++it){
        add_account(it->first, delete_account(it->first));
    }
}
bool Bankomat::insert_card(const string &number, const int pin) {
    if (card != "Not inside" || open) return false;
    try {
        if (Bank::check_pincode(number, pin)){
            card = number;
            return true;
        }
        return false;
    }
    catch (WrongOperation &e) {
        throw;
    }
}
