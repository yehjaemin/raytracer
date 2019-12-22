#include "untitled.h"

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
void handler(int sig) {
    void *array[10];
    size_t size;

    size = backtrace(array, 20);
    std::cerr << "Error: signal " << sig << std::endl;
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}

int main() {
    signal(SIGSEGV, handler);
    OrthographicCamera camera(Transform(), Bounds2f(Point2f(-100.f, -100.f),                                                    Point2f(100.f, 100.f)));
    BasicIntegrator b(camera);
    Sphere s(translate(Vector3f(-5.f, 5.f, 20.f)), 1.f);
    b.render(s);
    return 0;
}
