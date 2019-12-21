#pragma once

#include <cmath>
#include "geometry.h"

class Sphere {
public:
    Sphere() {}
    Sphere(const Point3f &p, const float &f) : o(p), r(f) {}

    bool isect(const Ray3f &ray) const;

    Point3f o; // origin
    float r; // radius
};
