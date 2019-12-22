#pragma once

#include <cmath>
#include <vector>
#include "camera.h"
#include "sphere.h"

class Integrator {
public:
    virtual void render(const Sphere &s) = 0;
};

class BasicIntegrator : public Integrator {
public:
//    Vector3f radiance(const Ray3f &ray, const Sphere &s);

    void render(const Sphere &s) {}

private:
//    OrthographicCamera camera;
};
