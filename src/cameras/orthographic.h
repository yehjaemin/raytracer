#pragma once

#include "camera.h"

class OrthographicCamera : public ProjectiveCamera {
public:
    OrthographicCamera(const Transform &cameraToWorld, const Bounds2f &screenWindow);

    void castRay(const Point2f &fp, Ray3f *ray) const;
};
