#include <gtest/gtest.h>
#include "../include/troll_defence.h"
#include "../include/Money.h"

// Тесты для первой лабы
TEST(Troll_01, BasicTest) {
  std::string troll_message_01 = "haha loshara";
  std::string result = troll_defence(troll_message_01);
  EXPECT_EQ(result, "hh lshr");
}

TEST(Troll_02, UpperTest) {
  std::string troll_message_02 = "HAHA LOSHARA";
  std::string result = troll_defence(troll_message_02);
  EXPECT_EQ(result, "HH LSHR");
}

TEST(Troll_03, RandomTest) {
  std::string troll_message_03 = "HahA lOShaRA";
  std::string result = troll_defence(troll_message_03);
  EXPECT_EQ(result, "Hh lShR");
}

TEST(Troll_04, LotOfVowelsTest) {
  std::string troll_message_04 = "aaaaaaaaa losharaaaaaa";
  std::string result = troll_defence(troll_message_04);
  EXPECT_EQ(result, " lshr");
}

// Тесты для второй лабы
TEST(Money_01, set_get_ruble_balance) {
    Money rubles("1025.56");
    std::string result = rubles.check_balance();
    EXPECT_EQ(result, "1 025.56 RUB");
}

TEST(Money_02, set_add_get_ruble_balance) {
    Money rubles("0001025.56");
    rubles.add("500.40");
    std::string result = rubles.check_balance();
    EXPECT_EQ(result, "1 525.96 RUB");
}

TEST(Money_03, set_withdraw_get_ruble_balance) {
    Money rubles("0001025.56");
    rubles.withdraw("400.20");
    std::string result = rubles.check_balance();
    EXPECT_EQ(result, "625.36 RUB");
}

TEST(Money_04, set_convert_get_yens_to_euros_balance) {
    Money yens("556.50", Currency::JPY);
    yens.convert_to(Currency::EUR);
    std::string result = yens.check_balance();
    EXPECT_EQ(result, "3.46 EUR");
}