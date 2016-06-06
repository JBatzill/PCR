//GCPC 2016 - Problem C --- not tested yet!!
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

vector<vector<pii>> graph;

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
		
		for(pii edge: graph[node.second]) {
			if(dist[node.second] + edge.second < dist[edge.first]) {
				dist[edge.first] = dist[node.second] + edge.second;
				// parent[edge.first] = node.second;
				pq.push((pll){dist[edge.first], edge.first});
			}
		}
	}
	
	return dist[end];
}

//checks wheter there exists a vector a >= 0 s.t. a'*g=k or not
//O(dijkstra)
bool linRepresentable(vector<int> g, ll k) {

	//get minimal element for smallest graph
	int m = g[0];
	for(int gi: g) m = min(m, gi);
	
	//get all moves O(m+n) (generate + extract)
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

void solve() {
	ll n,k; cin >> n >> k;
	
	vector<int> g = vector<int>(n);
	for(int i = 0; i < n; i++) cin >> g[i];
	
	if(linRepresentable(g, k)) cout << "possible" << endl;
	else cout << "impossible" << endl;
	
}



int main() {
	solve();
	return 0;
}