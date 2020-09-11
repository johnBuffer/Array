#include <iostream>
#include "index_vector.hpp"


void printArray(const IndexVector<int32_t>& a)
{
	for (uint64_t i(0); i < a.size(); ++i) {
		std::cout << a[i] << std::endl;
	}
}


int main()
{
	IndexVector<int32_t> a;

	uint64_t id_1 = a.emplace_back(0);
	uint64_t id_2 = a.push_back(1);
	uint64_t id_3 = a.push_back(2);
	uint64_t id_4 = a.push_back(9);

	Ptr<int32_t> ptr_1 = a.getPtr(id_2);
	
	std::cout << "PTR value " << *ptr_1 << std::endl;

	a.erase(id_2);

	for (int32_t b : a) {
		std::cout << b << std::endl;
	}
}
