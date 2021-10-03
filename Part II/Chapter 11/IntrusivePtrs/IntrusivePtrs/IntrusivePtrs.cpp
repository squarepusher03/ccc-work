#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "intrusive_ptr.hpp"

struct obj {
	const char* message;
	static int x;

	obj(const char* m = "") : message{ m } { x++; }
	~obj() { x--; }
};

using IntrusivePtr = boost::intrusive_ptr<obj>;
size_t ref_count{};

void intrusive_ptr_add_ref(obj* d) {
	ref_count++;
}

void intrusive_ptr_release(obj* d) {
	ref_count--;
	if (ref_count == 0) delete d;
}

TEST_CASE("IntrusivePtr uses an embedded reference to counter.") {
	REQUIRE(ref_count == 0);
	IntrusivePtr a{ new obj{} };
	REQUIRE(ref_count == 1);
	{
		IntrusivePtr b{ a };
		REQUIRE(ref_count == 2);
	}
	REQUIRE(obj::x == 1);
}
