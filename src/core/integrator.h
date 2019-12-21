#pragma once

class Integrator {
    ~Integrator();

    virtual void render(const Sphere &s) = 0;
};
