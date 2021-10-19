//
// Created by Ludwig on 2021-10-07.
//

#include "Sphere.h"

Sphere::Sphere(const Vector3f &position, const Vector3f &color, float specular, float lambert, float ambient,
               float radius) : position(position), color(color), specular(specular), lambert(lambert), ambient(ambient),
                               radius(radius) {}

const Vector3f &Sphere::getPosition() const {
    return position;
}

void Sphere::setPosition(const Vector3f &position) {
    Sphere::position = position;
}

const Vector3f &Sphere::getColor() const {
    return color;
}

void Sphere::setColor(const Vector3f &color) {
    Sphere::color = color;
}

float Sphere::getSpecular() const {
    return specular;
}

void Sphere::setSpecular(float specular) {
    Sphere::specular = specular;
}

float Sphere::getLambert() const {
    return lambert;
}

void Sphere::setLambert(float lambert) {
    Sphere::lambert = lambert;
}

float Sphere::getAmbient() const {
    return ambient;
}

void Sphere::setAmbient(float ambient) {
    Sphere::ambient = ambient;
}

float Sphere::getRadius() const {
    return radius;
}

void Sphere::setRadius(float radius) {
    Sphere::radius = radius;
}

float Sphere::distance(const Vector3f &origin, const Vector3f &direction) {
    const auto eyeToCenter = position - origin;
    const auto v = eyeToCenter.dot(direction);
    const auto eoDot = eyeToCenter.dot(eyeToCenter);
    const auto discriminant = radius * radius - eoDot + v * v;

    if(discriminant < 0) {
        return std::numeric_limits<float>::infinity();
    } else {
        return v - std::sqrt(discriminant);
    }
}

Vector3f Sphere::normal(Vector3f &point) {
    return (point - position).normalized();
}
