#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <array>
using namespace std;

array<int, 10> static_array{};

TEST_CASE("std::array") {
    REQUIRE(static_array[0] == 0);

    SECTION("uninitialized without braced initializers") {
        array<int, 10> local_array;
        REQUIRE(local_array[0] != 0);
    }

    SECTION("intialized with braced initializers") {
        array<int, 10> local_array{ 0, 1, 2, 3 };
        REQUIRE(local_array[0] == 0);
        REQUIRE(local_array[1] == 1);
        REQUIRE(local_array[2] == 2);
        REQUIRE(local_array[3] == 3);
    }
}

TEST_CASE("std::array access") {
    array<int, 4> fib{ 1, 1, 0, 3 };

    SECTION("operator[] can et and set elements") {
        fib[2] = 2;
        REQUIRE(fib[2] == 2);
        // fib[4] = 5;
        // ^ uncommenting this will cause undefined behavior
        // use .at() if you think you might go out of bounds since it'll throw an exception instead.
    }
}