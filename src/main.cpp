#include <iostream>

int main() {
	char a;
	char b;
	b = 127;
	a = -128;
	char c = a + b;
	std::cout << static_cast<int>(c) << std::endl;
	return 0;
}