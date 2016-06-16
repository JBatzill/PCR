//returns angle on the opposite side of o for triangle l,o,r
double lawOfCosinus(double l, double r, double o) {
    return acos((l*l+r*r-o*o) / (2*l*r));
}
