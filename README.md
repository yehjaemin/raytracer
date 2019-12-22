# raytracer
- integrator is broken while working on cameras
- film uses shared_ptr because unique_ptr and * crash make

### Low-Level Classes
- [x] vectors
- [x] points
- [x] normals
- [x] rays
- [x] bounds
- [x] transforms --> translate, scale, rotate, inverse, lookAt
- [ ] interactions
- [ ] spectrum
- [x] film

### Base Classes
- [x] shapes --> spheres
- [ ] materials
- [x] cameras
- [ ] lights
- [ ] samplers
- [x] integrators

## Main Rendering Loop
- [ ] radiance computation
- [ ] monte carlo integration

### Features
- [ ] parallel
  - parallelFor
- [ ] floating point error
- [ ] animated transforms

Remember to update CMakeLists.txt each time a new file is created.
