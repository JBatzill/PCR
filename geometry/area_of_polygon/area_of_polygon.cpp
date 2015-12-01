//polygon does not cut itself, startpoint != endpoint
double areaOfPolygon(vector<point2> &pol) {
	double res = 0; int n = pol.size();
	for(int i = 0; i < n; i++) {
		res += X2(pol[i], pol[(i+1) % n]);
	}
	return abs((res / 2.0L));
}