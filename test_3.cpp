//#include <iostream>
#include "gtest/gtest.h"
using namespace std;

#include "Bankomat_1.h"

using namespace ::testing;

TEST(test2, add_not_existing_bill_to_account){
    Bankomat b("KravetsBank");
    b.add_account("1234123412341234", 1234, ("KravetsBank"));
    b.insert_card("1234123412341234", 1234);
    try{
        int pole[] = {20, 50, 1, 5, 100, 7, 15, 5, 10};
        int size = sizeof(pole)/sizeof(*pole);
        b.put_money(pole, size);
        ASSERT_TRUE(false);
    }
    catch (WrongOperation &e) {
        ASSERT_EQ("unauthorized bill", e.message());
    }

}

TEST(test2, check_balance){
    try {
        Bankomat b("KravetsBank");
        b.add_account("1234567812345678", 1111, ("KravetsBank"));
        b.insert_card("1234567812345678", 1111);
        int money[] =  {5, 10, 20, 50, 100, 100};
        int size = sizeof(money)/sizeof(*money);
        b.put_money(money, size);
        ASSERT_EQ(285, b.balance());
    }
    catch (WrongOperation &e) {
        string err = e.message();
        ASSERT_EQ("Must be ok", err);
    }
}
TEST(test2, give_out1){
    Bankomat b("KravetsBank");
    try{
        b.add_account("1234567812345678", 1111, "KravetsBank");
        b.insert_card("1234567812345678", 1111);
        int money[] =  {5, 10, 20, 50, 100, 100};
        int size = sizeof(money)/sizeof(*money);
        b.put_money(money, size);
        b.give_out_money(250);
        ASSERT_EQ(35, b.balance());
    }
    catch (WrongOperation &e) {
        ASSERT_TRUE(false);
    }
}
TEST(test2, another_bank){
    try{
        Bankomat b("KravetsBank");
        b.add_account("1234567812345678", 1111, ("NewBank"));
        b.insert_card("1234567812345678", 1111);
        int money[] =  {5, 10, 20, 50, 100, 100};
        int size = sizeof(money)/sizeof(*money);
        b.put_money(money, size);
        b.give_out_money(250);
        ASSERT_EQ(25, b.balance());
    }
    catch (WrongOperation &e) {
        ASSERT_TRUE(false);
    }
}
TEST(test2, not_enough_money){
    Bankomat b("KravetsBank");
    b.add_account("1111222233334444", 1111, ("KravetsBank"));
    b.insert_card("1111222233334444", 1111);
    ASSERT_EQ(0, b.balance());
    try {
        b.give_out_money(100);
        ASSERT_TRUE(false);
    }
    catch (WrongOperation &e) {
        ASSERT_EQ("Not enough money", e.message());
    }
}
TEST(test2, not_enough_money_for_commission){
    Bankomat b("KravetsBank");
    b.add_account("1111222233334444", 1111, ("NewBank"));
    b.insert_card("1111222233334444", 1111);
    ASSERT_EQ(0, b.balance());
    try {
        int money[] =  {100};
        int size = sizeof(money)/sizeof(*money);
        b.put_money(money, size);
        ASSERT_EQ(100, b.balance());
        b.give_out_money(100);
        ASSERT_TRUE(false);
    }
    catch (WrongOperation &e) {
        ASSERT_EQ("Not enough money", e.message());
    }
}
TEST(test2, much_operations){
    Bankomat b("KravetsBank");
    try {
        b.add_account("1234123412341234", 1234, ("KravetsBank"));
        b.open_bankomat("2312");
        map<int, int> pole;
        for (int el : {5, 10, 20, 50, 100}) pole[el] = 100;
        map<int, int>* pole1 = &pole;
        b.top_up_an_ATM(pole1);
        b.close_bankomat();
        b.insert_card("1234123412341234", 1234);
        int m1[] = {10, 20, 20, 20, 5, 100, 100, 50, 10, 5, 20};
        int size = sizeof(m1)/sizeof(*m1);
        b.put_money(m1, size);
        ASSERT_EQ(360, b.balance());
        ASSERT_EQ(175, b.give_out_money(175));
        ASSERT_TRUE(b.put_money(m1, size));
        ASSERT_EQ(235, b.give_out_money(235));
        ASSERT_EQ(310, b.balance());
    }
    catch (WrongOperation &e) {
        ASSERT_TRUE(false);
    }
}
TEST(test2, copy_bills_and_accounts){
    Bankomat b;
    b.add_account("1234123412341234", 1234, "KravetsBank");
    int pole[] = {100, 100, 50, 5};
    int *pole1 = pole;
    int size = sizeof(pole)/sizeof(*pole);
    b.insert_card("1234123412341234", 1234);
    b.put_money(pole1, size);
    b.finish_work();
    Bankomat b1(b);
    ASSERT_TRUE(b1.insert_card("1234123412341234", 1234));
    try {
        b1.give_out_money(300);
        ASSERT_TRUE(false);
    }
    catch (WrongOperation &e) {
        ASSERT_EQ("Not enough money", e.message());
    }
    ASSERT_TRUE(b1.give_out_money(200));
}

TEST(test3, make_payment_when_acc_isnt_exist){
    Bankomat b("KravetsBank");
    b.add_account("1111222233334444", 2312, "KravetsBank");
    b.insert_card("1111222233334444", 2312);
    try{
        ASSERT_TRUE(b.make_payment("1234123412341234", 2312));
        ASSERT_TRUE(false);
    }
    catch (WrongOperation &e) {
        ASSERT_EQ(e.message(), "recipient account does not exist");
    }
}
TEST(test3, make_payment_when_not_enough_money){
    Bankomat b("KravetsBank");
    b.add_account("1111222233334444", 2312, "KravetsBank");
    b.add_account("1234123412341234", 2312, "KravetsBank");
    b.insert_card("1111222233334444", 2312);
    try{
        b.make_payment("1234123412341234", 100);
        ASSERT_TRUE(false);
    }
    catch (WrongOperation &e) {
        ASSERT_EQ(e.message(), "Not enough money to complete the transaction");
    }
}
TEST(test3, make_payment){
    Bankomat b("KravetsBank");
    b.add_account("1111222233334444", 2312, "KravetsBank");
    b.add_account("1234123412341234", 2312, "KravetsBank");
    b.insert_card("1111222233334444", 2312);
    int money[] =  {5, 10, 20, 50, 100, 100};
    int size = sizeof(money)/sizeof(*money);
    b.put_money(money, size);
    try{
        ASSERT_TRUE(b.make_payment("1234123412341234", 100));
        ASSERT_EQ(b.balance(), 185);
    }
    catch (...) {
        ASSERT_TRUE(false);
    }
    b.finish_work();
    b.insert_card("1234123412341234", 2312);
    ASSERT_EQ(b.balance(), 100);
}

TEST(test1, take_out){
    Bankomat b("KravetsBank");
    b.add_account("1111222233334444", 1234, ("KravetsBank"));
    b.insert_card("1111222233334444", 1234);
    int money[] = {5, 10, 20, 50, 100};
    int size = sizeof(money)/sizeof(*money);

    b.put_money(money, size);
    b.finish_work();

    map<int, int> pole;
    for (int el : money) pole[el] = 1;
    map<int, int> *pole1 = &pole;
    ASSERT_TRUE(b.open_bankomat("2312"));
    ASSERT_TRUE(b.withdraw_money_from_ATM(pole1));
}
