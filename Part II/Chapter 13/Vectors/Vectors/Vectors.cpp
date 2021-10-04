#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <array>
#include <vector>
using namespace std;

TEST_CASE("vector supports default construction") {
    vector<const char*> vec;
    REQUIRE(vec.empty());
}

TEST_CASE("vector supports braced initialization") {
    vector<int> fib{ 1, 1, 2, 3, 5 };
    REQUIRE(fib[4] == 5);
}

TEST_CASE("vector supports") {
    SECTION("braced initialization") {
        vector<int> five_nine{ 5, 9 };
        REQUIRE(five_nine[0] == 5);
        REQUIRE(five_nine[1] == 9);
    }

    SECTION("fill constructor") {
        vector<int> five_nines(5, 9);
        REQUIRE(five_nines[0] == 9);
        REQUIRE(five_nines[4] == 9);
    }
}

TEST_CASE("vector supports construction from iterators") {
    array<int, 5> fib_arr{ 1, 1, 2, 3, 5 };
    vector<int> fib_vec(fib_arr.begin(), fib_arr.end());
    REQUIRE(fib_vec[4] == 5);
    REQUIRE(fib_vec.size() == fib_arr.size());
}

TEST_CASE("vector assign replaces existing elements") {
    vector<int> message{ 13, 80, 110, 114, 102, 110, 101 };
    REQUIRE(message.size() == 7);
    message.assign({ 67, 97, 101, 115, 97, 114 });
    REQUIRE(message[5] == 114);
    REQUIRE(message.size() == 6);
}

TEST_CASE("vector insert places new elements") {
    vector<int> zeros(3, 0);
    auto third_element = zeros.begin() + 2;
    zeros.insert(third_element, 10);
    REQUIRE(zeros[2] == 10);
    REQUIRE(zeros.size() == 4);
}