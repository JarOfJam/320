#include <iostream>
#include <iomanip>
#include <string.h>
#include <string>
#include <sstream>
#include <math.h>

size_t hash(size_t x) {
	int w = 31;
	int p = 29;
	int a = 7;
	return (((a*x) & ((1 << w) - 1)) >> (w - p));
}

std::string hexi(size_t n) {
	std::stringstream a;
	a << std::hex << n;
	return a.str();
}

size_t shash(std::string a) {
	int sum = 0;
	int i = 0;
	while(a[i] != '\0') {
		sum = sum * 10 + a[i] - '0';
		i++;
	}
	return hash(sum);
}

size_t shashNotAsGood(std::string a) {
	int sum = 0;
	int i = 0;
	while(a[i] != '\0') {
		sum = sum + a[i] - '0';
		i++;
	}
	return hash(sum);
}

template <typename T>
size_t mhash(T a) {
	char* str;
	memcpy(str, a, sizeof(a));
	int sum = 0;
	int i = 0;
	while(a[i] != '\0') {
		sum = sum * 10 + a[i] - '0';
		i++;
	}
	return hash(sum);
}

int main() {
	std::cout << "String: 8 Hash: " << hash(8) << " Hex Hash: " << hexi(hash(8)) << std::endl;
	std::cout << "String: password Hash: " << shash("password") << " Hex Hash: " << hexi(shash("password")) << std::endl;
	std::cout << "String: password Hash: " << shashNotAsGood("password") << " Hex Hash: " << hexi(shashNotAsGood("password")) << std::endl;
	std::cout << "String: wordpass Hash: " << shash("wordpass") << " Hex Hash: " << hexi(shash("wordpass")) << std::endl;
	std::cout << "String: wordpass Hash: " << shashNotAsGood("wordpass") << " Hex Hash: " << hexi(shashNotAsGood("wordpass")) << std::endl;
	std::cout << "String: password Hash: " << mhash("password") << " Hex Hash: " << hexi(mhash("password")) << std::endl;
	return 0;
}
