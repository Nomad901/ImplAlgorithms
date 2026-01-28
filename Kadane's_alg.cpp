class Solution {
public:
int32_t maxSubArray(const std::vector<int32_t>& pNumbers)
{
	int32_t currentSum = pNumbers[0];
	int32_t maxSum = pNumbers[0];

	for (size_t i = 1; i < pNumbers.size(); ++i)
	{
		currentSum = std::max(pNumbers[i], currentSum + pNumbers[i]);
		maxSum = std::max(maxSum, currentSum);
	}
	return maxSum;
}

};


// 121. Best Time to Buy and Sell Stock
class Solution {
public:
int32_t maxProfit(std::vector<int32_t>& pPrices)
{
	if (pPrices.size() < 2)
		return 0;

	int32_t currentProfit = 0, maxProfit = 0;

	for (size_t i = 1; i < pPrices.size(); ++i)
	{
		int32_t dailyProfit = pPrices[i] - pPrices[i - 1];

		currentProfit = std::max(dailyProfit, dailyProfit + currentProfit);
		maxProfit = std::max(currentProfit, maxProfit);
	}

	return maxProfit;
}
};

//152. Maximum Product Subarray
class Solution {
public:
int32_t maxProduct(const std::vector<int32_t>& pNumbers)
{
	if (pNumbers.empty())
		return 0;

	int32_t minProduct = pNumbers[0];
	int32_t maxProduct = pNumbers[0];
	int32_t result = pNumbers[0];

	for (size_t i = 1; i < pNumbers.size(); ++i)
	{
		if (pNumbers[i] < 0)
			std::swap(minProduct, maxProduct);

		minProduct = std::min(pNumbers[i], minProduct * pNumbers[i]);
		maxProduct = std::max(pNumbers[i], maxProduct * pNumbers[i]);

		result = std::max(result, maxProduct);
	}

	return result;
}
};
