//
// Created by krave on 09/12/2020.
//
#include "Bank_1.h"
 using namespace std;
Account::Account()
    : balance(0), pincode(0000){}
Account::Account(int pincode1, const string &bank)
    : pincode(pincode1), balance(0), name_bank(bank){}

map<int, int> Bank::issuing_money(map<int, int> money, int amount) {
    int suma = amount;
    map <int, int>banknotes;
    set<int> set_of_banknotes;
    for (auto el : money) {
        banknotes[el.first] = money[el.first];
        set_of_banknotes.insert(el.first);
    }
    auto it = set_of_banknotes.end();
    while (suma > 0){
        if(*it <= suma){
            suma -= *it;
            banknotes[*it] -= 1;
        }
        else{
            if (it == set_of_banknotes.begin()) throw WrongOperation("not enough money or banknotes");
            --it;
        }
    }
    return banknotes;
}
pair<map<int, int>, int>Bank::adding_money(map<int, int> money, int *amount, int n) const {
    int suma = 0;
    map <int, int>banknotes;
    for (auto it = money.begin(); it != money.end(); ++it) {
        banknotes[it->first] = money[it->first];
    }
    for (int i = 0; i < n; i++){
        if (!banknotes.count(amount[i])) throw WrongOperation("unauthorized bill");
        if (banknotes[amount[i]] + 1 > MAXN) throw WrongOperation("the ATM can't process these bills");
        banknotes[amount[i]] += 1;
        suma += amount[i];
    }
    return pair<map<int, int>, int>(banknotes, suma);
}