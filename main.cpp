#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include "Vector3.h"
#include "Mesh.h"

using namespace std;

Mesh readObj(string filename);

const string ObjFilename = "./3d/coarseTri.botijo.obj";

int main() {
    Mesh mesh = readObj(ObjFilename);
    
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