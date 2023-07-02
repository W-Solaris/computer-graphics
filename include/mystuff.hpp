#ifndef MYSTUFF_H
#define MYSTUFF_H
#include <cmath>
#include <cstdlib>
#include <random>
#include <vecmath.h>
using namespace std;

#define PI 3.1415926536

static random_device rd;
static mt19937 mt(rd());
static uniform_real_distribution<float> dist1(-1, 1);

static float Rand1() { return dist1(mt); }

static uniform_real_distribution<float> dist2(0, 1);

static float Rand2() { return dist2(mt); }

inline void orthogonalize(const Vector3f &v1, Vector3f &v2, Vector3f &v3)
{
  if (abs(v1.x()) > abs(v1.y()))
  {
    float len = 1.f / sqrtf(v1.x() * v1.x() + v1.z() * v1.z());
    v2 = Vector3f(-v1.z() * len, 0.0f, v1.x() * len);
  }
  else
  {
    float len = 1.0f / sqrtf(v1.y() * v1.y() + v1.z() * v1.z());
    v2 = Vector3f(0.0f, v1.z() * len, -v1.y() * len);
  }
  v3 = Vector3f::cross(v1, v2);
}

inline Vector3f cosineHemisphere(float u1, float u2)
{
  const float r = sqrt(u1);
  const float theta = 2 * PI * u2;

  const float x = r * cos(theta);
  const float y = r * sin(theta);

  return Vector3f(x, y, sqrt(std::max(0.0f, 1 - u1)));
}
#endif
