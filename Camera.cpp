#include "Camera.h"
#include <iostream>

Camera::Camera(Vector3d pos, Vector3d target, double aspectRatio, double fov, double far, double near, int upDirection) {
    this->pos = pos;
    this->target = target;
    this->aspectRatio = aspectRatio;
    this->fov = fov;
    this->far = far;
    this->near = near;
    this->upDirection = upDirection;

    Vector3d tmp = pos - target;
    cameraDirection = tmp.normalized();
    std::cout << cameraDirection << std::endl << std::endl;

    //TODO: Deixar tmp como parametro
    tmp = Vector3d(0.0, upDirection, 0.0);

    tmp = tmp.cross(cameraDirection);
    cameraRight = tmp.normalized();
    std::cout << cameraRight << std::endl << std::endl;

    tmp = cameraDirection.cross(cameraRight);
    cameraUp = tmp;
    std::cout << cameraUp << std::endl << std::endl;

    Matrix4d m;
    m << cameraRight.x() ,    cameraRight.y() ,     cameraRight.z(),     0
      , cameraUp.x() ,        cameraUp.y() ,        cameraUp.z(),        0
      , cameraDirection.x() , cameraDirection.y() , cameraDirection.z(), 0
      , 0                   , 0,                    0,                   1;

    Matrix4d n;
    n << 1 ,    0 , 0, -pos.x()
      ,  0 ,    1 , 0, -pos.y()
      ,  0 ,    0 , 1, -pos.z()
      ,  0 ,    0 , 0,        1;

    std::cout << m << std::endl << std::endl;
    std::cout << n << std::endl << std::endl;

    cameraLookAt = m * n;

    std::cout << cameraLookAt << std::endl << std::endl;

    cameraPerspective << 1 / (aspectRatio * tan(fov * (M_PI / 180))) ,                              0,                            0,                              0
                                                                     , 0, 1 / tan(fov * (M_PI / 180)),                            0,                              0
                                                                     , 0,                           0, -((far + near)/(far - near)), -((2 * far * near)/(far-near))
                                                                     , 0,                           0,                           -1,                              0;

    std::cout << cameraPerspective << std::endl << std::endl;

    //finais = PERSP  * LAT * M * pontos
}

void Camera::setPos(Vector3d pos) {
    this->pos = pos;
}
void Camera::setTarget(Vector3d target) {
    this->target = target;
}
void Camera::setCameraUp(Vector3d cameraUp) {
    this->cameraUp = cameraUp;
}
void Camera::setCameraRight(Vector3d cameraRight) {
    this->cameraRight = cameraRight;
}

Matrix4d Camera::getCameraLookAt() {
    return cameraLookAt;
}

Matrix4d Camera::getCameraFinal() {
    return cameraFinal;
}