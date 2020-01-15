#include "integrator.h"

void BasicIntegrator::radiance(const Ray3f &ray, const Sphere &s) {
    return camera.castRay(ray, s);
}

void BasicIntegrator::render(const Sphere &s) {
    // define frame
    const int height = camera.film.height;
    const int width = camera.film.width;
    std::vector<Vector3f> frame(height * width);

    // cast rays from camera
    Point3f orig = camera.cameraToWorld(Point3f(0.f, 0.f, 0.f));
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            float t = std::tan(camera.fov / 2);
            float x =  (2 * (i + 0.5) / float(width) - 1) * t * width;
            float y = -(2 * (j + 0.5) / float(height)  - 1) * t * height;
            Vector3f dir = normalize(Vector3f(x, y, 1));
            Ray3f ray(orig, dir);
            frame[i * width + j] = radiance(ray, s);
        }
    }

    // save the frame to file
    camera.film.writeFrame(frame);
}
