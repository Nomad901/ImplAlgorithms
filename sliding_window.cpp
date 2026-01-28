int32_t getMaxSumSubArray(const std::vector<int32_t>& pNumbers, int32_t pSizeSubArray)
{ 
	int32_t sizeNumbers = pNumbers.size();
	if (sizeNumbers < pSizeSubArray)
		return -1;
	if (pNumbers.size() == 1)
		return pNumbers[0];

	int32_t firstWindowSum = 0;
	for (size_t i = 0; i < pSizeSubArray; ++i)
	{
		firstWindowSum += pNumbers[i];
	}

	int32_t maxSum = firstWindowSum;

	for (size_t i = pSizeSubArray; i < pNumbers.size(); ++i)
	{
		firstWindowSum = firstWindowSum + pNumbers[i] - pNumbers[i - pSizeSubArray];
		maxSum = std::max(maxSum, firstWindowSum);
	}

	return maxSum;
}
