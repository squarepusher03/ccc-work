#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <chrono>
#include <thread>
using namespace std;
using namespace literals::chrono_literals;

TEST_CASE("chrono supports several clocks") {
    auto sys_now = chrono::system_clock::now();
    auto hires_now = chrono::high_resolution_clock::now();
    auto steady_now = chrono::steady_clock::now();

    REQUIRE(sys_now.time_since_epoch().count() > 0);
    REQUIRE(hires_now.time_since_epoch().count() > 0);
    REQUIRE(steady_now.time_since_epoch().count() > 0);
}

TEST_CASE("chrono supports several units of measurement") {
    auto one_s = chrono::seconds(1);
    auto thousand_ms = 1000ms;
    REQUIRE(one_s == thousand_ms);
}

TEST_CASE("chrono supports duration_cast") {
    auto billion_ns_to_s = chrono::duration_cast<chrono::seconds>(1'000'000'000ns);
    REQUIRE(billion_ns_to_s.count() == 1);
}

TEST_CASE("chrono used to sleep") {
    auto start = chrono::system_clock::now();
    this_thread::sleep_for(100ms);
    auto end = chrono::system_clock::now();
    REQUIRE(end - start >= 100ms);
}