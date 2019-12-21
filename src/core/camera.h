#pragma once

#include "geometry.h"
#include "sphere.h"
#include "transform.h"

class Camera {
public:
    Camera() {}
    Camera(const Transform &t) : cameraToWorld(t);

    virtual Vector3f castRay(const Ray3f &r, const Sphere &s) = 0;

    Transform cameraToWorld;
};

class BasicCamera : public Camera {
    Vector3f castRay(const Ray3f &r, const Sphere &s);

    float fov; // field of view
};
