std::vector<int32_t> minBitwiseArray(std::vector<int32_t>& nums)
{
	for (size_t i = 0; i < nums.size(); ++i)
	{
		int32_t tmp = nums[i];
		for (size_t j = 1; j < nums[i]; ++j)
		{
			if ((j | (j + 1)) == nums[i])
			{
				nums[i] = j;
				break;
			}
		}
		if (nums[i] == tmp)
			nums[i] = -1;
	}
	return nums;
}

int32_t main()
{
    std::vector<int32_t> numbers = { 2, 3, 5, 7 };
    std::cout << std::format("result: {}\n", minBitwiseArray(numbers));
}
