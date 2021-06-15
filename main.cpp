#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <float.h>
#include <stack>

#include "Mesh.h"
#include "Translate.h"
#include "Scale.h"
#include "Rasterizer.h"
#include "Camera.h"

#include "Eigen/Dense"
#include "lodepng.h"    

using namespace Eigen;
using namespace std;

/*********************************
****Função para leitura de OBJ****
**********************************/
Mesh readObj(string filename);

/*****************************
****Função para gerar o PNG***
******************************/
void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height);

/***************************************************
****Função para converter graus em radianos*********
****************************************************/
double rad(double ang);

/* Retorna o vetor do centro de uma mesh */
Vector3d center(Mesh m);

/* Retorna o máximo de um vetor */
Vector3d maxArr(vector<Vector3d> v);

/* Retorna o mínimo de um vetor */
Vector3d minArr(vector<Vector3d> v);

/* Normaliza o vetor para a escala -1 a 1 */
Vector3d normalize(Mesh m);

/* Monta a matriz model */
Matrix4d getModel(stack<Matrix4d> s);

/*******************
*****CONSTANTES*****
********************/
const string ObjFilename = "./3d/coarseTri.cube.obj";
const string OutFilename = "result.png";
const double PI = 3.142592654;
const int WIDTH = 1000;
const int HEIGHT = 1000;

int main() {

    Mesh mesh = readObj(ObjFilename);

    stack<Matrix4d> s;

    // Move o objeto para o centro
    Vector3d ctr = center(mesh);
    Matrix4d toCenter = translate(-ctr);

    // Normaliza o objeto entre -1 e 1
    s.push(toCenter);

    Vector3d scl = normalize(mesh);
    Matrix4d normalized = scale(scl);
    
    s.push(normalized);

    Matrix4d model = getModel(s);

    Vector3d pos(40.0, 10.0, 10.0);
    Vector3d target(0.0, 0.0, 0.0);
    Vector3d upCoord(0.0, 1.0, 0.0);

    double aspectRatio = 1;
    double fov = 60.0;
    double far = 40.0;
    double near = 0.1;

    Camera c(pos, target, aspectRatio, rad(fov), far, near, upCoord);

    Matrix4d final = c.getCameraFinal() * model;
    

    vector<Vector4d> result;

    for (unsigned i = 0; i < mesh.v.size(); i++) {
        Vector4d vertice(mesh.v[i].x(), mesh.v[i].y(), mesh.v[i].z(), 1.0);
        result.push_back(final * vertice);
    }

    for (unsigned i = 0; i < result.size(); i++) {
        result[i] /= result[i].w();
    }


    Rasterizer r(HEIGHT, WIDTH, near * tan(rad(fov) / 2.0), aspectRatio * (near * tan(rad(fov) / 2.0) ) );
    r.rasterize(result, mesh.f);

    std::vector<unsigned char> image = r.image;

    encodeOneStep(OutFilename.c_str(), image, WIDTH, HEIGHT);

    return 0;
}

Mesh readObj(string filename) {
    ifstream file(filename);
    string line;
    Mesh mesh;

    if (file.is_open()) {
        
        while (getline (file, line)) {
            istringstream is(line);
            string x, y, z, tmp;
            string v1, v2, v3;

            if (line[0] == 'v') {

                getline(is, tmp,' ');
                getline(is, x,' ');
                getline(is, y,' ');
                getline(is, z,' ');

                mesh.pushV(stod(x), stod(y), stod(z));
            }
            else if (line[0] == 'f') {

                getline(is, tmp,' ');
                getline(is, v1,' ');
                getline(is, v2,' ');
                getline(is, v3,' ');

                mesh.pushF(stoi(v1) - 1, stoi(v2) - 1, stoi(v3) - 1);
                
            }

        }

        file.close();

    }

    return mesh;
}

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
  unsigned error = lodepng::encode(filename, image, width, height);

  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

double rad(double ang) {

    return (ang * (PI / 180));
}

Vector3d center(Mesh m) {
    Vector3d maxVal = maxArr(m.v);
    Vector3d minVal = minArr(m.v);

    return (maxVal + minVal) / 2.0;
}

Vector3d maxArr(vector<Vector3d> v) {
    Vector3d aux(-DBL_MAX, -DBL_MAX, -DBL_MAX);
    for (unsigned i = 0; i < v.size(); i++) {
        aux.x() = max(aux.x(), v[i].x());
        aux.y() = max(aux.y(), v[i].y());
        aux.z() = max(aux.z(), v[i].z());
    }

    return aux;
}

Vector3d minArr(vector<Vector3d> v) {
    Vector3d aux(DBL_MAX, DBL_MAX, DBL_MAX);
    for (unsigned i = 0; i < v.size(); i++) {
        aux.x() = min(aux.x(), v[i].x());
        aux.y() = min(aux.y(), v[i].y());
        aux.z() = min(aux.z(), v[i].z());
    }
    
    return aux;
}

Vector3d normalize(Mesh m) {
    Vector3d maxVal = maxArr(m.v);
    Vector3d minVal = minArr(m.v);

    double maxX = maxVal.x();
    double maxY = maxVal.y();
    double maxZ = maxVal.z();

    double minX = minVal.x();
    double minY = minVal.y();
    double minZ = minVal.z();

    double mymax = std::max(maxX - minX, std::max(maxY - minY, maxZ - minZ));

    return Vector3d(2 / (mymax), 2 / (mymax), 2 / (mymax));
}

Vector3d normalize2(Mesh m) {
    Vector3d maxVal = maxArr(m.v);
    Vector3d minVal = minArr(m.v);

    double maxX = maxVal.x();
    double maxY = maxVal.y();
    double maxZ = maxVal.z();

    double minX = minVal.x();
    double minY = minVal.y();
    double minZ = minVal.z();

    return Vector3d(2 / (maxX - minX), 2 / (maxY - minY), 2 / (maxZ - minZ));
}

Matrix4d getModel(stack<Matrix4d> s) {
    Matrix4d result;
    result << 1, 0, 0, 0
            ,  0, 1, 0, 0
            ,  0, 0, 1, 0
            ,  0, 0, 0, 1;

    while (!s.empty()) {
        result *= s.top();
        s.pop();
    }
    return result;
}