#define CATCH_CONFIG_MAIN
#include <iostream>
#include <memory>
#include "../../../lib/catch.hpp"
using namespace std;

struct obj {
	const char* message;
	static int x;

	obj(const char* m = "") : message{ m } { x++; }
	~obj() { x--; }
};

int obj::x{};

TEST_CASE("WeakPtr lock() yields") {
	auto message = "Open the pod bay doors, HAL.";
    SECTION("a shared pointer when tracked object is alive") {
		auto a = make_shared<obj>(message);
		// weak ptr tracking the obj owned by the shared ptr a
		weak_ptr<obj> b{ a };
		// creates a shared ptr owning the obj that the weak ptr was tracking
		auto shared_pointer = b.lock();
		// Proves it's the same dynamic obj from before
		REQUIRE(shared_pointer->message == message);
		// Shows that there are 2 shared ptrs active.
		REQUIRE(shared_pointer.use_count() == 2);
    }

	SECTION("empty when shared pointer empty") {
		weak_ptr<obj> a;
		{
			auto b = make_shared<obj>(message);
			// assigns the dynamic obj b owned to get tracked by a.
			a = b;
		} // b dies and is empty
		// a nullptr is returned since the last pointed to ptr is no longer active
		auto shared_pointer = a.lock();
		REQUIRE(nullptr == shared_pointer);
	}
}