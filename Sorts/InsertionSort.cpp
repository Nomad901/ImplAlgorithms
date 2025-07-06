#include <iostream>
#include <vector>
#include <algorithm>

/*------------------------------InsertionSort--------------------------------*/
// taking 1 element and comparing this with the beginning of the storage
template<typename Iter>
constexpr void insertionSort(Iter pBegin, Iter pEnd)
{
	for (auto it = pBegin; it != pEnd; ++it)
	{
		auto key = *it;
		auto insertion = it;
		while (insertion != pBegin && *(insertion - 1) > key)
		{
			*insertion = *(insertion - 1);
			insertion--;
		}
		*insertion = key;
	}
}
/*---------------------------------------------------------------------------*/

int main()
{
	std::vector<int> bubbleVector = { 5,423,563,4,24,65,876,923,12,2,1,3,9,0 };
	insertionSort(bubbleVector.begin(), bubbleVector.end());
	std::cout << std::format("Vector: {}\n", bubbleVector);
}
