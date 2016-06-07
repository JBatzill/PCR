int base;
vector<int> seg_tree;

//O(n)
void initSeg(vector<int> &data) {
	base = pow(2, (int)ceil(log2(data.size())) + 1) / 2;
	seg_tree = vector<int>(2 * base, MAX_INT);
	for(int i = base + data.size() - 1; i > 0; i--) {
		if(i >= base) seg_tree[i] = data[i - base];
		else {
			seg_tree[i] = min(seg_tree[2*i], seg_tree[2*i+1]);
		}
	}
}

int _getMin(int idx, int pos, int len, int l, int r) {
	if(pos == l && len == r - l) return seg_tree[idx];
	
	len >>= 1;
	int mm = MAX_INT;
	if(pos + len > l) mm = min(mm, _getMin(2*idx, pos, len, l, min(r, pos + len)));
	if(pos + len < r) mm = min(mm, _getMin(2*idx+1, pos + len, len,  max(l, pos + len), r));
	return mm;
}

//inclusive l, exclusive r
//O(log(n))
int getMin(int l, int r) {
	if(l >= r) return MAX_INT;
	else {
		return _getMin(1, 0, base, l, r);
	}
}