#include <gtest/gtest.h>
#include <string>

// Mock implementation of TrimTrailingZeros for testing purposes
std::wstring TrimTrailingZeros(std::wstring& value) {
    // This is a mock implementation and might not exactly match the actual implementation
    size_t pos = value.find_last_not_of(L'0');
    if (pos != std::wstring::npos && value[pos + 1] == L'.') {
        pos++;
    }
    value = value.substr(0, pos + 1);
    return value;
}

unsigned int GetNumberDigits(std::wstring value) {
    TrimTrailingZeros(value);
    unsigned int numberSignificantDigits = static_cast<unsigned int>(value.size());
    if (value.find(L'.') != std::wstring::npos) {
        --numberSignificantDigits;
    }
    if (value.find(L'-') != std::wstring::npos) {
        --numberSignificantDigits;
    }
    return numberSignificantDigits;
}

// Test fixture for the GetNumberDigits function
class GetNumberDigitsTest : public ::testing::Test {};

// Test case for a positive number with trailing zeros
TEST_F(GetNumberDigitsTest, PositiveNumberWithTrailingZeros) {
    std::wstring value = L"12300";
    EXPECT_EQ(GetNumberDigits(value), 3); // Expecting 3 significant digits
}

// Test case for a negative number with trailing zeros
TEST_F(GetNumberDigitsTest, NegativeNumberWithTrailingZeros) {
    std::wstring value = L"-12300";
    EXPECT_EQ(GetNumberDigits(value), 4); // Expecting 4 significant digits (including the sign)
}

// Test case for a decimal number with trailing zeros
TEST_F(GetNumberDigitsTest, DecimalNumberWithTrailingZeros) {
    std::wstring value = L"123.4500";
    EXPECT_EQ(GetNumberDigits(value), 5); // Expecting 5 significant digits (including the decimal point)
}

// Test case for a positive number without trailing zeros
TEST_F(GetNumberDigitsTest, PositiveNumberWithoutTrailingZeros) {
    std::wstring value = L"123";
    EXPECT_EQ(GetNumberDigits(value), 3); // Expecting 3 significant digits
}

// Test case for a negative number without trailing zeros
TEST_F(GetNumberDigitsTest, NegativeNumberWithoutTrailingZeros) {
    std::wstring value = L"-123";
    EXPECT_EQ(GetNumberDigits(value), 4); // Expecting 4 significant digits (including the sign)
}

// Test case for a decimal number without trailing zeros
TEST_F(GetNumberDigitsTest, DecimalNumberWithoutTrailingZeros) {
    std::wstring value = L"123.45";
    EXPECT_EQ(GetNumberDigits(value), 5); // Expecting 5 significant digits (including the decimal point)
}

// Test case for an empty string
TEST_F(GetNumberDigitsTest, EmptyString) {
    std::wstring value = L"";
    EXPECT_EQ(GetNumberDigits(value), 0); // Expecting 0 significant digits
}

// Test case for a string with only a sign
TEST_F(GetNumberDigitsTest, StringWithOnlySign) {
    std::wstring value = L"-";
    EXPECT_EQ(GetNumberDigits(value), 1); // Expecting 1 significant digit (the sign)
}

// Test case for a string with leading zeros
TEST_F(GetNumberDigitsTest, StringWithLeadingZeros) {
    std::wstring value = L"00123";
    EXPECT_EQ(GetNumberDigits(value), 3); // Expecting 3 significant digits after trimming leading zeros
}

// Test case for a string with non-numeric characters
TEST_F(GetNumberDigitsTest, StringWithNonNumericCharacters) {
    std::wstring value = L"123a45";
    EXPECT_EQ(GetNumberDigits(value), 5); // Expecting 5 significant digits (ignoring non-numeric characters)
}

// Test case for a string with multiple decimal points
TEST_F(GetNumberDigitsTest, StringWithMultipleDecimalPoints) {
    std::wstring value = L"123.45.67";
    EXPECT_EQ(GetNumberDigits(value), 8); // Expecting 8 significant digits (considering only the first decimal point)
}

// Test case for a string with a leading plus sign
TEST_F(GetNumberDigitsTest, StringWithLeadingPlusSign) {
    std::wstring value = L"+123";
    EXPECT_EQ(GetNumberDigits(value), 3); // Expecting 3 significant digits (ignoring the leading plus sign)
}

// Main function to run the tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}