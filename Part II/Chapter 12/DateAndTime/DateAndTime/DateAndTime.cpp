#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;

TEST_CASE("datetime construction") {
    SECTION("constructor") {
        date d{ 2021, 9, 29 };
        REQUIRE(d.day() == 29);
        REQUIRE(d.month() == 9);
        REQUIRE(d.year() == 2021);
        REQUIRE(d.day_of_week() == boost::date_time::Wednesday);
        REQUIRE(d.day_of_year() == 272);
    }

    SECTION("construct from string") {
        auto d = from_string("2021/9/29");
        REQUIRE(d.day() == 29);
        REQUIRE(d.month() == 9);
        REQUIRE(d.year() == 2021);
        REQUIRE(d.day_of_week() == boost::date_time::Wednesday);
        REQUIRE(d.day_of_year() == 272);
    }
}

TEST_CASE("invalid date throws exceptions") {
    REQUIRE_THROWS_AS(date(2021, 9, 31), bad_day_of_month);
}

TEST_CASE("current day") {
    date d{ 2021, 9, 29 };

    REQUIRE(day_clock::local_day() == d);
    REQUIRE(day_clock::universal_day() == d);
}

TEST_CASE("supports calendar arithmetic") {
    date d1{ 2003, 12, 2 };
    date d2{ 2021, 9, 29 };
    auto duration = d2 - d1;
    REQUIRE(duration.days() == 6'511);

    date_duration d{ 6'511 };
    d2 = d1 + d;
    REQUIRE(d2 == from_string("2021/9/29"));
}

TEST_CASE("date supports periods of time") {
    date d1{ 2003, 12, 2 };
    date d2{ 2021, 9, 29 };
    date_period p{ d1, d2 };
    REQUIRE(p.contains(date{ 2009, 11, 13 }));
}