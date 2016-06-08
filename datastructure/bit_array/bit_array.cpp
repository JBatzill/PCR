typedef vector<ull> bit_array;
void initBitArray(bit_array &a, int size) {
    int len = (size / (sizeof(ull) * 8)) + (size % (sizeof(ull) * 8) == 0 ? 0 : 1);
    a.resize(len, 0);
}
void flushBitArray(bit_array &a, bool v) {
    fill(a.begin(), a.end(), (v ? (ull)-1 : 0));
}
void setBit(bit_array &a, int pos, bool v) {
    int idx = pos / (sizeof(ull) * 8), offset = pos % (sizeof(ull) * 8);
    if(v == 1) a[idx] |= ((ull)1) << offset;
    else a[idx] &= ~(((ull)1) << offset);
}
bool getBit(bit_array &a, int pos) {
    int idx = pos / (sizeof(ull) * 8), offset = pos % (sizeof(ull) * 8);
    return (a[idx] & (((ull)1) << offset)) > 0;
}
int getSize(bit_array &a) {
    return a.size() * sizeof(ull) * 8;
}
