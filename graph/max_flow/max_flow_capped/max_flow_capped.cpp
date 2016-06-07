typedef struct {
	int dest, idx; ll weight;
} edge;

int N;
ll flowCap = MAX_LL, flowCounter = 0;
vector<vector<edge>> graph;
vector<ll> visited;

bool dfs(int s, int t) {
	visited[s] = flowCounter;
	
	if(s == t) return true;
	
	for(edge &e: graph[s]) {
		if(visited[e.dest] < flowCounter && e.weight >= flowCap && dfs(e.dest, t)) {
			e.weight -= flowCap;
			graph[e.dest][e.idx].weight += flowCap;
			return true;
		}
	}
	
	return false;
}

//returns the max flow between s and t in graph
//O(|E|^2 * log(C))
ll maxFlow(int s, int t) {
	ll flow = 0;
	flowCap = MAX_LL, flowCounter = 0;
	visited.assign(N, flowCounter);
	while(flowCap) {
		while(flowCounter++, dfs(s, t)) {
			flow += flowCap;
		}
		flowCap >>= 1;
	}
	
	return flow;
}