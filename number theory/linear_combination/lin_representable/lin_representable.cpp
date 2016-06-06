//checks whether there exists an int vector a >= 0 s.t. a'*g=k or not
//O((|g|*min(g)) * log(min(g)))
bool linRepresentable(vector<int> g, ll k) {

	//get minimal element for smallest graph
	int m = g[0];
	for(int gi: g) m = min(m, gi);
	
	//get all moves O(|g|+min(g))
	vector<pii> moves = vector<pii>();
	vector<int> tmp(m, MAX_INT);
	for(int gi: g) tmp[gi % m] = min(tmp[gi % m], gi);
	for(int i = 1; i < m; i++) {
		if(tmp[i] < MAX_INT) moves.pb((pii){i, tmp[i]});
	}
	
	//create graph
	vector<vector<pii>> graph = vector<vector<pii>>(m, vector<pii>());
	for(int i = 0; i < m; i++) {
		for(pii &move: moves) {
			graph[i].pb(((pii){(i+move.first) % m, move.second}));
		}
	}
	
	return dijkstra(graph, 0, (int)(k % m)) <= k;
}