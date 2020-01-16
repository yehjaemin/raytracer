# raytracer
- integrator is broken while working on cameras
- move castRay() into radiance() and delete castRay()
- add makeRay() to Camera
  - transforms pixels into vectors pointing into raster space
- move basic integrator into its own file and directory
- film uses shared_ptr because camera gets copied into integrator
  - pointer to camera could be a work around for this

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
