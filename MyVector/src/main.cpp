#include "myvector.h"

int main()
{
	MyVector<int> vec = {1, 2, 3, 4, 5};
	MyVector<int> vec2 = { 6, 7, 8, 9, 10 };

	vec.erase(vec.begin() + 2);
	vec.insert(vec.begin() + 2, vec2.begin() + 1, vec2.end() - 1);

	std::cout << vec << std::endl;

	return 0;
}