#ifndef CURVE_HPP
#define CURVE_HPP

#include <vecmath.h>

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include "object3d.hpp"
using namespace std;
struct CurvePoint
{
  Vector3f v;
  Vector3f tan;
};

class Curve
{
protected:
  std::vector<Vector3f> controls;

public:
  explicit Curve(std::vector<Vector3f> points) : controls(std::move(points))
  {
    ymin = INF;
    ymax = -INF;
    radius = 0;
    for (auto pt : controls)
    {
      // used for bounding box
      ymin = min(pt.y(), ymin);
      ymax = max(pt.y(), ymax);
      radius = max(radius, fabs(pt.x()));
      radius = max(radius, fabs(pt.z()));
    }
  }

  std::vector<Vector3f> &getControls() { return controls; }

  CurvePoint getPoint(float target)
  {
    CurvePoint pt;
    int position = upper_bound(t.begin(), t.end(), target) - t.begin() - 1; // 第一个大于 target 的元素位置
    vector<float> crvpoints(k + 2, 0), tans(k + 1, 1);
    crvpoints[k] = 1;
    for (int p = 1; p <= k; ++p)
    {
      for (int j = k - p; j < k + 1; ++j)
      {
        int i = j + position - k;
        float weight_1, tan_w1, weight_2, tan_w2;
        if (tpad[i + p] == tpad[i])
        {
          weight_1 = target;
          tan_w1 = 1;
        }
        else
        {
          weight_1 = (target - tpad[i]) / (tpad[i + p] - tpad[i]);
          tan_w1 = 1.0 / (tpad[i + p] - tpad[i]);
        }
        if (tpad[i + p + 1] == tpad[i + 1])
        {
          weight_2 = 1 - target;
          tan_w2 = -1;
        }
        else
        {
          weight_2 = (tpad[i + p + 1] - target) / (tpad[i + p + 1] - tpad[i + 1]);
          tan_w2 = -1 / (tpad[i + p + 1] - tpad[i + 1]);
        }
        if (p == k)
          tans[j] = (tan_w1 * crvpoints[j] + tan_w2 * crvpoints[j + 1]) * p;
        crvpoints[j] = weight_1 * crvpoints[j] + weight_2 * crvpoints[j + 1];
      }
    }
    crvpoints.pop_back();
    int lsk = k - position, rsk = position + 1 - n;
    if (lsk > 0)
    {
      for (int i = lsk; i < int(crvpoints.size()); ++i)
      {
        crvpoints[i - lsk] = crvpoints[i];
        tans[i - lsk] = tans[i];
      }
      crvpoints.resize(crvpoints.size() - lsk);
      tans.resize(tans.size() - lsk);
      lsk = 0;
    }
    if (rsk > 0)
    {
      if (rsk < int(crvpoints.size()))
      {
        crvpoints.resize(crvpoints.size() - rsk);
        tans.resize(tans.size() - rsk);
      }
      else
      {
        crvpoints.clear();
        tans.clear();
      }
    }
    for (int j = 0; j < int(crvpoints.size()); ++j)
    {
      pt.v += controls[-lsk + j] * crvpoints[j];
      pt.tan += controls[-lsk + j] * tans[j];
    }
    return pt;
  }

  void pad()
  {
    int tSize = t.size();
    tpad.resize(tSize + k);
    for (int i = 0; i < tSize; ++i)
      tpad[i] = t[i];
    for (int i = 0; i < k; ++i)
      tpad[i + tSize] = t.back();
  }

  int n, k;
  std::vector<float> t;
  std::vector<float> tpad;
  float ymin, ymax, radius;
  float range[2];
};

class BezierCurve : public Curve
{
public:
  explicit BezierCurve(const std::vector<Vector3f> &points) : Curve(points)
  {
    if (points.size() < 4 || points.size() % 3 != 1)
    {
      printf("Number of control points of BezierCurve must be 3n+1!\n");
      exit(0);
    }
    n = controls.size();
    k = n - 1;
    range[0] = 0;
    range[1] = 1;
    t.resize(2 * n);
    for (int i = 0; i < n; ++i)
    {
      t[i] = 0;
      t[i + n] = 1;
    }
    pad();
  }
};

#endif // CURVE_HPP
