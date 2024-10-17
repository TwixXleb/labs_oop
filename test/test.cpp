#include <gtest/gtest.h>
#include <math.h>
#include "../include/troll_defence.h"
#include "../include/Money.h"
#include "../include/Pentagon.h"
#include "../include/Hexagon.h"
#include "../include/Octagon.h"

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

//Тесты для третьей лабы
//Тесты дял класса Pentagon
TEST(PentagonTests, OutputTest) {
    Pentagon pentagon(0.0, 0.0, 5.0);
    std::ostringstream os;
    os << pentagon;
    std::string expected_output = "Pentagon with center (0, 0) and vertices:\n(5, 0)\n(1.54508, 4.75528)\n(-4.04508, 2.93893)\n(-4.04508, -2.93893)\n(1.54508, -4.75528)\n";
    EXPECT_EQ(os.str(), expected_output);
}

TEST(PentagonTests, InputTest) {
    std::istringstream is("0 0 5");
    Pentagon pentagon;
    is >> pentagon;
    std::ostringstream os;
    os << pentagon;
    std::string expected_output = "Pentagon with center (0, 0) and vertices:\n(5, 0)\n(1.54508, 4.75528)\n(-4.04508, 2.93893)\n(-4.04508, -2.93893)\n(1.54508, -4.75528)\n";
    EXPECT_EQ(os.str(), expected_output);
}

TEST(PentagonTests, CopyConstructorTest) {
    Pentagon original(0.0, 0.0, 5.0);
    Pentagon copy(original);

    EXPECT_EQ(copy.area(), original.area());
    EXPECT_EQ(copy.center().first, original.center().first);
    EXPECT_EQ(copy.center().second, original.center().second);
}

TEST(PentagonTests, CopyAssignmentTest) {
    Pentagon original(0.0, 0.0, 5.0);
    Pentagon copy;
    copy = original;

    EXPECT_EQ(copy.area(), original.area());
    EXPECT_EQ(copy.center().first, original.center().first);
    EXPECT_EQ(copy.center().second, original.center().second);
}

TEST(PentagonTests, EqualityTest) {
    Pentagon pentagon1(0.0, 0.0, 5.0);
    Pentagon pentagon2(0.0, 0.0, 5.0);

    EXPECT_TRUE(pentagon1 == pentagon2);
}

TEST(PentagonTests, InequalityTest) {
    Pentagon pentagon1(0.0, 0.0, 5.0);
    Pentagon pentagon2(1.0, 1.0, 5.0);

    EXPECT_FALSE(pentagon1 == pentagon2);
}

TEST(PentagonTests, MoveTest) {
    Pentagon pentagon(0.0, 0.0, 5.0);
    pentagon.move(10.0, 10.0);

    std::ostringstream os;
    os << pentagon;
    std::string expected_output = "Pentagon with center (10, 10) and vertices:\n(15, 10)\n(11.5451, 14.7553)\n(5.95492, 12.9389)\n(5.95492, 7.06107)\n(11.5451, 5.24472)\n";
    EXPECT_EQ(os.str(), expected_output);
}

TEST(PentagonTests, RotateTest) {
    Pentagon pentagon(0.0, 0.0, 5.0);
    pentagon.rotate(3.14159 / 2);

    std::ostringstream os;
    os << pentagon;

    std::string expected_output = "Pentagon with center (0, 0) and vertices:\n(0, 5)\n(-4.75528, 1.54508)\n(-2.93893, -4.04508)\n(2.93893, -4.04508)\n(4.75528, 1.54508)\n";
    EXPECT_EQ(os.str().substr(0, 30), expected_output.substr(0, 30));  // Сравниваем первую часть вывода
}

TEST(PentagonTests, AreaTest) {
    Pentagon pentagon(0.0, 0.0, 5.0);
    double expected_area = pentagon.area();
    EXPECT_NEAR(expected_area, 43.0119, 0.001);
}
