#include "camera.h"

ProjectiveCamera::ProjectiveCamera(const Transform &cameraToWorld, const Transform &cameraToScreen, const Bounds2f &screenWindow) : Camera(cameraToWorld), cameraToScreen(cameraToScreen) {
    // (0, 0) --> upper left corner of screen window
    Transform a = translate(Vector3f(-screenWindow.pMin.x, -screenWindow.pMax.y, 0));
    // (1, 1) --> bottom right corner of screen window
    Transform b = scale(Vector3f(1 / (screenWindow.pMax.x - screenWindow.pMin.x), 1 / (screenWindow.pMin.y - screenWindow.pMax.y), 1));
    // scale to resolution
    Transform c = scale(Vector3f(1280.f, 720.f, 1.f));
    screenToRaster = c(b(a));

    // inverse of matrix product
    Transform ainv = inverse(a);
    Transform binv = inverse(b);
    Transform cinv = inverse(c);
    rasterToScreen = a;

    // raster to screen to camera
    Transform screenToCamera;
    rasterToCamera = screenToCamera(rasterToScreen);
}
