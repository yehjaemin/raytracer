#include "orthographic.h"

OrthographicCamera::OrthographicCamera(const Transform &cameraToWorld, const Bounds2f &screenWindow) : ProjectiveCamera(cameraToWorld, Transform(), screenWindow) {} // default transform is identity which is a simple orthographic transform

void OrthographicCamera::castRay(const Point2f &fp, Ray3f *ray) const {}
