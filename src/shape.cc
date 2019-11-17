#include "shape.h"

Shape::Shape(const Transformation *ObjectToWorld, const Transformation *WorldToObject)
    : ObjectToWorld(ObjectToWorld), WorldToObject(WorldToObject) {};

Shape::~Shape() {}

Shape::getWorldBound() {
    return (*ObjectToWorld)(ObjectBound());
}
