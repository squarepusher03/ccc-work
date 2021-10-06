#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <array>
#include <set>
using namespace std;

TEST_CASE("set supports") {
    set<int> emp;
    set<int> fib{ 1, 1, 2, 3, 5 };

    SECTION("default construction") {
        REQUIRE(emp.empty());
    }

    SECTION("braced initialization") {
        REQUIRE(fib.size() == 4);
    }

    SECTION("copy construction") {
        auto fib_copy(fib);
        REQUIRE(fib.size() == 4);
        REQUIRE(fib_copy.size() == 4);
    }

    SECTION("move construction") {
        auto fib_moved(move(fib));
        REQUIRE(fib.empty());
        REQUIRE(fib_moved.size() == 4);
    }

    SECTION("range construction") {
        array<int, 5> fib_array{ 1, 1, 2, 3, 5 };
        set<int> fib_set(fib_array.cbegin(), fib_array.cend());
        REQUIRE(fib_set.size() == 4);
    }
}

TEST_CASE("set allows access") {
    set<int> fib{ 1, 1, 2, 3, 5 };

    SECTION("with find") {
        REQUIRE(*fib.find(3) == 3);
        REQUIRE(fib.find(100) == fib.end());
    }

    SECTION("with count") {
        REQUIRE(fib.count(3) == 1);
        REQUIRE(fib.count(100) == 0);
    }

    SECTION("with lower_bound") {
        auto itr = fib.lower_bound(3);
        REQUIRE(*itr == 3);
    }

    SECTION("with upper_bound") {
        auto itr = fib.upper_bound(3);
        REQUIRE(*itr == 5);
    }

    SECTION("with equal_range") {
        auto pair_itr = fib.equal_range(3);
        REQUIRE(*pair_itr.first == 3);
        REQUIRE(*pair_itr.second == 5);
    }
}

TEST_CASE("set allows insertion") {
    set<int> fib{ 1, 1, 2, 3, 5 };
    
    SECTION("with insert") {
        fib.insert(8);
        REQUIRE(fib.find(8) != fib.end());
    }

    SECTION("with emplace") {
        fib.emplace(8);
        REQUIRE(fib.find(8) != fib.end());
    }

    SECTION("with emplace_hint") {
        fib.emplace_hint(fib.end(), 8);
        REQUIRE(fib.find(8) != fib.end());
    }
}