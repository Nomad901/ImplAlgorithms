#include <iostream>
#include <vector>
#include <algorithm>

/*------------------------------QuickSort--------------------------------*/
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
/*---------------------------------------------------------------------------*/

int main()
{
    std::vector<int> bubbleVector = { 5,423,563,4,24,65,876,923,12,2,1,3,9,0 };
    quickSort(bubbleVector, 0, bubbleVector.size() - 1);
    std::cout << std::format("Vector: {}\n", bubbleVector);

}
