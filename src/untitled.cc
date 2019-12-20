#include "untitled.h"

#include "geometry.h"

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

void render() {
    // declare framebuffer made of RGB values
    const int width = 1024;
    const int height = 768;
    std::vector<Vector3f> framebuffer(width * height);

    // R increases top to bottom
    // G increases left to right
    // B remains at 0
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            framebuffer[i * width + j] = Vector3f(i / float(height), j / float(width), std::abs(std::sin(i * width + j)));

    // save the framebuffer to file
    std::ofstream ofs;
    ofs.open("./out.ppm");
    ofs << "P6" << std::endl;
    ofs << width << " " << height << std::endl;
    ofs << "255" << std::endl;

    // constrain spectrum from 0.f to 255.f
    for (int i = 0; i < width * height; ++i)
        for (int j = 0; j < 3; ++j)
            ofs << char(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
    ofs.close();
}

int main() {
    render();
    return 0;
}
