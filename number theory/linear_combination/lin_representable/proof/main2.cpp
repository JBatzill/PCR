//http://codeforces.com/problemset/problem/681/B
#include <bits/stdc++.h>

#define pb push_back

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef ll (*MY_FUNC)(ll x, ll y);

const ll MAX_LL = 1LL << 62; //(1 << 63) - 1
const int MAX_INT = (int)((1LL << 31) - 1);
const double PI = acos(-1);
const double EPS = 0.0000001L;
const ll MOD = 1000000007;


//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

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

void solve() {
    vector<int> g = {1234, 123456, 1234567};

    ll n; cin >> n;

    cout << (linRepresentable(g, n) ? "YES" : "NO") << endl;
}

int main() {
	//USE FOR FAST IO
	ios::sync_with_stdio(false);
	solve();
	return 0;
}
