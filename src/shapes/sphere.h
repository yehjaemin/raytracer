#pragma once

#include <cmath>
#include "geometry.h"
#include "shape.h"

class Sphere : public Shape {
public:
    Sphere() : Shape(), radius(0.f) {}
    Sphere(float radius) : Shape(), radius(radius) {}
    Sphere(const Transform objectToWorld, float radius);
    Sphere(const Transform objectToWorld, const Transform worldToObject, float radius);

    Bounds3f objectBound() const {
        return Bounds3f(Point3f(-radius, -radius, -radius),
                        Point3f( radius,  radius,  radius));
    }

    bool isect(const Ray3f &ray) const;

    float radius;
};
