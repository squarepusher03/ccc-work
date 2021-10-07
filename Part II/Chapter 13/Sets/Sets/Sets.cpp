#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <unordered_set>
#include <functional>
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

TEST_CASE("set allows removal") {
    set<int> fib{ 1, 1, 2, 3, 5 };
    
    SECTION("with erase") {
        fib.erase(3);
        REQUIRE(fib.find(3) == fib.end());
    }

    SECTION("with clear") {
        fib.clear();
        REQUIRE(fib.empty());
    }
}

TEST_CASE("multiset handles non-unique elements") {
    multiset<int> fib{ 1, 1, 2, 3, 5 };

    SECTION("as reflected by size") {
        REQUIRE(fib.size() == 5);
    }

    SECTION("and count returns values greater than 1") {
        REQUIRE(fib.count(1) == 2);
    }

    SECTION("and equal range returns non-trivial ranges") {
        auto [begin, end] = fib.equal_range(1);
        REQUIRE(*begin == 1);
        ++begin;
        REQUIRE(*begin == 1);
        ++begin;
        REQUIRE(begin == end);
    }
}

TEST_CASE("hash<long> returns") {
    hash<long> hasher;
    auto hash_code_42 = hasher(42);

    SECTION("equal hash codes for equal keys") {
        REQUIRE(hash_code_42 == hasher(42));
    }

    SECTION("unequal hash codes for unequal keys") {
        REQUIRE_FALSE(hash_code_42 == hasher(43));
    }
}

TEST_CASE("equal_to<long> returns") {
    equal_to<long> long_equal_to;

    SECTION("true when arguments equal") {
        REQUIRE(long_equal_to(42, 42));
    }

    SECTION("false when arguments unequal") {
        REQUIRE_FALSE(long_equal_to(42, 43));
    }
}

TEST_CASE("unordered_set") {
    unordered_set<unsigned long> sheep(100);

    SECTION("allows bucket count specification on construction") {
        REQUIRE(sheep.bucket_count() >= 100);
        REQUIRE(sheep.bucket_count() < sheep.max_bucket_count());
        REQUIRE(sheep.max_load_factor() == Approx(1.0));
    }

    SECTION("allows us to reserve space for elements") {
        sheep.reserve(100'000);
        sheep.insert(0);
        REQUIRE(sheep.load_factor() <= 0.00001);

        while (sheep.size() < 100'000) {
            sheep.insert(sheep.size());
        }
        REQUIRE(sheep.load_factor() <= 1.0);
    }
}