#include "sphere.h"

bool Sphere::isect(const Ray3f &ray) const {
    // check if ray origin is inside sphere
    if (distance(o, ray.o) <= r)
        return true;

    // check if ray is in front of sphere
    Vector3f v = o - ray.o;
    if (dot(v, ray.d) < 0)
        return false;

    // check if distance from origin to ray is greater than radius
    Vector3f proj = normalize(ray.d) * dot(ray.d, v);
    Point3f po = ray.o + proj;
    float dist = distance(o, po);
    if (dist > r)
        return false;
    return true;
}
