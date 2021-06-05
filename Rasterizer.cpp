#include "Rasterizer.h"

void Rasterizer::rasterize(Mesh m) {
    vector<Vector3d> pontos = m.getV();
    vector<Face> faces = m.getF();

    for (unsigned i = 0; i < faces.size(); i++) {
        std::vector<vector3d> line1, line2, line3;
        line1 = bresenham(pontos[faces[i].getV1()], pontos[faces[i].getV2()]);
        line2 = bresenham(pontos[faces[i].getV1()], pontos[faces[i].getV3()]);
        line3 = bresenham(pontos[faces[i].getV2()], pontos[faces[i].getV3()]);
    }
}

std::vector<Vector3d> Rasterizer::bresenham(Vector3d ci, Vector3d cf) {
    int xi = ci.x(), xf =  cf.x(),  yi =  cf.y(), yf = cf.y();

    // Ajusta octante
    if (xi > xf) {
        xf = -xf;
        xi = -xi;
    }
    if (yi > yf) {
        yf = -yf;
        yi = -yi;
    }
    
    
    int m = 2 * (yf - yi);
    int inclinacao = m - (xf - xi);

    int j = yi;

    std::vector<Vector3d> res;

    for (int i = xi; i <= xf; i++)
    {
        Vector3d aux;

        aux.x() = i;
        aux.y() = j;

        res.push_back(aux);

        inclinacao += m;

        if (inclinacao >= 0)
        {
            j++;
            inclinacao  -= 2 * (xf - xi);
        }
    }

    return res;
}

void Rasterize::Rasterize() {
    for (int i = 0; i < 1920; i++) {
        for (int j = 0; i < 1080; j++) {
            viewport[i] = 0;
        }
    }
}