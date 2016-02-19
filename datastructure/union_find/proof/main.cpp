//Link to problem: https://open.kattis.com/problems/unionfind

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

const int MAX_UF_SIZE = 1000010;
ll uf[MAX_UF_SIZE]; //init: -1

int find(int idx) {
	return (uf[idx] < 0 ? idx : (uf[idx] = find(uf[idx])));
}

void unite(int a, int b) {
	a = find(a), b = find(b);
	
	if(a == b) return;
	
	if(-uf[a] < -uf[b]) uf[a] = b;
	else if(-uf[a] > -uf[b]) uf[b] = a;
	else {
		uf[b] = a;
		uf[a]--;
	}
}

void solve() {
	int n,q; cin >> n >> q;
	memset(uf, -1, sizeof(uf));

	char c; int a,b;
	for(int i = 0 ; i < q; i++) {
		cin >> c >> a >> b;
		
		if(c == '?') {
			cout << (find(a) == find(b) ? "yes" : "no") << endl;
		} else {
			unite(a,b);
		}
	}
}

int main() {

	ios::sync_with_stdio(false);


	solve();
	return 0;
}