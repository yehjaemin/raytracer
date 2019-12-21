#include "untitled.h"

#include "camera.h"
#include "geometry.h"
#include "sphere.h"

//int main(int argc, char *argv[]) {
//    Point3f p1(0.f, 0.f, 0.f);
//    Point3f p2(1.f, 1.f, 1.f);
//    //Point3f p3 = p1 + p2;
//
//    Vector3f v1(0.f, 0.f, 0.f);
//    Vector3f v2(1.f, 1.f, 1.f);
//    Vector3f v3 = v1 + v2;
//
//    Normal3f n1(0.f, 0.f, 0.f);
//    Normal3f n2(1.f, 1.f, 1.f);
//    Normal3f n3 = n1 + n2;
//
//    std::cout << "Hello World!" << std::endl;
//    return 0;
//}

// --------------------
// tiny ray tracer ver.
// --------------------

void render(const Sphere &s) {
    // declare frame and field of view angle
    const int width = 1024;
    const int height = 768;
    const float fov = M_PI / 3.f;
    std::vector<Vector3f> framebuffer(width * height);

    // cast rays from camera facing +z dir
    // camera is placed at (0, 0, 0)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            float x =  (2 * (i + 0.5) / float(height) - 1) * std::tan(fov / 2.f);
            float y = -(2 * (j + 0.5) / float(width)  - 1) * std::tan(fov / 2.f) * width / float(height);
            Vector3f dir = normalize(Vector3f(x, y, 1));
            Ray3f ray(Point3f(0.f, 0.f, 0.f), dir);
            framebuffer[i * width + j] = castRay(ray, s);
        }
    }

    // save the framebuffer to file
    std::ofstream ofs;
    ofs.open("./out.ppm");
    ofs << "P6" << std::endl;
    ofs << width << " " << height << std::endl;
    ofs << "255" << std::endl;
    for (int i = 0; i < width * height; ++i)
        for (int j = 0; j < 3; ++j)
            ofs << char(255 * framebuffer[i][j]);
    ofs.close();
}

int main() {
    Sphere s(Point3f(0.f, 0.f, 10.f), 2.f);
    render(s);
    return 0;
}
