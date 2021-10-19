//
// Created by Ludwig on 2021-10-07.
//

#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H

#include "Eigen/Dense"

using namespace Eigen;

class Sphere {

private:
    Vector3f position;
    Vector3f color;

    float specular;
    float lambert;
    float ambient;
    float radius;

public:
    Sphere(const Vector3f &position, const Vector3f &color, float specular, float lambert, float ambient, float radius);

    const Vector3f &getPosition() const;

    void setPosition(const Vector3f &position);

    const Vector3f &getColor() const;

    void setColor(const Vector3f &color);

    float getSpecular() const;

    void setSpecular(float specular);

    float getLambert() const;

    void setLambert(float lambert);

    float getAmbient() const;

    void setAmbient(float ambient);

    float getRadius() const;

    void setRadius(float radius);

    float distance(const Vector3f &origin, const Vector3f &direction);
    Vector3f normal(Vector3f &point);
};


#endif //RAY_TRACER_SPHERE_H
