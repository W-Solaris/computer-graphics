#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "hit.hpp"
#include "material.hpp"
#include "ray.hpp"
#include <vector>

// Base class for all 3d entities.
using std::vector;
class Object3D
{
public:
  Object3D() : material(nullptr) {}

  virtual ~Object3D() = default;

  explicit Object3D(Material *material) { this->material = material; }

  virtual bool intersect(const Ray &r, Hit &h) = 0;
  virtual vector<Object3D *> getFaces() { return {this}; }
  virtual Vector3f min() const { return Vector3f(); }
  virtual Vector3f max() const { return Vector3f(); }
  virtual Vector3f center() const { return Vector3f(); }
  Material *material;
};

#endif
