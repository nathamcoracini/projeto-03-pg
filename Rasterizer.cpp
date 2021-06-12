#include "Rasterizer.h"
#include <cmath>
#include <iostream>

void Rasterizer::rasterize(std::vector<Vector4d> &v, std::vector<Face> &f) {

    for (unsigned i = 0; i < f.size(); i++) {

        std::vector<Vector4d> vtrans = changeCoord(v);

        /* Desenha as linhas de um triângulo */
        
        Vector4d vi, vf;
        vi = vtrans[f[i].getV1()];
        std::cout << i << std::endl;
        std::cout << f.size() << std::endl << f[i].getV2() << std::endl;
        vf = vtrans[f[i].getV2()];

        bresenham(vi, vf);

        vi = vtrans[f[i].getV1()];
        vf = vtrans[f[i].getV3()];

        bresenham(vi, vf);

        vi = vtrans[f[i].getV2()];
        vf = vtrans[f[i].getV3()];

        bresenham(vi, vf);

        /* Preenche o triângulo */
        // std::vector<Vector3d> result = scanline(line1, line2, line3);
    }

}

/* Z-Buffer */
/* Ficar sempre com o maior valor do Z*/

void Rasterizer::bresenham(Vector4d &ci, Vector4d &cf) {
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

    for (int i = xi; i <= xf; i++)
    {
        /* Pintar cada pixel */   
        // image[4 * w * j + 4 * i + 0] = 255;
        // image[4 * w * j + 4 * i + 1] = 255;
        // image[4 * w * j + 4 * i + 2] = 255;
        // image[4 * w * j + 4 * i + 3] = 255;

        inclinacao += m;

        if (inclinacao >= 0)
        {
            j++;
            inclinacao  -= 2 * (xf - xi);
        }
    }
}

Rasterizer::Rasterizer(const int &h, const int &w) {

    this->h = h;
    this->w = w;

    /* Inicia o vetor de imagem */
    image.resize(w * h * 4);
    for(int y = 0; y < h; y++)
        for(int x = 0; x < w; x++) {
            image[4 * w * y + 4 * x + 0] = 0;
            image[4 * w * y + 4 * x + 1] = 0;
            image[4 * w * y + 4 * x + 2] = 0;
            image[4 * w * y + 4 * x + 3] = 0;
        }
}

vector<Vector4d> Rasterizer::changeCoord(vector<Vector4d> v) {

    vector<Vector4d> final;
    for (unsigned i = 0; i < v.size(); i++) {
        final.push_back(Vector4d( (v[i].x() + 1) * w / 2, (v[i].y() + 1) * h / 2, v[i].z(), v[i].w() ) );
    }

    return final;

}