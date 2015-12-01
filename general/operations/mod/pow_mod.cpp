//a,b <=n and n <= MAX(ll)/2
ll pow_mod(ll a, ll b, ll n) {
	if(a == 0) return 0;
	if(b == 1) return a % n;
	
	if(b % 2 == 1) return mult_mod(a, pow_mod(a, b-1, n), n);
	else return pow_mod(mult_mod(a, a, n), b / 2, n);
}