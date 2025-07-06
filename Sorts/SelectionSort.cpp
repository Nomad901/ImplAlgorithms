#include <iostream>
#include <vector>
#include <algorithm>

/*------------------------------SelectionSort--------------------------------*/
// taking 1 element at a time and comparing this element with other ones
// if the element is lees than the previous - swaps, otherwise is going furher
template<typename Iter>
constexpr void selectionSort(Iter pBegin, Iter pEnd)
{
	for (; pBegin != pEnd; ++pBegin)
	{
		for (auto it = pBegin + 1; it != pEnd; ++it)
		{
			if (*it < *pBegin)
				std::iter_swap(it, pBegin);
		}
	}
}
template<typename Iter>
constexpr void selectionSortReverse(Iter pBegin, Iter pEnd)
{
	for (; pBegin != pEnd; ++pBegin)
	{
		for (auto it = pBegin + 1; it != pEnd; ++it)
		{
			if (*it > *pBegin)
				std::iter_swap(it, pBegin);
		}
	}
}
/*---------------------------------------------------------------------------*/
int main()
{
	std::vector<int> bubbleVector = { 5,423,563,4,24,65,876,923,12,2,1,3,9,0 };
	selectionSort(bubbleVector.begin(), bubbleVector.end());
	std::cout << std::format("Vector: {}\n", bubbleVector);
}
