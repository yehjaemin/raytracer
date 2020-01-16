#include "orthographic.h"

OrthographicCamera::OrthographicCamera(const Transform &cameraToWorld, const Bounds2f &screenWindow) : ProjectiveCamera(cameraToWorld, Transform(), screenWindow) {} // default transform is identity which is a simple orthographic transform

void OrthographicCamera::initRay(const Point2f &sample, Ray3f *ray) const {
    Point3f pRaster = Point3f(pixel.x, pixel.y, 0);
    Point3f pCamera = rasterToCamera(pRaster);

    *ray = Ray3f(pCamera, Vector3f(0, 0, 1); // orthographic
    *ray = cameraToWorld(*ray);
}
