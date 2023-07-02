#ifndef REVSURFACE_HPP
#define REVSURFACE_HPP
#include <tuple>

#include "AABB.hpp"
#include "curve.hpp"
#include "object3d.hpp"
#include "triangle.hpp"
const int resolution = 10;
const int NEWTON_STEPS = 20;
const float NEWTON_EPS = 1e-4;
class RevSurface : public Object3D
{
  Curve *pCurve;
  AABB aabb;
  typedef std::tuple<unsigned, unsigned, unsigned> Tup3u;
  std::vector<Triangle> triangles;

public:
  RevSurface(Curve *pCurve, Material *material)
      : Object3D(material), pCurve(pCurve)
  {
    for (const auto &crvpoint : pCurve->getControls())
    {
      if (crvpoint.z() != 0.0)
      {
        printf("Profile of revSurface must be flat on xy plane.\n");
        exit(0);
      }
    }
    aabb.set(Vector3f(-pCurve->radius, pCurve->ymin - 2, -pCurve->radius),
             Vector3f(pCurve->radius, pCurve->ymax + 2, pCurve->radius));
  }

  ~RevSurface() override { delete pCurve; }
  bool intersect(const Ray &r, Hit &h) override
  {
    float t, theta, target;
    if (!aabb.intersect(r, t) || t > h.getT())
      return false;
    getUV(r, t, theta, target); // 粗略估计交点，用牛顿迭代精确化
    Vector3f normal, point;
    if (!newton(r, t, theta, target, normal, point))
      return false;

    if (!isnormal(target) || !isnormal(theta) || !isnormal(t))
      return false;
    if (t < 0 || target < pCurve->range[0] || target > pCurve->range[1] || t > h.getT())
      return false;
    h.set(t, material, normal.normalized(),
          material->getColor(theta / (2 * M_PI), target), point);
    return true;
  }

  bool newton(const Ray &r, float &t, float &theta, float &target,
              Vector3f &normal, Vector3f &point)
  {
    Vector3f dtarget, dtheta;
    for (int i = 0; i < NEWTON_STEPS; ++i)
    {
      if (theta < 0.0)
        theta += 2 * M_PI;
      if (theta >= 2 * M_PI)
        theta = fmod(theta, 2 * M_PI);
      if (target >= 1)
        target = 1.0 - FLT_EPSILON;
      if (target <= 0)
        target = FLT_EPSILON;

      point = getPoint(theta, target, dtheta, dtarget);

      Vector3f f = r.origin + r.direction * t - point;
      float dist2 = f.squaredLength();
      if (dist2 < NEWTON_EPS)
        return true;

      normal = Vector3f::cross(dtarget, dtheta);
      float D = Vector3f::dot(r.direction, normal);
      t -= Vector3f::dot(dtarget, Vector3f::cross(dtheta, f)) / D;
      target -= Vector3f::dot(r.direction, Vector3f::cross(dtheta, f)) / D;
      theta += Vector3f::dot(r.direction, Vector3f::cross(dtarget, f)) / D;
    }
    return false;
  }

  Vector3f getPoint(const float &theta, const float &target, Vector3f &dtheta,
                    Vector3f &dtarget)
  {
    Vector3f point;
    Quat4f rot;
    rot.setAxisAngle(theta, Vector3f::UP);
    Matrix3f rotMat = Matrix3f::rotation(rot);
    CurvePoint crvpoint = pCurve->getPoint(target);
    point = rotMat * crvpoint.v;
    dtarget = rotMat * crvpoint.tan;
    dtheta = Vector3f(-crvpoint.v.x() * sin(theta), 0, -crvpoint.v.x() * cos(theta));
    return point;
  }

  void getUV(const Ray &r, const float &t, float &theta, float &target)
  {
    Vector3f point(r.origin + r.direction * t);
    theta = atan2(-point.z(), point.x()) + M_PI;
    target = (pCurve->ymax - point.y()) / (pCurve->ymax - pCurve->ymin);
  }

  Vector3f min() const override { return aabb.range[0]; }
  Vector3f max() const override { return aabb.range[1]; }
  Vector3f center() const override
  {
    return (aabb.range[0] + aabb.range[1]) / 2;
  }
  vector<Object3D *> getFaces() override { return {(Object3D *)this}; }
};

#endif // REVSURFACE_HPP
