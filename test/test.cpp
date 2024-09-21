#include <gtest/gtest.h>
#include "../include/troll_defence.h"

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