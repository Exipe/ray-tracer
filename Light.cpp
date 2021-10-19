//
// Created by Ludwig on 2021-10-07.
//

#include "Light.h"

const Vector3f &Light::getPosition() const {
    return position;
}

void Light::setPosition(const Vector3f &position) {
    Light::position = position;
}

Light::Light(const Vector3f &position) : position(position) {}
