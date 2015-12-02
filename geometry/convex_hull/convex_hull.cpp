//returns in ccw order
//for colinear points in hull remove '='
//first != last
vector<point2> convexHull(vector<point2> &points) {
	int k = 0, n = points.size();
	vector<point2> hull(n+2);
	sort(points.begin(), points.end(), [](const point2 &p1, const point2 &p2) {
		return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
	});
	
	//lower hull
	for(int i = 0; i < n; i++) {
		while(k >= 2 && ccw(hull[k-2], hull[k-1], points[i]) <= 0) k--;
		hull[k++] = points[i];
	}
	
	//upper hull
	for(int i = n - 2, t = k + 1; i >= 0; i--) {
		while(k >= t && ccw(hull[k-2], hull[k-1], points[i]) <= 0) k--;
		hull[k++] = points[i];
	}
	
	hull.resize(max(0, k - 1));
	return hull;
}