//
// Created by krave on 09/12/2020.
//
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <vector>
using namespace std;
class Exception {};

class WrongOperation : public Exception {
    string text;
public:
    explicit WrongOperation(const char *v) { text = v; };
    string message() const { return text; };
};

class Account{
    double balance;
    int pincode;
    string name_bank;
public:
    Account();
    Account(int pin, const string &bank);
    double check_balance() const { return balance;};
    bool check_pin(int pin) const { return pin == pincode;};
    void make_deposit(int money) {balance += money;};
    bool make_withdrawal(double money){
        if (balance >= money){
            balance -= money;
            return true;
        }
        return false;
    };
    string NameOfBank() const { return name_bank;};
};
class Bank {
    int MAXN = 2500;
    double coefficient = 1.04;
    string name = "KravetsBank";
    map<string, Account>accounts;
protected:
    map<string, Account> getAccounts() { return accounts; };
    bool check_pincode(const string &number, const int pin){
        if (accounts.count(number) == 0){
            throw WrongOperation("this account does not exist");
        }
        return accounts[number].check_pin(pin);
    }
    pair<map<int, int>, int>adding_money(map<int, int> money, int *amount, int n) const;
    static map<int, int> issuing_money(map<int, int> money, int amount);
    double check_balance(string &number){ return accounts[number].check_balance();};
    void make_deposit(const string &card, int money) {accounts[card].make_deposit(money);};
    bool make_withdrawal(const string &card, int money){
        if (accounts[card].NameOfBank() != name){
            return accounts[card].make_withdrawal(money*coefficient);
        }
        return accounts[card].make_withdrawal(money);
    };
    bool make_transaction(const string &card_sender, const string &card_recipient, int money){
        if (accounts.count(card_recipient) == 0) {
            throw WrongOperation("recipient account does not exist");
        }
        if (!make_withdrawal(card_sender, money)) {
            throw WrongOperation("Not enough money to complete the transaction");
        }
        accounts[card_recipient].make_deposit(money);
    }

    void SetNameOfBank(const string &name1){name = name1;};
    string GetNameOfBank(){ return name;};

    void add_account(const string &number, Account account) {
        if (accounts.count(number) == 0){
            accounts[number] = account;
        }
        else{
            throw WrongOperation("This account already exists");
        }
    };
    Account delete_account(const string &number){
        for (auto it = accounts.begin(); it != accounts.end(); ++it){
            if (it->first == number){
                Account result = it->second;
                accounts.erase(it);
                return result;
            }
        }
        throw WrongOperation("This account doesn't exist");
    }
public:
    void add_account(const string &number, int pass, const string &bank) {
        if (accounts.count(number) == 0){
            accounts[number] = Account(pass, bank);
        }
        else{
            throw WrongOperation("This account already exists");
        }
    };
};