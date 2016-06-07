//https://open.kattis.com/problems/maxflow

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


int M, S, T;
vector<vector<edge>> graph2;


void ouputFlowGraphDetails() {
	int count = 0;
	stringstream ss;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < graph[i].size(); j++) {
			if(graph2[i][j].weight > graph[i][j].weight) {
				count++;
				ss << i << " " << graph[i][j].dest << " " << (graph2[i][j].weight - graph[i][j].weight) << endl;
			}
		}
	}
	
	cout << count << endl;
	cout << ss.str();
}

void solve() {
	cin >> N >> M >> S >> T;
	graph = vector<vector<edge>>(N, vector<edge>());
	graph2 = vector<vector<edge>>(N, vector<edge>());
	for(int i = 0; i < M; i++) {
		int u,v,c; cin >> u >> v >> c;
		graph[u].pb(edge {v, (int)graph[v].size(), (ll)c});
		graph[v].pb(edge {u, (int)graph[u].size() - 1, 0L});
		
		graph2[u].pb(edge {v, (int)graph2[v].size(), (ll)c});
		graph2[v].pb(edge {u, (int)graph2[u].size() - 1, 0L});
	}
	
	ll flow = maxFlow(S, T);
	
	cout << N << " " << flow << " ";
	ouputFlowGraphDetails();
}

int main() {
	solve();
	return 0;
}