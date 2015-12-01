//p1 -> p2 -> p3
//ccw(=counter clockwise) > 0
//colinear == 0
//cw < 0
ll ccw(point2 p1, point2 p2, point2 p3) {
    return X2(p2-p1, p3-p1);
}