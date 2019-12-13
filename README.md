# raytracer

- [x] vectors
- [x] points
- [ ] normals
  - normalize
  - reorient
  - explicit Vector3 conversion
  - dot and cross product
    - can’t cross normals with each other
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
    - transform corners and find box OR
    - optimize using corner max / min components
  - transforms
    - T(p) = A(B(C(p)))
    - T = A * B * C
  - swapsHandedness
    - determinant of upper left 3x3 sub matrix is negative

- [ ] shapes
- [ ] lights
- [ ] samplers
- [ ] integrators

Remember to update CMakeLists.txt each time a new file is created.
