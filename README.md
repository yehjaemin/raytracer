# raytracer

### Low-Level Classes
- [x] vectors
- [x] points
- [x] normals
- [x] rays
  - REMEMBER TO TEMPLATE RAY CLASS
  - template <typename T> class Ray3
  - typedef Ray3<float> Ray3f
- [x] bounds
- [ ] transforms
  - inverse
  - points
  - vectors
    - simplified point transform
  - normals
    - transform in terms of tangent
  - rays
    - error bounding on origin
  - bounds
    - transform all corners and find new box OR
    - optimize using corner max / min components
  - transforms
    - T(p) = A(B(C(p)))
    - T = A * B * C
  - swapsHandedness
    - flip if determinant of upper left 3x3 submatrix is negative
- [ ] interactions

### Base Classes
- [ ] shapes
- [ ] cameras
- [ ] lights
- [ ] samplers
- [ ] integrators

### Features
- [ ] floating point error
- [ ] animated transforms

Remember to update CMakeLists.txt each time a new file is created.
