#include "Bankomat_1.h"
#include <iostream>
#include <ctime>
string Bankomat::finish_work(bool print_check) {
    card = "Not inside";
    string result = "";
    if (print_check) result = printCheck();
    operations.clear();
    return result;
}
string Bankomat::printATM() {
    string bankomat = "__________________________________\n";
    if (card == "Not inside"){
        bankomat += "|                        | [ < ] |\n"
                    "|                        |       |\n"
                    "|                        | [ < ] |\n"
                    "|                        |       |\n"
                    "|  Please insert a card  | [ < ] |\n"
                    "|                        |       |\n"
                    "|                        | [ < ] |\n"
                    "|                        |       |\n"
                    "|                        | [ < ] |\n";
    }
    else{
        bankomat += "|   Take out the money   | [ < ] |\n"
                    "|                        |       |\n"
                    "|    top up the card     | [ < ] |\n"
                    "|                        |       |\n"
                    "|      make_payment      | [ < ] |\n"
                    "|                        |       |\n"
                    "|     check balance      | [ < ] |\n"
                    "|                        |       |\n"
                    "|      finish work       | [ < ] |\n";
    }
    bankomat += "|--------------------------------|\n"
                "| _____________                  |\n"
                "| | 1 | 2 | 3 |                  |\n"
                "| |-----------|                  |\n"
                "| | 4 | 5 | 6 |                  |\n"
                "| |-----------|                  |\n"
                "| | 7 | 8 | 9 |     [ enter  ]   |\n"
                "| |___________|     [ cancel ]   |\n"
                "|________________________________|";
    return bankomat;
}
string Bankomat::getTime() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y",timeinfo);
    string str(buffer);
    return buffer;
}
string Bankomat::printCheck() {
    if (operations.size() == 0) return "";
    string result = "________________________________\n"
                    "|                              |\n"
                    "|";
    int tab = ((30 - NameBank().size()) - (30 - NameBank().size())%2)/2;
    for (int i = 0; i < tab; i++) result += " ";
    result += NameBank();
    for (int i = 0; i < tab + (30 - NameBank().size())%2; i++) result += " ";
    result += "|\n|                              |\n";
    for (auto el : operations){
        string op = el.first + ": " + to_string(el.second) + " EUR";
        result += "|  " + op;
        for (int i = 0; i < 28 - op.size(); i++) result += " ";
        result += "|\n";
    }
    result += "|                              |\n"
              "|                              |\n|";
    tab = ((30 - getTime().size()) - (30 - getTime().size())%2)/2;
    for (int i = 0; i < tab; i++) result += " ";
    result += getTime();
    for (int i = 0; i < tab+(30 - getTime().size())%2; i++) result += " ";
    result += "|\n"
              "|                              |\n"
              "--------------------------------\n";
    return result;
}


