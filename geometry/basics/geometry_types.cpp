typedef struct { ll x, y; } point2;
point2 operator+(const point2 &p1, const point2 &p2) {
	return (point2 {p1.x + p2.x, p1.y + p2.y});
} 
point2 operator-(const point2 &p1, const point2 &p2) {
	return (point2 {p1.x - p2.x, p1.y - p2.y});
}

typedef struct { ll x, y, z; } point3;
point3 operator+(const point3 &p1, const point3 &p2) {
	return (point3 {p1.x + p2.x, p1.y + p2.y, p1.z + p2.z});
}
point3 operator-(const point3 &p1, const point3 &p2) {
	return (point3 {p1.x - p2.x, p1.y - p2.y, p1.z - p2.z});
}