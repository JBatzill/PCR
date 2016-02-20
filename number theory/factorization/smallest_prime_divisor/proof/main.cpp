//http://codeforces.com/contest/546/problem/D

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


//stores the smallest prime divisor for each i <= PRIME_MAX <= 10^7
const int PRIME_MAX = 5000010;
int sd[PRIME_MAX];

//precalculates the smallest primefactor for each i <= PRIME_MAX
//O(n*log(log(n)))
void pre() {
	sd[0] = sd[1] = 0;
	for(int i = 2; i <= PRIME_MAX; i++) sd[i] = (i % 2 == 0 ? 2 : i);
	
	for(ll i = 3; i * i <= PRIME_MAX; i++) {
		if(sd[i] == i) {
			for(ll n = i*i; n <= PRIME_MAX; n += (i<<1)) {
				if(sd[n] == n) sd[n] = i;
			}
		}
	}
}

//factorizes n (n <= PRIME_MAX!)
//O(log(n))
vector<int> factorize(int n) {
	vector<int> res;
	while(n > 1) {
		res.pb(sd[n]);
		n /= sd[n];
	}
	return res;
}
//-------------------------------------------------------------------------------------------------

int factorize2(int n) {
	int res = 0;
	while(n > 1) {
		res++;
		n /= sd[n];
	}
	return res;
}

int res[PRIME_MAX];
void pre2(int max) {
	res[0] = 0;
	for(int i = 1; i <= max; i++) {
		res[i] = res[i-1] + factorize2(i);
	}
}

void solve() {
	pre();
	pre2(PRIME_MAX);
	
	int N; scanf("%d", &N);
	int a,b; 
	while(N--) {
		scanf("%d%d",&a,&b);
		printf("%d\n",res[a]-res[b]);
	}
	
}

int main() {
	//USE FOR FAST IO
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	solve();
	return 0;
}