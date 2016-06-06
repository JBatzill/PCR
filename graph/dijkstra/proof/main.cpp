//http://codeforces.com/problemset/problem/20/C
#include <bits/stdc++.h>

#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef ll (*MY_FUNC)(ll x, ll y);

const ll MAX_LL = (1LL << 62); //(1 << 63) - 1
const int MAX_INT = (int)((1LL << 31) - 1);
const double PI = acos(-1);
const double EPS = 0.0000001L;


//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------


vector<int> parent;
vector<vector<pii>> graph;

//O(|E|*log|V|)
ll dijkstra(vector<vector<pii>> &graph, int start, int end) {
	vector<ll> dist = vector<ll>((int)graph.size(), MAX_LL);
	dist[0] = 0;
	priority_queue<pll, vector<pll>, greater<pll>> pq;
	pq.push({0, start});
	
	while(!pq.empty()) {
		pll node = pq.top(); pq.pop();
		
		if(node.first > dist[node.second]) continue;
		if(node.second == end) break; //remove for dist to all
		
		for(pii &edge: graph[node.second]) {
			if(dist[node.second] + edge.second < dist[edge.first]) {
				dist[edge.first] = dist[node.second] + edge.second;
				parent[edge.first] = node.second;
				pq.push({dist[edge.first], edge.first});
			}
		}
	}
	
	return dist[end];
}

void print(int i) {
	if(i == -1) return;
	print(parent[i]);
	cout << (i > 0 ? " " : "") << (i+1);
}

void solve() {
	int n,m; cin >> n >> m;
	graph = vector<vector<pii>>(n, vector<pii>());
	for(int i = 0; i < m; i++) {
		int a,b,w; cin >> a >> b >> w; a--; b--;
		graph[a].pb({b, w});
		graph[b].pb({a, w});
	}
	
	parent = vector<int>(n, -1);
	dijkstra(graph, 0, n-1);
	
	if(parent[n-1] == -1) cout << -1 << endl;
	else {
		print(n-1);
	}
}

int main() {
	//USE FOR FAST IO
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	solve();
	return 0;
}