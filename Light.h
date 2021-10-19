//
// Created by Ludwig on 2021-10-07.
//

#ifndef RAY_TRACER_LIGHT_H
#define RAY_TRACER_LIGHT_H

#include "Eigen/Dense"

using namespace Eigen;

class Light {
private:
    Vector3f position;
public:
    explicit Light(const Vector3f &position);

    const Vector3f &getPosition() const;

    void setPosition(const Vector3f &position);
};


#endif //RAY_TRACER_LIGHT_H
