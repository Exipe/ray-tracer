//
// Created by Ludwig on 2021-10-05.
//

#ifndef RAY_TRACER_SCENE_H
#define RAY_TRACER_SCENE_H


#include "Camera.h"
#include "Sphere.h"
#include "Light.h"
#include <SDL.h>
#include <vector>

using namespace std;

class Scene {
public:
    Scene(const Camera &camera, const vector<Sphere> &spheres, const vector<Light> &lights);

    void render(Uint8 *pixels);

private:
    Vector3f trace(const Vector3f &origin, const Vector3f &direction, int depth);

    Vector3f
    surface(const Vector3f &origin, const Vector3f &direction, Sphere &sphere, Vector3f &point, Vector3f &normal,
            int depth);

    bool isLightVisible(const Vector3f &point, const Light &light);

    void findIntersection(const Vector3f &origin, const Vector3f &direction, Sphere *&intersecting, float &closest);

    Camera camera;

    vector<Sphere> spheres;
    vector<Light> lights;

};


#endif //RAY_TRACER_SCENE_H
