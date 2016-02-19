const int MAX_UF_SIZE = 1000010;
ll uf[MAX_UF_SIZE]; //init: -1

//returns index of the representative of the set containing idx
//O(alpha(n)) ~ const
int find(int idx) {
	return (uf[idx] < 0 ? idx : (uf[idx] = find(uf[idx])));
}


//unites the set containing a with the set containing b
//O(alpha(n)) ~ const
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