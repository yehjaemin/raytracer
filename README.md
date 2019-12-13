# raytracer

### Low-Level Classes
- [x] vectors
- [x] points
- [ ] normals
  - normalize
  - reorient
  - explicit vector conversion
  - dot and cross products
- [x] rays
- [x] bounds
- [ ] transforms
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
    - flip if determinant of upper left 3x3 submatrix id negative

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
