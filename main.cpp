#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include "Mesh.h"
#include "Translate.h"
#include "Scale.h"
#include "Eigen/Dense"
#include "Camera.h"

using namespace Eigen;

using namespace std;

Mesh readObj(string filename);

const string ObjFilename = "./3d/coarseTri.botijo.obj";

int main() {
    Mesh mesh = readObj(ObjFilename);

    Vector3d t(2.0, 2.0, 2.0);
    Matrix4d m = translate(t);
    cout << "Teste Matriz de Transformacao de Translacao: " << endl << m << endl << endl;

    Matrix4d s = scale(t);
    cout << "Teste Matriz de Transformacao de Escala: " << endl << s << endl << endl;

    Vector3d pos(20.0, 20.0, 20.0);
    Vector3d target(0.0, 0.0, 0.0);
    double aspectRatio = 16/9;
    double fov = 90.0;
    double far = 25.0;
    double near = 1.0;

    Camera c(pos, target, aspectRatio, fov, far, near);

    return 0;
}

Mesh readObj(string filename) {
    ifstream file(filename);
    string line;
    Mesh mesh;

    if (file.is_open()) {
        
        while (getline (file, line)) {
            istringstream is(line);
            string x, y, z, pablo;
            string v1, v2, v3;

            if (line[0] == 'v') {

                getline(is, pablo,' ');
                getline(is, x,' ');
                getline(is, y,' ');
                getline(is, z,' ');

                mesh.pushV(stod(x), stod(y), stod(z));
            }
            else if (line[0] == 'f') {

                getline(is, pablo,' ');
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