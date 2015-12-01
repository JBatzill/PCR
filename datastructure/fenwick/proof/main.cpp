//Link to problem: https://open.kattis.com/problems/fenwick
//Link to problem: https://open.kattis.com/problems/fenwick

#include <bits/stdc++.h>

#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef ll (*MY_FUNC)(ll x, ll y);

const ll MAX_LL = 1L << 62; //(1 << 63) - 1
const double EPS = 0.0000001L;


//---------------------------------------------------------------------------------------------
//ios::sync_with_stdio(false); //USE FOR FAST IO
//---------------------------------------------------------------------------------------------

int lsbs(int x) {
	return (x & (-x));
}

const int MAX_FT_SIZE = 5000010;
ll ft[MAX_FT_SIZE];

ll getV(int i) {
	ll res = ft[i];
	while((i -= lsbs(i)) > 0) {
		res += ft[i];
	}
	return res;
}

void setV(int i, ll value) {
	while(i < MAX_FT_SIZE) {
		ft[i] += value;
		i += lsbs(i);
	}	
}

ll getRange(int l, int r) {
	return getV(r) - getV(l - 1);
}


void solve() {
	memset(ft, 0, sizeof(ft));
	ll N,Q; cin >> N >> Q;
	
	for(ll i = 0; i < Q; i++) {
		char c; cin >> c;
		if(c == '+') {
			ll idx, value; cin >> idx >> value;
			setV(idx + 1, value);
		} else {
			ll idx; cin >> idx;
			if(idx == 0) cout << 0 << endl;
			else {
				cout << getRange(1, idx) << endl;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);

	solve();
	return 0;
}