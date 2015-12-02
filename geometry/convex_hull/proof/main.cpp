//https://open.kattis.com/problems/convexhull

#include <bits/stdc++.h>

#define pb push_back
#define FORI(i,a,b) for(int i=a; i<b; i++)
#define REPI(i,n) FORI(i,0,n)

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef ll (*MY_FUNC)(ll x, ll y);

const ll MAX_LL = 1L << 62; //(1 << 63) - 1
const int MAX_INT = (int)((1L << 31) - 1);
const double PI = acos(-1);
const double EPS = 0.0000001L;


//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

typedef struct { ll x, y; } point2;
point2 operator+(const point2 &p1, const point2 &p2) {
	return (point2 {p1.x + p2.x, p1.y + p2.y});
} 
point2 operator-(const point2 &p1, const point2 &p2) {
	return (point2 {p1.x - p2.x, p1.y - p2.y});
}
bool operator==(const point2 &p1, const point2 &p2) {
	return (p1.x == p2.x) && (p1.y == p2.y);
}

//cross product in 2d is the z coordinate of the cross product of the vectors in 3d with z = 0
ll X2(point2 p1, point2 p2) {
	return (p1.x * p2.y) - (p1.y * p2.x);
}

//p1 -> p2 -> p3
//ccw(=counter clockwise) > 0
//colinear == 0
//cw < 0
ll ccw(point2 p1, point2 p2, point2 p3) {
    return X2(p2-p1, p3-p1);
}

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


int n;
vector<point2> points;

void solve() {
	points = vector<point2>(n, point2 {0,0});
	REPI(i, n) {
		cin >> points[i].x >> points[i].y;
	}
	vector<point2> res = convexHull(points);
	
	//only one node
	if(res.size() == 0) {
		res.pb(points[0]);
	} else if(res.size() == 2) {
		if(res[0] == res[1]) {
			res.resize(1);
		}
	}
	
	cout << res.size() << endl;
	
	for(point2 &p: res) {
		cout << p.x << " " << p.y << endl;
	}
	
}

int main() {

	ios::sync_with_stdio(false);

	while(cin >> n, n > 0) {
		solve();
	}
	return 0;
}