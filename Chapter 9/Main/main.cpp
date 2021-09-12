#include <iostream>
using namespace std;

constexpr char pos_A{ 65 }, pos_Z{ 90 }, pos_a{ 97 }, pos_z{ 122 };
constexpr bool isUpper(char x) { return pos_A <= x && pos_Z >= x; }
constexpr bool isLower(char x) { return pos_a <= x && pos_z >= x; }

class AlphaHistogram {
	size_t counts[26]{};

public:
	void ingest(const char* x) {
		size_t index{};
		while (const auto c = x[index]) {
			if (isUpper(c)) counts[c - pos_A]++;
			else if (isLower(c)) counts[c - pos_a]++;
			index++;
		}	
	}

	void print() const {
		for (auto index{ pos_A }; index <= pos_Z; index++) {
			cout << index << ": ";
			auto asterisks = counts[index - pos_A];
			while (asterisks--) cout << '*';
			cout << "\n";
		}
	}
};

int main(int argc, char** argv) {
	AlphaHistogram hist;
	for (size_t i{ 1 }; i < argc; i++) {
		hist.ingest(argv[i]);
	}
	hist.print();
}