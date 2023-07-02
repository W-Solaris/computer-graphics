#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vecmath.h>

#include <cfloat>
#include <cmath>
#include <iostream>

#include "object3d.hpp"
using namespace std;

class Triangle : public Object3D
{
public:
  Triangle() = delete;

  Triangle(const Vector3f &a, const Vector3f &b, const Vector3f &c, Material *m)
      : Object3D(m), a(a), b(b), c(c), an(Vector3f::ZERO), bn(Vector3f::ZERO),
        cn(Vector3f::ZERO)
  {
    normal = Vector3f::cross((b - a), (c - a)).normalized();
    d = Vector3f::dot(normal, a);
    range[0] = minE(minE(a, b), c);
    range[1] = maxE(maxE(a, b), c);
    cen = (a + b + c) / 3;
    nSet = false;
    tSet = false;
  }

  bool intersect(const Ray &r, Hit &h) override
  {
    Vector3f o(r.getOrigin()), dir(r.getDirection());
    Vector3f a_b = b - a;
    Vector3f a_c = c - a;
    Vector3f pvec = Vector3f::cross(dir, a_c);
    float det = Vector3f::dot(a_b, pvec);
    if (fabs(det) < FLT_EPSILON)
      return false;
    float invDet = 1 / det;
    Vector3f tvec = o - a;
    float u = Vector3f::dot(tvec, pvec) * invDet;
    if (u < 0 || u > 1)
      return false;
    Vector3f qvec = Vector3f::cross(tvec, a_b);
    float v = Vector3f::dot(dir, qvec) * invDet;
    if (v < 0 || u + v > 1)
      return false;
    float t = Vector3f::dot(a_c, qvec) * invDet;
    if (t <= 0 || t > h.getT())
      return false;
    Vector3f p(o + dir * t);
    getUV(p, u, v);
    h.set(t, material, getNorm(p), material->getColor(u, v), p);
    return true;
  }

  void setVNorm(const Vector3f &anorm, const Vector3f &bnorm,
                const Vector3f &cnorm)
  {
    an = anorm;
    bn = bnorm;
    cn = cnorm;
    nSet = true;
  }

  Vector3f min() const override { return range[0]; }
  Vector3f max() const override { return range[1]; }
  Vector3f center() const override { return cen; }
  vector<Object3D *> getFaces() override { return {(Object3D *)this}; }
  Vector3f normal;
  Vector3f a, b, c, cen;
  Vector2f at, bt, ct;
  Vector3f an, bn, cn;
  Vector3f range[2];
  float d;
  bool nSet = false;
  bool tSet = false;

protected:
  bool inTriangle(const Vector3f &p)
  {
    float va = Vector3f::dot(Vector3f::cross((b - p), (c - p)), normal),
          vb = Vector3f::dot(Vector3f::cross((c - p), (a - p)), normal),
          vc = Vector3f::dot(Vector3f::cross((a - p), (b - p)), normal);
    return (va >= 0 && vb >= 0 && vc >= 0);
  }

  Vector3f getNorm(const Vector3f &p)
  {
    if (!nSet)
      return normal;
    Vector3f va = (a - p), vb = (b - p), vc = (c - p);
    float ra = Vector3f::cross(vb, vc).length(),
          rb = Vector3f::cross(vc, va).length(),
          rc = Vector3f::cross(va, vb).length();
    return (ra * an + rb * bn + rc * cn).normalized();
  }

  void getUV(const Vector3f &p, float &u, float &v)
  {
    if (!tSet)
      return;
    Vector3f va = (a - p), vb = (b - p), vc = (c - p);
    float ra = Vector3f::cross(vb, vc).length(),
          rb = Vector3f::cross(vc, va).length(),
          rc = Vector3f::cross(va, vb).length();
    Vector2f uv = (ra * at + rb * bt + rc * ct) / (ra + rb + rc);
    u = uv.x();
    v = uv.y();
  }
};

#endif // TRIANGLE_H
