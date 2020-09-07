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

	Ptr<int32_t> ptr_1 = a.getPtr(id_2);
	
	std::cout << "PTR value " << *ptr_1 << std::endl;

	a.erase(id_2);

	a.push_back(11);

	if (ptr_1) {
		std::cout << "PTR value " << *ptr_1 << std::endl;
	}
	else {
		std::cout << "PTR invalid" << std::endl;
	}

	printArray(a);
}
