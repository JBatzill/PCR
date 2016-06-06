//O(|E|*log|V|)
ll dijkstra(vector<vector<pii>> &graph, int start, int end) {
	vector<ll> dist = vector<ll>(graph.size(), MAX_LL);
	dist[0] = 0;
	priority_queue<pll, vector<pll>, greater<pll>> pq;
	pq.push((pll){0, start});
	
	while(!pq.empty()) {
		pll node = pq.top(); pq.pop();
		
		if(node.first > dist[node.second]) continue;
		if(node.second == end) break; //remove for dist to all
		
		for(pii &edge: graph[node.second]) {
			if(dist[node.second] + edge.second < dist[edge.first]) {
				dist[edge.first] = dist[node.second] + edge.second;
				// parent[edge.first] = node.second;
				pq.push((pll){dist[edge.first], edge.first});
			}
		}
	}
	
	return dist[end];
}