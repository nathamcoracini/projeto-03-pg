#include "Vector3.h"

Vector3::Vector3(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

double Vector3::getX() { return x; }
double Vector3::getY() { return y; }
double Vector3::getZ() { return z; }