//returns the square of the eucl. dist
double dist2(double x1, double y1, double x2, double y2) {
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
//returns the eucl dist
double dist(double x1, double y1, double x2, double y2) {
    return sqrt(dist2(x1, y1, x2, y2));
}
