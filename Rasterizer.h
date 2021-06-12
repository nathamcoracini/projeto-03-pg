#include "Eigen/Dense"
#include "Camera.h"
#include "Mesh.h"
#include "Face.h"

#ifndef RASTERIZER_H_
#define RASTERIZER_H_

class Rasterizer {
    private:
        void bresenham(Vector4d &ci, Vector4d &cf);
        int h;
        int w;
        vector<Vector4d> changeCoord(vector<Vector4d> v);
       
    public:
        void rasterize(std::vector<Vector4d> &v, std::vector<Face> &f);
        Rasterizer(const int &h, const int &w);
        std::vector<unsigned char> image;
};

#endif