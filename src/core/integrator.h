#pragma once

class Integrator {
public:
    virtual ~Integrator();

    virtual void render(const Sphere &s) = 0;
};

class BasicIntegrator : public Integrator {
public:
    void render(const Sphere &s);

private:
    Camera camera;
};
