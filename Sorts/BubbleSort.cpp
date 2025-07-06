#include <iostream>
#include <vector>
#include <algorithm>

/*---------------------------------------BubbleSort---------------------------------------*/
// comparing elements in apple-pie order. if an element is bigger than the next - swaps them, 
// otherwise comparing with the next element
template<typename Iter>
constexpr void bubbleSort(Iter pBegin, Iter pEnd)
{
	for (auto it1 = pBegin; it1 != pEnd; ++it1)
	{
		for (auto it2 = pBegin; it2 != pEnd-1; ++it2)
		{
			auto next = it2 + 1;
			if (*next < *it2)
				std::iter_swap(next, it2);
		}
	}
}
template<typename Iter>
constexpr void bubbleSortReverse(Iter pBegin, Iter pEnd)
{
	for (auto it1 = pBegin; it1 != pEnd; ++it1)
	{
		for (auto it2 = pBegin; it2 != pEnd - 1; ++it2)
		{
			auto next = it2 + 1;
			if (*next > *it2)
				std::iter_swap(next, it2);
		}
	}
}
/*----------------------------------------------------------------------------------------*/

int main()
{
	std::vector<int> bubbleVector = { 5,423,563,4,24,65,876,923,12,2,1,3,9,0 };
	bubbleSort(bubbleVector.begin(), bubbleVector.end());
	std::cout << std::format("Vector: {}\n", bubbleVector);
}
