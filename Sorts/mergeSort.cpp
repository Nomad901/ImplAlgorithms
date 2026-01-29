void merge(std::vector<int32_t>& pStorage, int32_t pLeft, int32_t pRight, int32_t pMid)
{
	int32_t begin1Half = pMid - pLeft + 1;
	int32_t begin2Half = pRight - pMid;
	
	std::vector<int32_t> leftSubString(begin1Half), rightSubString(begin2Half);

	int32_t i = 0;
	for (; i < begin1Half; ++i)
	{
		leftSubString[i] = pStorage[pLeft + i];
	}
	int32_t j = 0;
	for (; j < begin2Half; ++j)
	{
		rightSubString[j] = pStorage[pMid + 1 + j];
	}
	i = 0, j = 0;
	int32_t k = pLeft;
	
	while (i < begin1Half && j < begin2Half)
	{
		if (leftSubString[i] <= rightSubString[j])
			pStorage[k++] = leftSubString[i++];
		else
			pStorage[k++] = rightSubString[j++];
	}
	
	while (i < begin1Half)
	{
		pStorage[k++] = leftSubString[i++];
	}
	while (j < begin2Half)
	{
		pStorage[k++] = rightSubString[j++];
	}
}

void mergeSort(std::vector<int32_t>& pStorage, int32_t pLeft, int32_t pRight)
{
	if (pLeft >= pRight)
		return;

	int32_t mid = pLeft + (pRight - pLeft) / 2;

	mergeSort(pStorage, pLeft, mid);
	mergeSort(pStorage, mid + 1, pRight);
	merge(pStorage, pLeft, pRight, mid);
}

int32_t main()
{
	std::vector<int32_t> storage = { 6, 4, 3, 2, 1, 9 };

	mergeSort(storage, 0, storage.size() - 1);

	std::cout << std::format("result of sort: {}\n", storage);
}
