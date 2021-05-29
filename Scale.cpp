#include "Scale.h"

Matrix4d scale(Vector3 v) {
    Matrix4d m;
    m << v.getX(), 0,        0,        0,
         0,        v.getY(), 0,        0,
         0,        0,        v.getZ(), 0,
         0,        0,        0,        1;

    return m;
}