#include "integrator.h"

void BasicIntegrator::render(const Sphere &s) {
    // define frame
    const int height = camera.film.height;
    const int width = camera.film.width;
    std::vector<Vector3f> frame(height * width);

    // cast rays from camera
    Point3f orig = camera.cameraToWorld(Point3f(0.f, 0.f, 0.f));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            float t = std::tan(camera.fov / 2);
            float x =  (2 * (i + 0.5) / float(height) - 1) * t;
            float y = -(2 * (j + 0.5) / float(width)  - 1) * t * width / float(height);
            Vector3f dir = normalize(Vector3f(x, y, 1));
            Ray3f ray(orig, dir);
            frame[i * width + j] = camera.castRay(ray, s);
        }
    }

    // save the frame to file
    camera.film.writeFrame(frame);
}
