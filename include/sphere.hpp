#ifndef SPHERE_H
#define SPHERE_H

#include <vecmath.h>

#include "object3d.hpp"
#include <cmath>

class Sphere : public Object3D
{
public:
  Sphere(const Vector3f &center, float radius, Material *material)
      : Object3D(material), cen(center), radius(radius) {}
  ~Sphere() override = default;

  bool intersect(const Ray &r, Hit &h) override
  {
    Vector3f origin(r.getOrigin()), dir(r.getDirection());
    Vector3f OC(cen - origin);
    float b = -Vector3f::dot(OC, dir);
    float c = OC.squaredLength() - radius * radius;
    float delta = b * b - c;
    if (delta <= 0)
      return false;
    float sqrt_delta = sqrtf(delta);
    float t1 = (-b - sqrt_delta), t2 = (-b + sqrt_delta);
    float t;
    if (t1 <= h.getT() && t1 >= 0)
      t = t1;
    else if (t2 <= h.getT() && t2 >= 0)
      t = t2;
    else
      return false;
    Vector3f OP(origin + dir * t - cen);
    Vector3f normal = OP.normalized();
    float u = 0.5 + atan2(normal.x(), normal.z()) / (2 * M_PI),
          v = 0.5 - asin(normal.y()) / M_PI;
    h.set(t, material, getNormal(normal, OP, u, v), material->getColor(u, v),
          origin + dir * t);
    return true;
  }

  Vector3f getNormal(const Vector3f &n, const Vector3f &p, float u, float v)
  {
    Vector2f grad(0);
    float f = material->bump.getDisturb(u, v, grad);
    if (fabs(f) < FLT_EPSILON)
      return n;
    float phi = u * 2 * M_PI, theta = M_PI - v * M_PI;
    Vector3f pu(-p.z(), 0, p.x()),
        pv(p.y() * cos(phi), -radius * sin(theta), p.y() * sin(phi));
    if (pu.squaredLength() < FLT_EPSILON)
      return n;
    return Vector3f::cross(pu + n * grad[0] / (2 * M_PI), pv + n * grad[1] / M_PI).normalized();
  }

  Vector3f min() const override { return cen - Vector3f(radius); }
  Vector3f max() const override { return cen + Vector3f(radius); }
  Vector3f center() const override { return cen; }
  vector<Object3D *> getFaces() override { return {(Object3D *)this}; }

protected:
  Vector3f cen;
  float radius;
};

#endif
