#include "Bankomat_1.h"
#include <iostream>

bool Bankomat::open_bankomat(const string &pass) {
    if (pass != password || open) return false;
    open = true;
    return true;
}
bool Bankomat::close_bankomat() {
    if (!open) return false;
    open = false;
    return true;
}
bool Bankomat::top_up_an_ATM(map<int, int>* money) {
    if (!open) return false;
    map <int, int> new_bills;
    for (auto el : *money){
        if (bills.find(el.first) != bills.end()){
            if(bills[el.first] + el.second > MAXN) return false;
            else new_bills[el.first] = bills[el.first] + el.second;
        }
        else if (el.second > MAXN) return false;
        else new_bills[el.first] = el.second;
    }
    for (auto el : new_bills){
        bills[el.first] = el.second;
    }
    return true;
}
bool Bankomat::withdraw_money_from_ATM(map<int, int> *money) {
    if (!open) return false;
    map <int, int> new_bills;
    for (auto el : *money){
        if (!bills.count(el.first) || bills[el.first] < el.second){
            return false;
        }
        else {
            new_bills[el.first] = bills[el.first] - el.second;
        }
    }
    for (auto el : new_bills) {
        bills[el.first] = el.second;
    }
    return true;
}
