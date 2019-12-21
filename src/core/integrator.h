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
    void render(const Sphere &s);

private:
    BasicCamera camera;
};
