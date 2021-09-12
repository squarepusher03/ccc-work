#include <iostream>
using namespace std;

class LambdaFactory {
	const char key;
	size_t tally;

public:
	LambdaFactory(char input) : key{input}, tally{} { }
	
	auto make_lambda() {
		return [this](const char* str) {
			size_t index{}, result{};
			while (str[index]) {
				if (str[index] == key) result++;
				index++;
			}
			tally += result;
			return result;
		};
	}

	size_t const get_tally() {
		return tally;
	}
};

int main() {
	char key{'a'};
	size_t tally{};
	
	auto a_search = [&, key](const char* str) mutable {
		size_t index{}, result{};
		
		while (str[index]) {
			if (str[index] == key) result++;
			index++;
		}

		tally += result;
		return result;
	};

	cout << "tally: " << tally << endl;
	auto str1 = a_search("aaa aa aaa"); // 8
	cout << "str1: " << str1 << endl;

	cout << "tally: " << tally << endl;
	auto str2 = a_search("ababbba aaba"); // 6
	cout << "str2: " << str2 << endl;

	cout << "tally: " << tally << endl;

	LambdaFactory factory{'a'};
	auto lambda = factory.make_lambda();

	cout << "tally: " << factory.get_tally() << endl;
	cout << "str1: " << lambda("aaa aa aaa") << endl;

	cout << "tally: " << factory.get_tally() << endl;
	cout << "str2: " << lambda("ababbba aaba") << endl;

	cout << "tally: " << factory.get_tally() << endl;
}