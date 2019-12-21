#pragma once

#include "geometry.h"
#include "sphere.h"

Vector3f castRay(const Ray3f &r, const Sphere &s) {
    // sphere is blue
    // background is white
    if (s.isect(r))
        return Vector3f(0.f, 0.f, 1.f);
    return Vector3f(1.f, 1.f, 1.f);
}
