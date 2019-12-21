#pragma once

#include "film.h"
#include "geometry.h"
#include "sphere.h"
#include "transform.h"

class Camera {
public:
    Camera() {}
    Camera(const Transform &t) : cameraToWorld(t) {}

    virtual Vector3f castRay(const Ray3f &r, const Sphere &s) = 0;

    Transform cameraToWorld;
};

class BasicCamera : public Camera {
public:
    BasicCamera() : fov(M_PI / 3.f) {
        cameraToWorld = Transform(translate(Vector3f(0.f, 0.f, 1.f)));
    }
    BasicCamera(const Film &film, const float &fov) : film(film), fov(fov) {}

    Vector3f castRay(const Ray3f &r, const Sphere &s);

    Film film;
    float fov; // field of view
};
