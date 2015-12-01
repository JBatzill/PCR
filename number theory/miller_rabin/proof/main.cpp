//https://open.kattis.com/problems/primes2

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
//ios::sync_with_stdio(false); //USE FOR FAST IO
//setprecision(10); fixed; //USE FOR PRECISE OUTPUT
//---------------------------------------------------------------------------------------------

int base[4] = {2, 8, 10, 16};

//a,b <=n and n <= MAX(ll)/2
ll mult_mod(ll a, ll b, ll n) {
	if(a == 0 || b == 0) return 0;
	if(b == 1) return a % n;
	
	if(b % 2 == 1) return (a + mult_mod(a, b-1, n)) % n;
	else return mult_mod((a + a) % n, b / 2, n);
}

//a,b <=n and n <= MAX(ll)/2
ll pow_mod(ll a, ll b, ll n) {
	if(a == 0) return 0;
	if(b == 1) return a % n;
	
	if(b % 2 == 1) return mult_mod(a, pow_mod(a, b-1, n), n);
	else return pow_mod(mult_mod(a, a, n), b / 2, n);
}

//theoretical: n < 318,665,857,834,031,151,167,461 ( > 10^23)
//but: n ~<= 10^18 (because of MAX(ll))
//O(logn)
bool isPrime(ll n) {
	if(n == 2) return true;
	if(n < 2 || n % 2 == 0) return false;
	ll d=n-1,j=0;
	while(d % 2 == 0) d >>= 1, j++;
	for(int a = 2; a <= min((ll)37, n-1); a++) {
		ll v = pow_mod(a, d, n);
		if(v == 1 || v == n-1) continue;
		for(int i = 1;  i <= j; i++) {
			v = mult_mod(v, v, n);
			if(v == n-1 || v <= 1) break;
		}
		
		if(v != n-1) return false;
	}
	return true;
}

//a >= b
ll gcd(ll a, ll b) {
	if(b == 0) return a;
	else return gcd(b, a % b);
}

void solve() {
	string s; cin >> s;
	ll res[4] = {0,0,0,0};
	
	for(char c: s) {
		ll val;
		
		if('0' <= c && c <= '9') val = (ll)(c - '0');
		else val = (ll)(c - 'A') + 10;
		
		for(int i = 0; i < 4; i++) {
			if(res[i] == -1) continue;
			else if(val >= base[i]) {
				res[i] = -1;
				continue;
			} else {
				res[i] = (res[i] * base[i]) + val;
			}
		}
	}
	

	
	int count = 0, prime = 0;
	for(int i = 0; i < 4; i++) {
		if(res[i] == -1) continue;
		
		count++;
		if(isPrime(res[i]))prime++;
	}
	
	int d = gcd(count, prime);
	
	cout << (prime / d) << "/" << (count / d) << endl;
	
}

int main() {
	int T; cin >> T;
	while(T--) {
		solve();
	}
	return 0;
}