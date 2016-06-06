//0<=a,b<=n and n <= MAX(ll)/2
//O(logn^2)
ll pow_mod(ll a, ll b, ll n) {
	if(b == 0) return 1;
	if(b == 1) return a % n;
	
	if(b % 2 == 1) return mult_mod(pow_mod(a, b-1, n), a, n);
	else return pow_mod(mult_mod(a, a, n), b / 2, n);
}