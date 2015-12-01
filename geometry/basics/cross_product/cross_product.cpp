//cross product in 2d is the z coordinate of the cross product of the vectors in 3d with z = 0
ll X2(point2 p1, point2 p2) {
	return (p1.x * p2.y) - (p1.y * p2.x);
}

ll X3(point3 p1, point3 p2) {
	point3 res;
	res.x = (p1.y * p2.z) - (p1.z * p2.y);
	res.y = (p1.z * p2.x) - (p1.x * p2.z);
	res.z = (p1.x * p2.y) - (p1.y * p2.x);
	return res;
}