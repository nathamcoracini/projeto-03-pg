#ifndef VECTOR_3_H
#define VECTOR_3_H

class Vector3 {
    private:
        double x, y, z;

    public:
        Vector3(double x, double y, double z);
        double getX();
        double getY();
        double getZ();
        
};

#endif