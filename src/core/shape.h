#include "geometry.h"
#include "transform.h"

class Shape {
public:
    Shape() {}
    Shape(const Transform objectToWorld);
    Shape(const Transform objectToWorld, const Transform worldToObject);
    virtual ~Shape() {}

    virtual Bounds3f objectBound() const = 0;
    virtual Bounds3f worldBound() const;

    virtual bool isect(const Ray3f &ray) const = 0;

    const Transform objectToWorld, worldToObject;
};

