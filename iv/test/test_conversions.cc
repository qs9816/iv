#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <iv/conversions.h>
#include <iv/platform_math.h>

TEST(ConversionsCase, UStringToDoubleTest) {
  using iv::core::StringToDouble;
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("TEST", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble(" T", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble(" T ", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("T ", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("T", false)));
  ASSERT_EQ(0, StringToDouble(" ", false));
  ASSERT_EQ(0, StringToDouble("    ", false));
  ASSERT_EQ(0, StringToDouble("0   ", false));
  ASSERT_EQ(0, StringToDouble(" 0  ", false));
  ASSERT_EQ(0, StringToDouble("0000", false));
  ASSERT_EQ(0, StringToDouble("00  ", false));
  ASSERT_EQ(1, StringToDouble("01  ", false));
  ASSERT_EQ(8, StringToDouble("08  ", false));
  ASSERT_EQ(8, StringToDouble("  08  ", false));
  ASSERT_EQ(8, StringToDouble("  8", false));
  ASSERT_EQ(8, StringToDouble("8", false));
  ASSERT_EQ(1, StringToDouble("0x01", false));
  ASSERT_EQ(15, StringToDouble("0x0f", false));
  ASSERT_EQ(31, StringToDouble("0x1f", false));
  ASSERT_EQ(31, StringToDouble("0x1f   ", false));
  ASSERT_EQ(31, StringToDouble("    0x1f   ", false));
  ASSERT_EQ(31, StringToDouble("    0x1f", false));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("    0x   1f", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("    0 x   1f", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("    0x1 f", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("    0 x1f  ", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("    0X   1f", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("    0 X   1f", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("    0X1 f", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("    00X1f", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("00X1f  ", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("    00X1f  ", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("00X1f", false)));
  ASSERT_EQ(100, StringToDouble("100", false));
  ASSERT_EQ(100, StringToDouble(" 100 ", false));
  ASSERT_EQ(100, StringToDouble("100   ", false));
  ASSERT_EQ(100, StringToDouble("    100", false));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("100T", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("T100", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("100     T", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("         100     T", false)));
  ASSERT_EQ(0, StringToDouble("0", false));
  ASSERT_EQ(0, StringToDouble("", false));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("E0", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("e0", false)));
  ASSERT_EQ(1, StringToDouble("1e0", false));
  ASSERT_EQ(-10, StringToDouble("-10", false));
  ASSERT_EQ(10, StringToDouble("+10", false));
  ASSERT_EQ(-10, StringToDouble(" -10 ", false));
  ASSERT_EQ(10, StringToDouble(" +10 ", false));
  ASSERT_FALSE(iv::core::math::IsFinite(StringToDouble(" +Infinity ", false)));
  ASSERT_FALSE(iv::core::math::IsFinite(StringToDouble(" -Infinity ", false)));
  ASSERT_FALSE(iv::core::math::IsFinite(StringToDouble("+Infinity ", false)));
  ASSERT_FALSE(iv::core::math::IsFinite(StringToDouble("-Infinity ", false)));
  ASSERT_FALSE(iv::core::math::IsFinite(StringToDouble("  +Infinity", false)));
  ASSERT_FALSE(iv::core::math::IsFinite(StringToDouble("  -Infinity", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("Infinity  ty", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("+Infinity t", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("-Infinity t", false)));
  ASSERT_GT(StringToDouble(" +Infinity ", false), 0);
  ASSERT_LT(StringToDouble(" -Infinity ", false), 0);
  ASSERT_EQ(-1.0, StringToDouble("   -1   ", false));
  ASSERT_EQ(1.0, StringToDouble("   +1   ", false));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("   -  1   ", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("   +  1   ", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("+\t1", false)));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("-\t1", false)));

  ASSERT_EQ(32, StringToDouble("0x20", false));
  ASSERT_EQ(0, StringToDouble("0x20", true));

  ASSERT_EQ(1, StringToDouble("1ex", true));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("1ex", false)));

  ASSERT_EQ(0, StringToDouble("0.x", true));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble(".x", true)));

  ASSERT_TRUE(iv::core::math::IsNaN(StringToDouble("0.x", false)));
}

TEST(ConversionsCase, BigNumberTest) {
  using iv::core::StringToDouble;
  ASSERT_FALSE(iv::core::math::IsFinite(StringToDouble("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111", false)));
  ASSERT_LT(StringToDouble("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111e-20000000000", false), 1);
  ASSERT_LT(StringToDouble("-11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111.111111111111111111111111111111111111111111111111111111111111111111e-999", false), 1);
}

TEST(ConversionsCase, DoubleToStringWithRadix) {
  using iv::core::DoubleToStringWithRadix;
  ASSERT_EQ("1010", DoubleToStringWithRadix(10.0, 2));
  ASSERT_EQ("1011", DoubleToStringWithRadix(11.0, 2));
  ASSERT_EQ("22", DoubleToStringWithRadix(10.0, 4));
  ASSERT_EQ("23", DoubleToStringWithRadix(11.0, 4));
  ASSERT_EQ("12", DoubleToStringWithRadix(10.0, 8));
  ASSERT_EQ("13", DoubleToStringWithRadix(11.0, 8));
  ASSERT_EQ("b", DoubleToStringWithRadix(11.0, 16));
  ASSERT_EQ("c", DoubleToStringWithRadix(12.0, 16));
  DoubleToStringWithRadix(std::numeric_limits<double>::max(), 2);
}

TEST(ConversionsCase, Int32ToString) {
  using iv::core::Int32ToString;
  std::string str;
  str.clear();
  Int32ToString(std::numeric_limits<int32_t>::max(), std::back_inserter(str));
  ASSERT_EQ("2147483647", str);
  str.clear();
  Int32ToString(std::numeric_limits<int32_t>::min(), std::back_inserter(str));
  ASSERT_EQ("-2147483648", str);
  str.clear();
  Int32ToString(0, std::back_inserter(str));
  ASSERT_EQ("0", str);
  str.clear();
  Int32ToString(-1, std::back_inserter(str));
  ASSERT_EQ("-1", str);
  str.clear();
  Int32ToString(-9, std::back_inserter(str));
  ASSERT_EQ("-9", str);
  str.clear();
  Int32ToString(-10, std::back_inserter(str));
  ASSERT_EQ("-10", str);
  str.clear();
  Int32ToString(-11, std::back_inserter(str));
  ASSERT_EQ("-11", str);
  str.clear();
  Int32ToString(1, std::back_inserter(str));
  ASSERT_EQ("1", str);
  str.clear();
  Int32ToString(9, std::back_inserter(str));
  ASSERT_EQ("9", str);
  str.clear();
  Int32ToString(10, std::back_inserter(str));
  ASSERT_EQ("10", str);
  str.clear();
  Int32ToString(11, std::back_inserter(str));
  ASSERT_EQ("11", str);
}

TEST(ConversionsCase, UInt32ToString) {
  using iv::core::UInt32ToString;
  std::string str;
  str.clear();
  UInt32ToString(std::numeric_limits<uint32_t>::max(), std::back_inserter(str));
  ASSERT_EQ("4294967295", str);
  str.clear();
  UInt32ToString(std::numeric_limits<uint32_t>::min(), std::back_inserter(str));
  ASSERT_EQ("0", str);
  str.clear();
  UInt32ToString(9, std::back_inserter(str));
  ASSERT_EQ("9", str);
  str.clear();
  UInt32ToString(10, std::back_inserter(str));
  ASSERT_EQ("10", str);
  str.clear();
  UInt32ToString(11, std::back_inserter(str));
  ASSERT_EQ("11", str);
}

TEST(ConversionsCase, Int32ToStringArrayBuffered) {
  using iv::core::Int32ToString;
  std::array<char, 15> buffer;
  {
    char* end =
        Int32ToString(std::numeric_limits<int32_t>::max(), buffer.data());
    ASSERT_EQ(10, std::distance(buffer.data(), end));
    ASSERT_EQ("2147483647", std::string(buffer.data(), end));
  }
  {
    char* end =
        Int32ToString(std::numeric_limits<int32_t>::min(), buffer.data());
    ASSERT_EQ(11, std::distance(buffer.data(), end));
    ASSERT_EQ("-2147483648", std::string(buffer.data(), end));
  }
  {
    char* end = Int32ToString(0, buffer.data());
    ASSERT_EQ(1, std::distance(buffer.data(), end));
    ASSERT_EQ("0", std::string(buffer.data(), end));
  }
  {
    char* end = Int32ToString(-1, buffer.data());
    ASSERT_EQ(2, std::distance(buffer.data(), end));
    ASSERT_EQ("-1", std::string(buffer.data(), end));
  }
  {
    char* end = Int32ToString(-9, buffer.data());
    ASSERT_EQ(2, std::distance(buffer.data(), end));
    ASSERT_EQ("-9", std::string(buffer.data(), end));
  }
  {
    char* end = Int32ToString(-10, buffer.data());
    ASSERT_EQ(3, std::distance(buffer.data(), end));
    ASSERT_EQ("-10", std::string(buffer.data(), end));
  }
  {
    char* end = Int32ToString(-11, buffer.data());
    ASSERT_EQ(3, std::distance(buffer.data(), end));
    ASSERT_EQ("-11", std::string(buffer.data(), end));
  }
  {
    char* end = Int32ToString(1, buffer.data());
    ASSERT_EQ(1, std::distance(buffer.data(), end));
    ASSERT_EQ("1", std::string(buffer.data(), end));
  }
  {
    char* end = Int32ToString(9, buffer.data());
    ASSERT_EQ(1, std::distance(buffer.data(), end));
    ASSERT_EQ("9", std::string(buffer.data(), end));
  }
  {
    char* end = Int32ToString(10, buffer.data());
    ASSERT_EQ(2, std::distance(buffer.data(), end));
    ASSERT_EQ("10", std::string(buffer.data(), end));
  }
  {
    char* end = Int32ToString(11, buffer.data());
    ASSERT_EQ(2, std::distance(buffer.data(), end));
    ASSERT_EQ("11", std::string(buffer.data(), end));
  }
}

TEST(ConversionsCase, UInt32ToStringArrayBuffered) {
  using iv::core::UInt32ToString;
  std::array<char, 15> buffer;
  {
    char* end =
        UInt32ToString(std::numeric_limits<uint32_t>::max(), buffer.data());
    ASSERT_EQ(10, std::distance(buffer.data(), end));
    ASSERT_EQ("4294967295", std::string(buffer.data(), end));
  }
  {
    char* end =
        UInt32ToString(std::numeric_limits<uint32_t>::min(), buffer.data());
    ASSERT_EQ(1, std::distance(buffer.data(), end));
    ASSERT_EQ("0", std::string(buffer.data(), end));
  }
  {
    char* end = UInt32ToString(9, buffer.data());
    ASSERT_EQ(1, std::distance(buffer.data(), end));
    ASSERT_EQ("9", std::string(buffer.data(), end));
  }
  {
    char* end = UInt32ToString(10, buffer.data());
    ASSERT_EQ(2, std::distance(buffer.data(), end));
    ASSERT_EQ("10", std::string(buffer.data(), end));
  }
  {
    char* end = UInt32ToString(11, buffer.data());
    ASSERT_EQ(2, std::distance(buffer.data(), end));
    ASSERT_EQ("11", std::string(buffer.data(), end));
  }
}

TEST(ConversionsCase, StringToIntegerWithRadix) {
  using iv::core::StringToIntegerWithRadix;
  ASSERT_EQ(20, StringToIntegerWithRadix("20", 10, true));
  ASSERT_EQ(20, StringToIntegerWithRadix("20dddd", 10, true));
  ASSERT_EQ(255, StringToIntegerWithRadix("ff", 16, true));
  ASSERT_EQ(600, StringToIntegerWithRadix("go", 36, true));
  ASSERT_TRUE(iv::core::math::IsNaN(StringToIntegerWithRadix("20dddd", 2, true)));
}

TEST(ConversionsCase, ConvertToUInt32) {
  using iv::core::ConvertToUInt32;
  uint32_t target;
  ASSERT_FALSE(ConvertToUInt32("0x0100", &target));
  ASSERT_FALSE(ConvertToUInt32("d0100", &target));
  ASSERT_FALSE(ConvertToUInt32("20e", &target));

  ASSERT_TRUE(ConvertToUInt32("0", &target));
  ASSERT_EQ(0u, target);

  ASSERT_TRUE(ConvertToUInt32("1", &target));
  ASSERT_EQ(1u, target);

  ASSERT_TRUE(ConvertToUInt32("10", &target));
  ASSERT_EQ(10u, target);

  ASSERT_TRUE(ConvertToUInt32("1000", &target));
  ASSERT_EQ(1000u, target);

  ASSERT_FALSE(ConvertToUInt32("0100", &target));

  // big pattern
  ASSERT_TRUE(ConvertToUInt32("4294967290", &target));
  ASSERT_EQ(4294967290UL, target);

  ASSERT_TRUE(ConvertToUInt32("4294967291", &target));
  ASSERT_EQ(4294967291UL, target);

  ASSERT_TRUE(ConvertToUInt32("4294967292", &target));
  ASSERT_EQ(4294967292UL, target);

  ASSERT_TRUE(ConvertToUInt32("4294967293", &target));
  ASSERT_EQ(4294967293UL, target);

  ASSERT_TRUE(ConvertToUInt32("4294967294", &target));
  ASSERT_EQ(4294967294UL, target);

  ASSERT_TRUE(ConvertToUInt32("4294967295", &target));
  ASSERT_EQ(4294967295UL, target);

  ASSERT_FALSE(ConvertToUInt32("4294967296", &target));
  ASSERT_FALSE(ConvertToUInt32("4294967297", &target));
  ASSERT_FALSE(ConvertToUInt32("4294967298", &target));
  ASSERT_FALSE(ConvertToUInt32("4294967299", &target));
  ASSERT_FALSE(ConvertToUInt32("4294967300", &target));
}

TEST(ConversionsCase, BigRadix) {
  {
    const std::string str("0000001000000001001000110100010101100111100010011010101111011");
    EXPECT_EQ(18054430506169724.0, iv::core::StringToIntegerWithRadix(str, 2, false));
  }
  {
    const std::string str("123456789012345678");
    EXPECT_EQ(123456789012345680.0, iv::core::StringToIntegerWithRadix(str, 10, false));
  }
  {
    const std::string str("0x1000000000000081");
    EXPECT_EQ(1152921504606847200.0, iv::core::StringToIntegerWithRadix(str, 16, true));
  }
  {
    const std::string str("0xFFFFFFFFFFFFFB000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010");
    EXPECT_EQ(std::numeric_limits<double>::infinity(), iv::core::StringToIntegerWithRadix(str, 16, true));
  }
}

TEST(ConversionsCase, JSONQuote) {
  std::array<const char*, 32> expected = { {
    "\\u0000",
    "\\u0001",
    "\\u0002",
    "\\u0003",
    "\\u0004",
    "\\u0005",
    "\\u0006",
    "\\u0007",
    "\\b",
    "\\t",
    "\\n",
    "\\u000b",
    "\\f",
    "\\r",
    "\\u000e",
    "\\u000f",
    "\\u0010",
    "\\u0011",
    "\\u0012",
    "\\u0013",
    "\\u0014",
    "\\u0015",
    "\\u0016",
    "\\u0017",
    "\\u0018",
    "\\u0019",
    "\\u001a",
    "\\u001b",
    "\\u001c",
    "\\u001d",
    "\\u001e",
    "\\u001f"
  } };
  std::vector<char> res;
  for (char16_t i = 0; i < 32; ++i) {
    res.clear();
    iv::core::JSONQuote(&i, &i + 1, std::back_inserter(res));
    res.push_back('\0');
    EXPECT_STREQ(expected[i], res.data());
  }
}
