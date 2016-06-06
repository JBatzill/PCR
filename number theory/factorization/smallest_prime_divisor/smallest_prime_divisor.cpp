//stores the smallest prime divisor for each i <= PRIME_MAX <= 10^8
const int PRIME_MAX = 100000;
int sd[PRIME_MAX+1];

//precalculates the smallest primefactor for each i <= PRIME_MAX
//O(n*log(log(n)))
void pre() {
	sd[0] = sd[1] = 0;
	for(int i = 2; i <= PRIME_MAX; i++) sd[i] = (i % 2 == 0 ? 2 : i);
	
	for(ll i = 3; i * i <= PRIME_MAX; i+=2) {
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
