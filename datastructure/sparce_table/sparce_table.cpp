const int RMQ_SIZE = 1000;
ll data[RMQ_SIZE], rmq[((int)log2(RMQ_SIZE)) + 1][RMQ_SIZE];

//O(n*log(n))
void initRMQ() {
	memset(rmq, 0, sizeof(rmq));
	for(int i = 0, l = 1, ol = 1; l <= RMQ_SIZE; i++, ol = l, l <<= 1) {	
		for(int k = 0; k + l <= RMQ_SIZE; k++) {
			if(l == 1) rmq[i][k] = k;
			else rmq[i][k] = (data[rmq[i-1][k]]  <= data[rmq[i-1][k+ol]] ? rmq[i-1][k] : rmq[i-1][k+ol]);
		}
	}
}

//returns index of minimum of [a, b)
//O(1)
ll queryRMQ(int a, int b) {
	if(a >= b) return b;
	int l = (int)log2(b-a);
	b = b - (1 << l);
	return (data[rmq[l][a]] <= data[rmq[l][b]] ? rmq[l][a] : rmq[l][b]);
}