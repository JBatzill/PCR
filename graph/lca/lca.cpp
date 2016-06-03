int LCA_MAX; //#nodes
vector<int>vis, first, mapping;
int lca_time, map_idx;
vector<vector<int>> graph;

void dfs(int u) {
	int mi = map_idx++;
	
	mapping[mi] = u;
	first[u] = lca_time;
	vis[lca_time++] = mi;
	
	for(int v: graph[u]) {
		dfs(v);
		vis[lca_time++] = mi;
	}
}

void init(int root) {
	first = vector<int>(LCA_MAX, -1);
	mapping = vector<int>(LCA_MAX, -1);
	vis = vector<int>(2 * LCA_MAX, -1);
	lca_time = 0, map_idx = 0;
	
	dfs(root);
	initSeg(vis);
}

int lca(int u, int v) {
	int i1 = min(first[u], first[v]);
	int i2 = max(first[u], first[v]);
	return mapping[getMin(i1, i2 + 1)];
}