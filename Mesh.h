#ifndef MESH_H
#define MESH_H

#include "Vector3.h"
#include "Face.h"

#include <vector>

using std::vector;

class Mesh {
    private:
        vector<Vector3> v;
        vector<Face> f;
    
    public:
        void pushV(double x, double y, double z);
        void pushF(int v1, int v2, int v3);
        double** translate(double x, double y, double z);
        double** scale(double x, double y, double z);
};

#endif