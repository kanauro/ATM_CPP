#include "gtest/gtest.h"
using namespace std;

#include "Bankomat_1.h"

using namespace ::testing;

TEST(test4, printBankomat){
    Bankomat b;
    ASSERT_EQ("__________________________________\n"
    "|                        | [ < ] |\n"
    "|                        |       |\n"
    "|                        | [ < ] |\n"
    "|                        |       |\n"
    "|  Please insert a card  | [ < ] |\n"
    "|                        |       |\n"
    "|                        | [ < ] |\n"
    "|                        |       |\n"
    "|                        | [ < ] |\n"
    "|--------------------------------|\n"
    "| _____________                  |\n"
    "| | 1 | 2 | 3 |                  |\n"
    "| |-----------|                  |\n"
    "| | 4 | 5 | 6 |                  |\n"
    "| |-----------|                  |\n"
    "| | 7 | 8 | 9 |     [ enter  ]   |\n"
    "| |___________|     [ cancel ]   |\n"
    "|________________________________|", b.printATM());
}

TEST(test4, print_with_card_inside){
    Bankomat b;
    b.add_account("1234567887654321", 1111, "NewBank");
    b.insert_card("1234567887654321", 1111);
    ASSERT_EQ("__________________________________\n"
    "|   Take out the money   | [ < ] |\n"
    "|                        |       |\n"
    "|    top up the card     | [ < ] |\n"
    "|                        |       |\n"
    "|      make_payment      | [ < ] |\n"
    "|                        |       |\n"
    "|     check balance      | [ < ] |\n"
    "|                        |       |\n"
    "|      finish work       | [ < ] |\n"
    "|--------------------------------|\n"
    "| _____________                  |\n"
    "| | 1 | 2 | 3 |                  |\n"
    "| |-----------|                  |\n"
    "| | 4 | 5 | 6 |                  |\n"
    "| |-----------|                  |\n"
    "| | 7 | 8 | 9 |     [ enter  ]   |\n"
    "| |___________|     [ cancel ]   |\n"
    "|________________________________|", b.printATM());
}
TEST(test4, printCheck){
    Bankomat b;
    b.add_account("1234123412341234", 1234, "KravetsBank");
    b.add_account("1111222233334444", 1111, "KravetsBank");
    int pole[] = {100, 100, 5, 20, 50};
    int size = sizeof(pole)/sizeof(*pole);
    b.insert_card("1234123412341234", 1234);
    b.put_money(pole, size);
    b.give_out_money(100);
    b.give_out_money(100);

    b.make_payment("1111222233334444", 50);
    ASSERT_EQ(25, b.balance());
    ASSERT_EQ("________________________________\n"
              "|                              |\n"
              "|         KravetsBank          |\n"
              "|                              |\n"
              "|  cash withdrawal: 100 EUR    |\n"
              "|  deposit: 275 EUR            |\n"
              "|  transaction: 50 EUR         |\n"
              "|                              |\n"
              "|                              |\n"
              "|          30-01-2021          |\n"
              "|                              |\n"
              "--------------------------------\n", b.finish_work(true));
}
TEST(test4, emptyCheck){
    Bankomat b;
    b.add_account("1234123412341234", 1234, "KravetsBank");
    int pole[] = {100, 100, 5, 20, 50};
    int size = sizeof(pole)/sizeof(*pole);
    b.insert_card("1234123412341234", 1234);
    b.put_money(pole, size);
    b.finish_work(false);
    b.insert_card("1234123412341234", 1234);
    ASSERT_EQ(275, b.balance());
    ASSERT_EQ("", b.finish_work(true));
}