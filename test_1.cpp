//
// Created by krave on 09/12/2020.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

#include "Bankomat_1.h"

using namespace ::testing;

TEST(test1, init){
    Bankomat b;
    ASSERT_EQ("KravetsBank", b.NameBank());
    ASSERT_TRUE(b.open_bankomat("2312"));
}
TEST(test1, copy){
    Bankomat b1("NewBank", "12344321");
    Bankomat b2(b1);
    ASSERT_EQ("NewBank", b2.NameBank());
    ASSERT_TRUE(b2.open_bankomat("12344321"));
    ASSERT_EQ("NewBank", b1.NameBank());
    ASSERT_TRUE(b1.open_bankomat("12344321"));
}
TEST(test1, presuv){
    Bankomat b1("OldBank", "0000");
    Bankomat b2(move(b1));
    ASSERT_EQ("OldBank", b2.NameBank());
    ASSERT_EQ("", b1.NameBank());
}
TEST(test1, card_not_exist){
    string exc;
    Bankomat b("KravetsBank");
    try{
        b.insert_card("0000000000000000", 0000);
        ASSERT_TRUE(false);
    }
    catch (WrongOperation &e){
        exc = e.message();
    }
    ASSERT_EQ("this account does not exist", exc);
}
TEST(test1, card_is_inside){
    Bankomat b("KravetsBank");
    try{
        b.add_account("1234567812345678", 1111, "SomeBank");
        b.add_account("1111222233334444", 1111, "AnyBank");
        ASSERT_TRUE(b.insert_card("1234567812345678", 1111));
        ASSERT_FALSE(b.insert_card("1111222233334444", 1111));
    }
    catch(...){
        ASSERT_TRUE(false);
    }
}
TEST(test1, new_card){
    Bankomat b("KravetsBank");
    try {
        b.add_account("1111222233334444", 1111, ("KravetsBank"));
        b.add_account("1234567812345678", 1111, ("KravetsBank"));
        b.insert_card("1111222233334444", 1111);
        b.finish_work();
        ASSERT_TRUE(b.insert_card("1234567812345678", 1111));
    }
    catch(...){
        ASSERT_TRUE(false);
    }
}
TEST(test1, incorrect_pass){
    string exc;
    Bankomat b("KravetsBank");
    try{
        b.add_account("1111222233334444", 1111, ("KravetsBank"));
        ASSERT_FALSE(b.insert_card("1111222233334444", 1231));
    }
    catch(...){
        ASSERT_TRUE(false);
    }
}
TEST(test1, was_open){
    Bankomat b("KravetsBank");
    b.add_account("1111222233334444", 1111, ("KravetsBank"));
    b.open_bankomat("2312");
    ASSERT_FALSE(b.insert_card("1111222233334444", 1111));
}
TEST(test1, close_and_do){
    Bankomat b("KravetsBank");
    b.add_account("1111222233334444", 1111, ("KravetsBank"));
    b.open_bankomat("2312");
    b.add_account("1111111111111111", 1111, ("KravetsBank"));
    b.close_bankomat();
    ASSERT_TRUE(b.insert_card("1111111111111111", 1111));
}
TEST(test1, open_with_wrong_pass){
    Bankomat b("KravetsBank");
    ASSERT_FALSE(b.open_bankomat("1111"));
}
