////
//// Created by krave on 09/12/2020.
////
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

#include "Bankomat_1.h"

using namespace ::testing;

TEST(test2, put_money){
    Bankomat b("KravetsBank");
    b.open_bankomat("2312");
    map<int, int> pole;
    pole[5] = 100;
    pole[10] = 100;
    pole[17] = 200;
    pole[20] = 100;
    pole[100] = 400;
    map<int, int>* pole1 = &pole;
    try{
        ASSERT_TRUE(b.top_up_an_ATM(pole1));
    }
    catch (WrongOperation &e) {
        ASSERT_EQ("should have been fine", e.message());
    }
}
TEST(test2, put_over){
    Bankomat b("KravetsBank");
    b.open_bankomat("2312");
    int pole[] = {100, 200, 300, 400, 2600};
    int pole2[] = {5, 20, 10, 100, 50};
    map<int, int> banknotes;
    for (int i : {0, 1, 2, 3, 4}) banknotes[pole2[i]] = pole[i];
    map<int, int>* pole1 = &banknotes;
    ASSERT_FALSE(b.top_up_an_ATM(pole1));
}
TEST(test2, put_in_close) {
    Bankomat b("KravetsBank");
    map<int, int> pole;
    pole.insert(pair<int, int>(5, 100));
    pole.insert(pair<int, int>(10, 200));
    pole.insert(pair<int, int>(20, 300));
    pole.insert(pair<int, int>(50, 400));
    pole.insert(pair<int, int>(100, 1));
    map<int, int> *pole1 = &pole;
    ASSERT_FALSE(b.top_up_an_ATM(pole1));
}
TEST(test2, take_out_money){
    Bankomat b("KravetsBank");
    map<int, int> pole;
    for (int bill : {5, 10, 20, 50, 100}) pole[bill] = 100;
    map<int, int> *pole1 = &pole;
    b.open_bankomat("2312");
    b.top_up_an_ATM(pole1);
    ASSERT_TRUE(b.withdraw_money_from_ATM(pole1));
}
TEST(test2, take_out_money_of_the_empty) {
    Bankomat b("KravetsBank");
    map<int, int> pole;
    for (int bill : {5, 10, 20, 50, 100}) pole[bill] = 100;
    map<int, int> *pole1 = &pole;
    b.open_bankomat("2312");
    ASSERT_FALSE(b.withdraw_money_from_ATM(pole1));
}


