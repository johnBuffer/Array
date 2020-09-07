#include <iostream>
#include "array.hpp"


void printArray(const Array<int32_t>& a)
{
	for (uint64_t i(0); i < a.size(); ++i) {
		std::cout << a[i] << std::endl;
	}
}


int main()
{
	Array<int32_t> a;

	uint64_t id_1 = a.push_back(0);
	uint64_t id_2 = a.push_back(1);
	uint64_t id_3 = a.push_back(2);
	uint64_t id_4 = a.push_back(9);

	a.erase(0);

	printArray(a);
}