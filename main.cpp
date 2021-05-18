#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const string ObjFilename = "./3d/coarseTri.botijo.obj";

int main() {
    ifstream file(ObjFilename);
    string line;

    if (file.is_open()) {
        while (getline (file, line)) {
            cout << line << '\n';
        }

        file.close();
    }

    return 0;
}