//
// Created by Ludwig on 2021-10-05.
//

#include "Scene.h"
#include <iostream>
#include <math.h>

using namespace Eigen;

bool Scene::isLightVisible(const Vector3f &point, const Light &light) {
    float closest;
    Sphere *intersecting;

    findIntersection(point,
                     (point - light.getPosition())
                             .normalized(),
                     intersecting, closest);

    return intersecting != nullptr && closest > -0.005;
}

void Scene::findIntersection(const Vector3f &origin, const Vector3f &direction, Sphere *&intersecting, float &closest) {
    intersecting = nullptr;
    closest = std::numeric_limits<float>::infinity();

    for (int i = 0; i < spheres.size(); i++) {
        auto &sphere = spheres[i];
        float distance = sphere.distance(origin, direction);
        if (distance < closest) {
            intersecting = &sphere;
            closest = distance;
        }
    }
}

Vector3f
Scene::surface(const Vector3f &origin, const Vector3f &direction, Sphere &sphere, Vector3f &point, Vector3f &normal,
               int depth) {
    auto &color = sphere.getColor();
    auto reflectedColor(Vector3f(0.0, 0.0, 0.0));
    float lambertAmount = 0;

    for (int i = 0; i < lights.size(); i++) {
        auto &lightPoint = lights[i];

        if (!isLightVisible(point, lightPoint)) {
            continue;
        }

        auto contribution = (lightPoint.getPosition() - point)
                .normalized()
                .dot(normal);
        if (contribution > 0) {
            lambertAmount += contribution;
        }
    }

    if (sphere.getSpecular() > 0) {
        const Vector3f a = normal * direction.dot(normal);
        const Vector3f reflect = a * 2 - direction;

        reflectedColor = trace(point, reflect, depth+1);
    }

    lambertAmount = min(1.f, lambertAmount);
    return reflectedColor * sphere.getSpecular()
           + color * lambertAmount * sphere.getLambert()
           + color * sphere.getAmbient();
}

Vector3f Scene::trace(const Vector3f &origin, const Vector3f &direction, int depth = 0) {
    if(depth > 3) {
        return {0, 0, 0};
    }

    float closest;
    Sphere *intersecting;

    findIntersection(origin, direction, intersecting, closest);

    if (intersecting == nullptr) {
        return {255, 255, 255};
    }

    Vector3f point = origin + closest * direction;
    Vector3f normal = intersecting->normal(point);
    return surface(origin, direction, *intersecting, point, normal, depth);
}

void Scene::render(Uint8 *pixels) {
    Vector3f eye = camera.getDirection() - camera.getPoint();
    eye.normalize();

    Vector3f vpRight = eye.cross(Vector3f(0, 1.0, 0)).normalized();
    Vector3f vpUp = vpRight.cross(eye).normalized();

    double halfWidth, halfHeight;
    camera.calculateDimensions(halfWidth, halfHeight);
    double width = halfWidth * 2, height = halfHeight * 2;
    double pixelWidth = width / (camera.getWidth() - 1), pixelHeight = height / (camera.getHeight() - 1);

    for (int x = 0; x < camera.getWidth(); x++) {
        for (int y = 0; y < camera.getHeight(); y++) {
            Vector3f xcomp = vpRight * (x * pixelWidth - halfWidth);
            Vector3f ycomp = vpUp * (y * pixelHeight - halfHeight);

            Vector3f rayDirection = eye + xcomp + ycomp;
            rayDirection.normalize();

            Vector3f color = trace(camera.getPoint(), rayDirection);

            int index = y * camera.getWidth() * 3 + x * 3;
            pixels[index] = (Uint8) color[0];
            pixels[index + 1] = (Uint8) color[1];
            pixels[index + 2] = (Uint8) color[2];
        }
    }
}

Scene::Scene(const Camera &camera, const vector<Sphere> &spheres, const vector<Light> &lights) : camera(camera),
                                                                                                 spheres(spheres),
                                                                                                 lights(lights) {}
