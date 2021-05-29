#include "Translate.h"

Matrix4d translate(Vector3 v) {
    Matrix4d m;
    m << 1, 0, 0, v.getX(),
         0, 1, 0, v.getY(),
         0, 0, 1, v.getZ(),
         0, 0, 0, 1;

    return m;
}


