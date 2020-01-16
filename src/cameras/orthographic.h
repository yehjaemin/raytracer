#pragma once

#include "camera.h"

class OrthographicCamera : public ProjectiveCamera {
public:
    OrthographicCamera(const Transform &cameraToWorld, const Bounds2f &screenWindow);

    void initRay(const Point2f &sample, Ray3f *ray) const;
};
