#ifndef HIT_H
#define HIT_H

#include <vecmath.h>

#include "ray.hpp"
#ifndef INF
#define INF 0x10000000
#endif
class Material;

class Hit
{
public:
  Hit()
  {
    material = nullptr;
    t = INF;
    r2 = 0.001;
    normal = color = Vector3f::ZERO;
    n = 0;
  }

  Hit(float _t, Material *m, const Vector3f &norm)
  {
    t = _t;
    material = m;
    normal = norm;
    r2 = 0.001;
    color = Vector3f::ZERO;
    n = 0;
  }

  float getT() const { return t; }

  Material *getMaterial() const { return material; }

  const Vector3f &getNormal() const { return normal; }

  void set(float _t, Material *_material, const Vector3f &_normal, const Vector3f &_color, const Vector3f &_point)
  {
    t = _t;
    material = _material;
    normal = _normal;
    color = _color;
    point = _point;
  }

  float t, r2;
  Material *material;
  Vector3f normal, color, dir, point;
  int n;
};

inline std::ostream &operator<<(std::ostream &os, const Hit &h)
{
  os << "Hit <" << h.getT() << ", " << h.getNormal() << ">";
  return os;
}
#endif // HIT_H
