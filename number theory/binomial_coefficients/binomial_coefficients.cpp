//O(n*log(n))    more specific: O(min(n-k, k) * log(n))
ll binFac(int n, int k) {
	k = max(k, n-k);
	ll res = 1, nn = k;
	while(nn++ < n) {
		ll d = nn - k, f = nn, d1 = gcd(f, d);
		res = (res / (d/d1)) * (f / d1);
	}
	return res;
}