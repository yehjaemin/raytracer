#include "sphere.h"

Sphere::Sphere(const Transform objectToWorld, float radius) : Shape(objectToWorld), radius(radius) {}

Sphere::Sphere(const Transform objectToWorld, const Transform worldToObject, float radius) : Shape(objectToWorld, worldToObject), radius(radius) {}

bool Sphere::isect(const Ray3f &ray) const {
    // check if ray origin is inside sphere
    Point3f o = objectToWorld(Point3f(0.f, 0.f, 0.f));
    if (distance(o, ray.o) <= radius)
        return true;

    // check if ray is in front of sphere
    Vector3f v = o - ray.o;
    if (dot(v, ray.d) < 0)
        return false;

    // check if distance from origin to ray is greater than radius
    Vector3f proj = normalize(ray.d) * dot(ray.d, v);
    Point3f po = ray.o + proj;
    float dist = distance(o, po);
    if (dist > radius)
        return false;
    return true;
}
