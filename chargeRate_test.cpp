#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "chargeRate.h"

TEST_CASE("Characters to int test conversion"){
    sessionValues.clear();
    SECTION("Addition of digit character input"){
        char digit[] = "12";
        REQUIRE(addParsedSession(digit) == true);
    }
    SECTION("Attempt of non digit character input"){
        char nonDigit[] = "HI";
        REQUIRE(addParsedSession(nonDigit) == false);
    }
    SECTION("Attempt of non digit special characters"){
        char nonDigitSpecialChars[] = "/0";
        REQUIRE(addParsedSession(nonDigitSpecialChars) == false);
    }
}

TEST_CASE("Parsing array of charging sessions"){
    sessionValues.clear();
    SECTION("Smallest set of valid digit sequences"){
        char sessions[] = "4, 5";
        std::list<long> parsedSessions = parseChargeSessions(sessions);
        REQUIRE(parsedSessions.size() == 2);
    }
    SECTION("Digit sequence with non digit"){
        char sessions[] = "4, 5, n, 123";
        std::list<long> parsedSessions = parseChargeSessions(sessions);
        REQUIRE(parsedSessions.size() == 3);
    }
}

TEST_CASE("Range calculation"){
    sessionValues.clear();
    chargeRanges.clear();
    SECTION("Smallest set of valid digit sequences + isolated sessions"){
        char sessions[] = "12, 4, 5, 9, 20";
        std::list<long> parsedSessions = parseChargeSessions(sessions);
        std::list<chargeRange> ranges = calculateRanges();
        REQUIRE(ranges.size() == 1);
    }
}