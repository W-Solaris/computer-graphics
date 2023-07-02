#ifndef AABB_H
#define AABB_H
#include "ray.hpp"
#include <vecmath.h>
#include <vector>
using std::vector;
#ifndef INF
#define INF 0x10000000
#endif
class AABB
{
public:
  AABB()
  {
    range[0] = Vector3f(INF);
    range[1] = Vector3f(-INF);
  }

  AABB(const Vector3f &min, const Vector3f &max)
  {
    range[0] = min;
    range[1] = max;
  }

  void set(const Vector3f &lo, const Vector3f &hi)
  {
    range[0] = lo;
    range[1] = hi;
  }

  void updateRange(const Vector3f &vec)
  {
    for (int i = 0; i < 3; ++i)
    {
      range[0][i] = range[0][i] < vec[i] ? range[0][i] : vec[i];
      range[1][i] = range[1][i] < vec[i] ? vec[i] : range[1][i];
    }
  }

  bool intersect(const Ray &r, float &t_min)
  {
    Vector3f origin(r.getOrigin()), invdir(1 / r.getDirection());
    vector<int> sgn = {invdir.x() < 0, invdir.y() < 0, invdir.z() < 0};
    t_min = INF;
    float tmin, tmax, tymin, tymax, tzmin, tzmax;
    tmin = (range[sgn[0]].x() - origin.x()) * invdir.x();
    tmax = (range[1 - sgn[0]].x() - origin.x()) * invdir.x();
    tymin = (range[sgn[1]].y() - origin.y()) * invdir.y();
    tymax = (range[1 - sgn[1]].y() - origin.y()) * invdir.y();
    if ((tmin > tymax) || (tymin > tmax))
      return false;
    if (tymin > tmin)
      tmin = tymin;
    if (tymax < tmax)
      tmax = tymax;
    tzmin = (range[sgn[2]].z() - origin.z()) * invdir.z();
    tzmax = (range[1 - sgn[2]].z() - origin.z()) * invdir.z();
    if ((tmin > tzmax) || (tzmin > tmax))
      return false;
    if (tzmin > tmin)
      tmin = tzmin;
    if (tzmax < tmax)
      tmax = tzmax;
    t_min = tmin;
    return true;
  }
  Vector3f range[2];
};

#endif // !AABB_H