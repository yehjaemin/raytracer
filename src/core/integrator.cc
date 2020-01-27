#include "integrator.h"

Vector3f BasicIntegrator::radiance(const Ray3f &ray, const Sphere &s) {
    if (s.isect(ray))
        return Vector3f(1.f, 1.f, 1.f);
    return Vector3f(0.f, 1.f, 1.f);
}

void BasicIntegrator::render(const Sphere &s) {
    // define frame
    const int height = camera->film.height;
    const int width = camera->film.width;
    std::vector<Vector3f> frame(height * width);

    // cast rays from camera
    Point3f orig = camera->cameraToWorld(Point3f(0.f, 0.f, 0.f));
    for (int i = 0; i < width; ++i) {
       for (int j = 0; j < height; ++j) {
            float t = std::tan(camera->fov / 2);
            float x =  (2 * (i + 0.5) / float(width) - 1) * t * width;
            float y = -(2 * (j + 0.5) / float(height)  - 1) * t * height;
            Ray3f ray;
            camera->initRay(Point2f(x, y), &ray);
            frame[i * width + j] = radiance(ray, s);
        }
    }

    // save the frame to file
    camera->film.writeFrame(frame);
}
