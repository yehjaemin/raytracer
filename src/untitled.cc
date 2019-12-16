#include <iostream>
#include "untitled.h"

#include "geometry.h"

int main(int argc, char *argv[]) {
    Point3f p1(0.f, 0.f, 0.f);
    Point3f p2(1.f, 1.f, 1.f);
    //Point3f p3 = p1 + p2;

    Vector3f v1(0.f, 0.f, 0.f);
    Vector3f v2(1.f, 1.f, 1.f);
    Vector3f v3 = v1 + v2;

    Normal3f n1(0.f, 0.f, 0.f);
    Normal3f n2(1.f, 1.f, 1.f);
    Normal3f n3 = n1 + n2;

    std::cout << "Hello World!" << std::endl;
    return 0;
}
