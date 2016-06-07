int base;
vector<pii> seg_tree;

//O(n)
void initSeg(int size) {
	base = pow(2, (int)ceil(log2(size	)) + 1) / 2;
	seg_tree = vector<pii>(2 * base, {0, 0});
}


int _getSum(int idx, int pos, int len, int l, int r, int rot) {
	if(pos == l && len == r - l) {
		int mm = seg_tree[idx].first;
		if(rot % 2 == 1) mm = len - mm;
		return mm;
	}
	
	rot = (rot + seg_tree[idx].second) % 2;
	len >>= 1;
	int mm = 0;
	if(l < pos + len) mm +=  _getSum(2*idx, pos, len, l, min(r, pos + len), rot);
	if(pos + len < r) mm += _getSum(2*idx+1, pos + len, len,  max(l, pos + len), r, rot);
	
	return mm;
}

void _flip(int idx, int pos, int len, int l, int r, int rot) {
	if(pos == l && len == r - l) {
		if(rot) {
			//cout << l << " to " << (r-1)	 << " switch " << endl;
			seg_tree[idx].first = len - seg_tree[idx].first;
			seg_tree[idx].second = (seg_tree[idx].second + 1) % 2;
		}
		return;
	}
	
	len >>= 1;
	
	_flip(2*idx, 0, len, 0, len, seg_tree[idx].second);
	_flip(2*idx+1, 0, len, 0, len, seg_tree[idx].second);
	

	if(l < pos + len) _flip(2*idx, pos, len, l, min(r, pos + len), 1);
	if(pos + len < r) _flip(2*idx+1, pos + len, len,  max(l, pos + len), r, 1);
	
	seg_tree[idx].second = 0;
	seg_tree[idx].first = seg_tree[2*idx].first + seg_tree[2*idx+1].first;
}

//inclusive l, exclusive r
//O(log(n))
int getSum(int l, int r) {
	if(l >= r) return 0;
	else {
		return _getSum(1, 0, base, l, r, 0);
	}
}

//inclusive l, exclusive r
//O(log(n))
void flip(int l, int r) {
	if(l < r) {
		_flip(1, 0, base, l, r, 1);
	}
}
