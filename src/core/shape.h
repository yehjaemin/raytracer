#include "geometry.h"

class Shape {
public:
    Shape(const Transform *ObjectToWorld, const Transform *WorldToObject);
    virtual ~Shape();
    virtual Bounds3f getObjectBound() const = 0;
    virtual Bounds3f getWorldBound() const;

    const Transform *ObjectToWorld, *WorldToObject;
};
