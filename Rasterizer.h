#include "Eigen/Dense"
#include "Camera.h"
#include "Mesh.h"
#include <cmath>

#ifndef RASTERIZER_H_
#define RASTERIZER_H_

class Rasterizer {
    private:
        std::vector<Vector3d> bresenham(Vector3d ci, Vector3d cf); 
        int viewport[1920][1080];
       
    public:
        void rasterize(Mesh m);
        void Rasterize();
};

#endif