#include "Face.h"

Face::Face(int v1, int v2, int v3) {
    v1 = v1;
    v2 = v2;
    v3 = v3;
}

int Face::getV1() {
    return v1;
}
int Face::getV2() {
    return v2;
}
int Face::getV3() {
    return v3;
}