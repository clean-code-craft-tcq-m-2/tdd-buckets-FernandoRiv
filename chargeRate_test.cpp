#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "chargeRate.h"
#include <string.h>

TEST_CASE("Characters to int test conversion"){
    std::list<SessionVal> sessionValues = {};
    SECTION("Addition of digit character input"){
        char digit[] = "12";
        REQUIRE(addDirectSession(digit, sessionValues) == true);
    }
    SECTION("Attempt of non digit character input"){
        char nonDigit[] = "HI";
        REQUIRE(addDirectSession(nonDigit, sessionValues) == false);
    }
    SECTION("Attempt of non digit special characters"){
        char nonDigitSpecialChars[] = "/0";
        REQUIRE(addDirectSession(nonDigitSpecialChars, sessionValues) == false);
    }
    SECTION("Attempt of nullptr at character input"){
        REQUIRE(addDirectSession(nullptr, sessionValues) == false);
    }
    SECTION("Attempt of digit + non digit at character input"){
        char digitNonDigit[] = "12CD1";
        REQUIRE(addDirectSession(digitNonDigit, sessionValues) == false);
    }
    sessionValues.clear();
}

TEST_CASE("Parsing array of direct current samples"){
    std::list<SessionVal> sessionValues = {};
    SECTION("Smallest set of valid digit sequences"){
        char sessions[] = "4, 5";
        REQUIRE(parseDirectChargeSession(sessions, sessionValues) == true);
        REQUIRE(sessionValues.size() == 2);
    }
    SECTION("Digit sequence with non digit"){
        char sessions[] = "4, 5, n, 123";
        REQUIRE(parseDirectChargeSession(sessions, sessionValues) == true);
        REQUIRE(sessionValues.size() == 3);
    }
    sessionValues.clear();
}

TEST_CASE("Parsing array of 12 Bit current samples"){
    std::list<SessionVal> sessionValues = {};
    SECTION("Smallest set of valid 12 bit sequence"){
        char sessions[] = "1638, 2048";
        REQUIRE(parse12BitChargeSession(sessions, sessionValues) == true);
        REQUIRE(sessionValues.size() == 2);
    }
    SECTION("12 Bit current sampling with non digit"){
        char sessions[] = "1638, 2048, n";
        REQUIRE(parse12BitChargeSession(sessions, sessionValues) == true);
        REQUIRE(sessionValues.size() == 2);
    }
    SECTION("12 Bit current sampling with out of range digits"){
        char sessions[] = "-1, 4095";
        REQUIRE(parse12BitChargeSession(sessions, sessionValues) == false);
        REQUIRE(sessionValues.size() == 0);
    }
    sessionValues.clear();
}

TEST_CASE("Direct Range calculation"){
    std::list<SessionVal> sessionValues = {};
    std::list<chargeRange> chargeRanges = {};
    SECTION("Different set of valid digit sequences + isolated sessions"){
        char sessions[] = "12, 4, 5, 9, 20, 6, 4, 4, 13, 14";
        char toStringArray[200];
        REQUIRE(parseDirectChargeSession(sessions, sessionValues) == true);
        REQUIRE(calculateRanges(sessionValues, chargeRanges) == true);
        REQUIRE(chargeRanges.size() == 2);
        // 1st range evaluation
        std::list<chargeRange>::iterator it = chargeRanges.begin();
        REQUIRE(it->lowValue  == 4);
        REQUIRE(it->highValue == 6);
        REQUIRE(it->readings  == 5);
        REQUIRE(it->getRangeString(toStringArray, sizeof(toStringArray)));
        REQUIRE(strcmp(toStringArray, "4-6, 5\n") == 0);
        it++;
        // 2nd range evaluation
        REQUIRE(it->lowValue  == 12);
        REQUIRE(it->highValue == 14);
        REQUIRE(it->readings  == 3);
        REQUIRE(it->getRangeString(toStringArray, sizeof(toStringArray)));
        REQUIRE(strcmp(toStringArray, "12-14, 3\n") == 0);
        it++;
        REQUIRE(it == chargeRanges.end());
    }
    sessionValues.clear();
    chargeRanges.clear();
}

TEST_CASE("12 Bit Range calculation"){
    std::list<SessionVal> sessionValues = {};
    std::list<chargeRange> chargeRanges = {};
    SECTION("Different set of valid digit sequences + isolated sessions"){
        char sessions[] = "1200, 1100, 1300, 1700, 3800, 3500,"\
                          "2040, 100, 500, 4094";
        char toStringArray[200];
        REQUIRE(parse12BitChargeSession(sessions, sessionValues) == true);
        REQUIRE(calculateRanges(sessionValues, chargeRanges) == true);
        REQUIRE(chargeRanges.size() == 3);
        // 1st range evaluation
        std::list<chargeRange>::iterator it = chargeRanges.begin();
        REQUIRE(it->lowValue  == 0);
        REQUIRE(it->highValue == 1);
        REQUIRE(it->readings  == 2);
        REQUIRE(it->getRangeString(toStringArray, sizeof(toStringArray)));
        REQUIRE(strcmp(toStringArray, "0-1, 2\n") == 0);
        it++;
        // 2nd range evaluation
        REQUIRE(it->lowValue  == 3);
        REQUIRE(it->highValue == 5);
        REQUIRE(it->readings  == 5);
        REQUIRE(it->getRangeString(toStringArray, sizeof(toStringArray)));
        REQUIRE(strcmp(toStringArray, "3-5, 5\n") == 0);
        it++;
        // 3rd range evaluation
        REQUIRE(it->lowValue  == 9);
        REQUIRE(it->highValue == 10);
        REQUIRE(it->readings  == 3);
        REQUIRE(it->getRangeString(toStringArray, sizeof(toStringArray)));
        REQUIRE(strcmp(toStringArray, "9-10, 3\n") == 0);
        it++;
        REQUIRE(it == chargeRanges.end());
    }
    sessionValues.clear();
    chargeRanges.clear();
}