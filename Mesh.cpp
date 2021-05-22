#include "Mesh.h"

void Mesh::pushV(double x, double y, double z) {
    Vector3 vec3(x, y, z);
    v.push_back(vec3);
}

void Mesh::pushF(int v1, int v2, int v3) {
    Face vec3(v1, v2, v3);
    f.push_back(vec3);
}

// double** Mesh::translate(double x, double y, double z) {
//     double pf[4];
//     double d[][4] = {{1, 0, 0, x},
//                     {0, 1, 0, y},
//                     {0, 0, 1, z},
//                     {0, 0, 0, 1}};
//     double p[4];

//     for (Vector3 i : v) {

//         p[0] = i.getX();
//         p[1] = i.getY();
//         p[2] = i.getZ();
//         p[3] = 1;

//         for (int j = 0; j < 4; j++) {
//             pf[0] = p[0] + d[j][0];
//             pf[1] = p[1] + d[j][1];
//             pf[2] = p[2] + d[j][2];
//             pf[3] = 1;
//         }

        
        
//     }

//     return d;
// }

// double** Mesh::scale(double x, double y, double z) {
//         double **d = new double[][4];

//         d = {{x, 0, 0, 0},
//             {0, y, 0, 0},
//             {0, 0, z, 0},
//             {0, 0, 0, 1}};

//         return d;
// }
