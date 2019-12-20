# raytracer

### Low-Level Classes
- [x] vectors
- [x] points
- [x] normals
- [x] rays
- [x] bounds
- [x] transforms - the columns of a transformation matrix give the effect of the transformation on the basis of a coordinate system
  - translate
  - scale
  - rotate
  - inverse
  - lookAt
- [ ] interactions
  - do this after looking at shapes
  - public variables - Point3f p, float time, Vector3f wo, Normal3f n
  - public methods - constructors, isSurfaceInteraction(), isMediumInteraction(), spawnRay(), spawnRayTo()
  - class SurfaceInteraction : public Interaction {...};

### Base Classes
- [ ] shapes
  - Sphere
- [ ] cameras
  - public variables - Transform cameraToWorld, Film film
- [ ] lights
  - this might not be necessary
  - do this after spectrum
- [ ] samplers
- [ ] integrators
  - SamplerIntegrator

## Main Rendering Loop
- [ ] scene
  - create a test scene and directly feed it into the rendering loop
  - Scene <-- simplify this
- [ ] film
- [ ] spectrum
  - RGBSpectrum

### Features
- [ ] parallel
  - parallelFor
- [ ] floating point error
- [ ] animated transforms

Remember to update CMakeLists.txt each time a new file is created.
