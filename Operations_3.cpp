#include "Bankomat_1.h"
#include <iostream>


bool Bankomat::put_money(int *money, int n) {
    if (open || card == "Not inside") return false;
    try{
        pair<map<int, int>, int>new_bills = adding_money(bills, money, n);
        for (auto it: new_bills.first) bills[it.first] = it.second;

        make_deposit(card, new_bills.second);
        operations["deposit"] = new_bills.second;
        return true;
    }
    catch (WrongOperation &e) {
        throw;
    }

}
int Bankomat::give_out_money(int money) {
    if (open || card == "Not inside") throw WrongOperation("Please, insert card");
    try{
        map <int, int> new_bills = issuing_money(bills, money);
        for (auto it : new_bills){
            bills[it.first] = it.second;
        }
        if (make_withdrawal(card, money)){
            operations["cash withdrawal"] = money;
            return money;
        }
        throw WrongOperation("Not enough money");
    }
    catch (WrongOperation &e) {
        throw;
    }
}
int Bankomat::balance() {
    if (open || card == "Not inside") throw WrongOperation("The operation is not available");
    return check_balance(card);
}

bool Bankomat::make_payment(const string &card1, int money) {
    if (open || card == "Not inside") return false;
    try{
        make_transaction(card, card1, money);
        operations["transaction"] = money;
        return true;
    }
    catch (WrongOperation &e) {
        throw;
    }
}
