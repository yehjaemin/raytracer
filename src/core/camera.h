#pragma once

#include "film.h"
#include "geometry.h"
#include "transform.h"

class Camera {
public:
    Camera(const Transform &cameraToWorld) : cameraToWorld(cameraToWorld) {}

    virtual void initRay(const Point2f &sample, Ray3f *ray) const = 0;

    Transform cameraToWorld;
    Film film;
};

class ProjectiveCamera : public Camera {
public:
    ProjectiveCamera(const Transform &cameraToWorld, const Transform &cameraToScreen, const Bounds2f &screenWindow);

    float fov = 3.14;

protected:
    // screen is the visible film plane
    // raster is screen scaled to resolution
    Transform screenToRaster, rasterToScreen;
    Transform cameraToScreen, rasterToCamera;
};
