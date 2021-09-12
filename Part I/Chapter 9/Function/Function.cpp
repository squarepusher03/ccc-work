#include <iostream>
#include <functional>
using namespace std;

class CountIf {
	const char x;

public:
	CountIf (char x) : x{ x } { }
	size_t operator()(const char* str) const {
		size_t index{}, result{};
		while (str[index]) {
			if (str[index] == x) result++;
			index++;
		}

		return result;
	}
};

size_t count_spaces(const char* str) {
	size_t index{}, result{};
	
	while (str[index]) {
		if (str[index] == ' ') result++;
		index++;
	}
	
	return result;
}

std::function<size_t(const char*)> funcs[]{
	count_spaces,
	CountIf{ 'e' },
	[](const char* str) {
		size_t index{};
		while (str[index]) index++;
		return index;
	}
};

void const static_func() {
	cout << "A static function.\n";
}

auto text = "Sailor went to sea to see what he could see.";

int main() {
	function<void()> func1 { []{ cout << "A lambda.\n"; } };
	func1();
	func1 = static_func;
	func1();

	size_t index{};
	for (const auto& func : funcs) {
		cout << "Index " << ++index << ": " << func(text) << "\n";
	}
}