#include "shape.h"

Shape::Shape(const Transform objectToWorld) : objectToWorld(objectToWorld), worldToObject(inverse(objectToWorld)) {}

Shape::Shape(const Transform objectToWorld, const Transform worldToObject) : objectToWorld(objectToWorld), worldToObject(worldToObject) {}

Bounds3f Shape::worldBound() const {
    return objectToWorld(objectBound());
}
