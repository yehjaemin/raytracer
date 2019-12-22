#pragma once

#include "film.h"
#include "geometry.h"
#include "transform.h"

class Camera {
public:
    Camera(const Transform &cameraToWorld) : cameraToWorld(cameraToWorld) {}

    virtual void castRay(const Point2f &fp, Ray3f *ray) = 0;

    Transform cameraToWorld;
    Film film;
};

class ProjectiveCamera : public Camera {
public:
    ProjectiveCamera(const Transform &cameraToWorld, const Transform &cameraToScreen, const Bounds2f &screenWindow);

protected:
    // screen is the visible film plane
    // raster is screen scaled to resolution
    Transform screenToRaster, rasterToScreen;
    Transform cameraToScreen, rasterToCamera;
};
