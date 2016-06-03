//http://www.spoj.com/problems/LCA/
#include <bits/stdc++.h>

#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef ll (*MY_FUNC)(ll x, ll y);

const ll MAX_LL = 1L << 62; //(1 << 63) - 1
const int MAX_INT = (int)((1L << 31) - 1);
const double PI = acos(-1);
const double EPS = 0.0000001L;


//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------



int base;
vector<int> seg_tree;

//O(n)
void initSeg(vector<int> &data) {
	base = pow(2, (int)ceil(log2(data.size())) + 1) / 2;
	seg_tree = vector<int>(2 * base, MAX_INT);
	for(int i = base + data.size() - 1; i > 0; i--) {
		if(i >= base) seg_tree[i] = data[i - base];
		else {
			seg_tree[i] = min(seg_tree[2*i], seg_tree[2*i+1]);
		}
	}
}


int _getMin(int idx, int pos, int len, int l, int r) {
	if(pos == l && len == r - l) return seg_tree[idx];
	
	len >>= 1;
	int mm = MAX_INT;
	if(pos + len > l) mm = min(mm, _getMin(2*idx, pos, len, l, min(r, pos + len)));
	if(pos + len < r) mm = min(mm, _getMin(2*idx+1, pos + len, len,  max(l, pos + len), r));
	return mm;
}

//inclusive l, exclusive r
//O(log(n))
int getMin(int l, int r) {
	if(l >= r) return MAX_INT;
	else {
		return _getMin(1, 0, base, l, r);
	}
}


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

void solve() {
	cin >> LCA_MAX;
	graph = vector<vector<int>>(LCA_MAX, vector<int>());
	for(int u = 0; u < LCA_MAX; u++) {
		int n; cin >> n;
		graph[u].resize(n, 0);
		for(int i = 0; i < n; i++) {
			cin >> graph[u][i];
			graph[u][i]--;
		}
	}		
	
	init(0);
	
	int Q; cin >> Q;
	while(Q--) {
		int u,v; cin >> u; cin >> v; 
		
		cout << (lca(u-1, v-1) + 1) << endl;
	}
}

int main() {
	int T; cin >> T;
	for(int i = 0; i < T; i++) {
		cout << "Case " << (i+1) << ":" << endl;
		solve();
	}
	return 0;
}