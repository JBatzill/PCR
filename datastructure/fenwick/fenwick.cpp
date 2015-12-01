const int MAX_FT_SIZE = 1 << 15;
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