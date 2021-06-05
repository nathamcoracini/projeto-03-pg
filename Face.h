#ifndef FACE_H
#define FACE_H

class Face {
    private:
        int v1, v2, v3;
    public:
        Face(int v1, int v2, int v3);
        int getV1();
        int getV2();
        int getV3();
};

#endif