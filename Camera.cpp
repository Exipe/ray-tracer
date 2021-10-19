//
// Created by Ludwig on 2021-10-05.
//

#include "Camera.h"

int Camera::getWidth() const {
    return width;
}

void Camera::setWidth(int width) {
    Camera::width = width;
}

int Camera::getHeight() const {
    return height;
}

void Camera::setHeight(int height) {
    Camera::height = height;
}

int Camera::getFieldOfView() const {
    return fieldOfView;
}

void Camera::setFieldOfView(int fieldOfView) {
    Camera::fieldOfView = fieldOfView;
}

Camera::Camera(int width, int height, int fieldOfView, const Vector3f &direction, const Vector3f &point) : width(width),
                                                                                                           height(height),
                                                                                                           fieldOfView(
                                                                                                                  fieldOfView),
                                                                                                           direction(
                                                                                                                   direction),
                                                                                                           point(point) {}

const Vector3f &Camera::getDirection() const {
    return direction;
}

void Camera::setDirection(const Vector3f &direction) {
    Camera::direction = direction;
}

const Vector3f &Camera::getPoint() const {
    return point;
}

void Camera::setPoint(const Vector3f &point) {
    Camera::point = point;
}

void Camera::calculateDimensions(double &halfWidth, double &halfHeight) {
    double fovRadians = (M_PI * ((double) fieldOfView / 2)) / 180;
    double ratio = (double) height / width;
    halfWidth = tan(fovRadians);
    halfHeight = ratio * halfWidth;
}
