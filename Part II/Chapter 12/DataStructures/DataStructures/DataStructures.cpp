#define CATCH_CONFIG_MAIN
#include "boost/logic/tribool.hpp"
#include "catch.hpp"
#include <optional>
#include <variant>
#include <utility>
#include <tuple>
#include <any>

// ----------------- Tribool -----------------

using boost::logic::indeterminate;
boost::logic::tribool t = true, f = false, i = indeterminate;

TEST_CASE("Boost tribool converts to bool") {
    REQUIRE(t);
    REQUIRE_FALSE(f);
    REQUIRE(!f);
    REQUIRE_FALSE(!t);
    REQUIRE(indeterminate(i));
    REQUIRE_FALSE(indeterminate(t));
}

TEST_CASE("Boost tribool supports boolean operations") {
    auto t_or_f = t || f;
    REQUIRE(t_or_f);
    REQUIRE(indeterminate(t && indeterminate));
    REQUIRE(indeterminate(f || indeterminate));
    REQUIRE(indeterminate(!i));
}

TEST_CASE("Boost tribool works nicely with if statements") {
    if (i) FAIL("Indeterminate is true");
    else if (!i) FAIL("Indeterminate is false");
    else {}
}

// ----------------- Optional -----------------

struct TheMatrix {
    const int iteration;
    TheMatrix(int x) : iteration{ x } {}
};

enum class Pill { Red, Blue };

std::optional<TheMatrix> take(Pill pill) {
    if (pill == Pill::Blue) return TheMatrix{ 6 };
    return std::nullopt;
}

TEST_CASE("std::optional contains types") {
    if (auto matrix_opt = take(Pill::Blue)) {
        REQUIRE(matrix_opt->iteration == 6);
        auto& matrix = matrix_opt.value();
        REQUIRE(matrix.iteration == 6);
    }
    else {
        FAIL("The optional evaluated to false.");
    }
}

TEST_CASE("std::optional can be empty") {
    auto matrix_opt = take(Pill::Red);
    if (matrix_opt) FAIL("The Matrix is not empty.");
    REQUIRE_FALSE(matrix_opt.has_value());
}

// ----------------- Pair -----------------

struct A { const char* m; };
struct B { const char* m; };
A a{ "Hello" };
B b{ "Goodbye" };

TEST_CASE("std::pair permits access to members") {
    std::pair<A, B> ab{ a, b };
    REQUIRE(ab.first.m == a.m);
    REQUIRE(ab.second.m == b.m);
}

// ----------------- Tuple -----------------

struct C { const char* m; };
C c{ "Thank you" };

TEST_CASE("std::tuple permits access to members with std::get") {
    using Trio = std::tuple<A, B, C>;
    Trio abc{ a, b, c };
    auto& a_ref = std::get<0>(abc);
    REQUIRE(a_ref.m == a.m);

    auto& c_ref = std::get<C>(abc);
    REQUIRE(c_ref.m == c.m);
}

// ----------------- Any -----------------

struct D {
    int x;
    D(int x) : x{ x } {}
};

TEST_CASE("std::any allows us to std::any_cast into a type") {
    std::any d;
    d.emplace<D>(600);
    auto e = std::any_cast<D>(d);
    REQUIRE(e.x == 600);
    REQUIRE_THROWS_AS(std::any_cast<float>(d), std::bad_any_cast);
}

// ----------------- Variant -----------------

struct E {
    int x;
    bool b;

    E() : b{ true }, x{ 20'000 } {}
};

TEST_CASE("std::variant 1") {
    std::variant<E, D> d;
    REQUIRE(d.index() == 0);

    d.emplace<D>(600);
    REQUIRE(d.index() == 1);

    REQUIRE(std::get<D>(d).x == 600);
    REQUIRE(std::get<1>(d).x == 600);
    REQUIRE_THROWS_AS(std::get<0>(d), std::bad_variant_access);
}

TEST_CASE("std::variant 2") {
    std::variant<E, D> d;
    d.emplace<D>(600);
    auto x = std::visit([](auto& y) { return 2.2 * y.x; }, d);
    REQUIRE(x == 1320);
}