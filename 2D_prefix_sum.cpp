int32_t maxSideLength(const std::vector<std::vector<int32_t>>& pMatrix, int32_t pThreshold) 
{
    int32_t m = pMatrix.size();
    int32_t n = pMatrix[0].size();
    
    std::vector<std::vector<int32_t>> prefix(m + 1, std::vector<int32_t>(n + 1, 0));
    
    for (int32_t i = 1; i <= m; ++i)  
    {
        for (int32_t j = 1; j <= n; ++j)  
        {
            prefix[i][j] = pMatrix[i - 1][j - 1] +
                prefix[i - 1][j] +
                prefix[i][j - 1] -
                prefix[i - 1][j - 1];
        }
    }

	return 0;
}
