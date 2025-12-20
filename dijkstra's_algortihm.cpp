std::vector<int32_t> dijkstra(int32_t pTotalNodes,
							  const std::vector<std::vector<std::pair<int32_t, int32_t>>>& pGraph,
							  int32_t pStartNode)
{
	assert(pTotalNodes > pStartNode);

	std::vector<int32_t> distances(pTotalNodes, std::numeric_limits<int32_t>::max());
	distances[pStartNode] = 0;

	std::priority_queue<std::pair<int32_t, int32_t>,
						std::vector<std::pair<int32_t, int32_t>>,
						std::greater<std::pair<int32_t, int32_t>>> nodesToCheck;
	
	nodesToCheck.push(std::make_pair(0, pStartNode));

	while (!nodesToCheck.empty())
	{
		int32_t currentDistance = nodesToCheck.top().first;
		int32_t currentNode = nodesToCheck.top().second;
		nodesToCheck.pop();

		if (currentDistance > distances[currentNode])
			continue;
		
		for (const auto& neighborInfo : pGraph[currentNode])
		{
			int32_t neighborNode = neighborInfo.first;
			int32_t edgeWeightToNeighborNode = neighborInfo.second;
			
			int32_t newDistanceToNeighbor = currentDistance + edgeWeightToNeighborNode;

			if (newDistanceToNeighbor < distances[neighborNode])
			{
				distances[neighborNode] = newDistanceToNeighbor;
				nodesToCheck.push(std::make_pair(newDistanceToNeighbor, neighborNode));
			}
		}
	}

	return distances;
}
