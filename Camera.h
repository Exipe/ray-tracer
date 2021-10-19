//
// Created by Ludwig on 2021-10-05.
//

#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H
#include "Eigen/Dense"

using namespace Eigen;

class Camera {
private:
    int width;
    int height;
    int fieldOfView;
    Vector3f direction;
    Vector3f point;

public:
    Camera(int width, int height, int fieldOfView, const Vector3f &direction, const Vector3f &point);

    void calculateDimensions(double &halfWidth, double &halfHeight);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    int getFieldOfView() const;

    void setFieldOfView(int fieldOfView);

    const Vector3f &getDirection() const;

    void setDirection(const Vector3f &direction);

    const Vector3f &getPoint() const;

    void setPoint(const Vector3f &point);
};


#endif //RAY_TRACER_CAMERA_H
