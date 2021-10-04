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

    SECTION("operator[] can at and set elements") {
        fib[2] = 2;
        REQUIRE(fib[2] == 2);
        // fib[4] = 5;
        // ^ uncommenting this will cause undefined behavior
        // use .at() if you think you might go out of bounds since it'll throw an exception instead.
    }

    SECTION("at() can get and set elements") {
        fib.at(2) = 2;
        REQUIRE(fib.at(2) == 2);
        REQUIRE_THROWS_AS(fib.at(4), out_of_range);
    }

    SECTION("get can get and set elements") {
        get<2>(fib) = 2;
        REQUIRE(get<2>(fib) == 2);
        // get<4>(fib);
    }
}

TEST_CASE("array has convenience methods") {
    array<int, 4> fib{ 0, 1, 2, 0 };

    SECTION("front") {
        fib.front() = 1;
        REQUIRE(fib.front() == 1);
        REQUIRE(fib.front() == fib[0]);
    }

    SECTION("back") {
        fib.back() = 3;
        REQUIRE(fib.back() == 3);
        REQUIRE(fib.back() == fib[3]);
    }
}

TEST_CASE("we can obtain a pointer to the first element using") {
    array<char, 9> color{ 'o', 'c', 't', 'a', 'r', 'i', 'n', 'e' };
    const auto* color_ptr = color.data();

    SECTION("data") {
        REQUIRE(*color_ptr == 'o');
    }

    SECTION("address-of-front") {
        REQUIRE(&color.front() == color_ptr);
    }

    SECTION("address-of at(0)") {
        REQUIRE(&color.at(0) == color_ptr);
    }

    SECTION("address-of get<0>(array)") {
        REQUIRE(&get<0>(color) == color_ptr);
    }
}

TEST_CASE("array begin/end form a half-open range") {
    array<int, 0> e{};
    REQUIRE(e.begin() == e.end());
}

TEST_CASE("array iterators are pointer-like") {
    array<int, 3> easy_as{ 1, 2, 3 };
    auto iter = easy_as.begin();
    REQUIRE(*iter == 1);
    ++iter;
    REQUIRE(*iter == 2);
    ++iter;
    REQUIRE(*iter == 3);
    ++iter;
    REQUIRE(iter == easy_as.end());
}

TEST_CASE("array can be used as a range expression") {
    array<int, 5> fib{ 1, 1, 2, 3, 5 };
    int sum{};
    for (const auto element : fib) {
        sum += element;
    }
    REQUIRE(sum == 12);
}