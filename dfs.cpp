void dfs(int32_t pNode, 
		 std::vector<std::vector<int32_t>>& pAdj, 
		 std::vector<bool>& pVisited)
{
	pVisited[pNode] = true;

	for (int32_t i : pAdj[pNode])
	{
		if (i < pVisited.size() && !pVisited[i])
			dfs(i, pAdj, pVisited);
	}
}

int32_t main()
{
	std::vector<std::vector<int32_t>> adj(5);

	adj[0] = { 3, 2 };
	adj[1] = { 0, 3 };
	adj[2] = { 0 };
	adj[3] = { 6, 5 };
	adj[4] = { 3 };

	std::vector<bool> visited(5, false);
	dfs(0, adj, visited);
}
