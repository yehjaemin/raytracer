#pragma once

#include <cmath>
#include <vector>
#include "geometry.h"
#include "orthographic.h"
#include "sphere.h"
#include "transform.h"

class Integrator {
public:
    virtual ~Integrator() {}

    virtual void render(const Sphere &s) = 0;
};

class BasicIntegrator : public Integrator {
public:
    BasicIntegrator(OrthographicCamera cam) {
        camera = &cam;
    }
    Vector3f radiance(const Ray3f &ray, const Sphere &s);

    void render(const Sphere &s);

private:
    OrthographicCamera* camera;
};
