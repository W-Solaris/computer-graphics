#ifndef MESH_H
#define MESH_H
#include <vector>

#include "Vector2f.h"
#include "Vector3f.h"
#include "AABB.hpp"
#include "object3d.hpp"
#include "kdtree.hpp"
#include "ray.hpp"
#include "triangle.hpp"

class Mesh : public Object3D
{

public:
  Mesh(const char *filename, Material *m);

  ~Mesh();

  std::vector<std::string> split(std::string str, std::string pattern);

  struct TriangleIndex
  {
    TriangleIndex()
    {
      x[0] = -1;
      x[1] = -1;
      x[2] = -1;
    }
    int &operator[](const int i) { return x[i]; }
    // By Computer Graphics convention, counterclockwise winding is front face
    int x[3]{};
    bool valid() { return x[0] != -1 && x[1] != -1 && x[2] != -1; }
  };

  vector<Object3D *> triangles;
  bool intersect(const Ray &r, Hit &h) override
  {
    float tb;
    if (!aabb.intersect(r, tb))
      return false;
    if (tb > h.getT())
      return false;
    // kd-tree search
    bool flag = kdTree->intersect(r, h);
    return flag;
  };
  Vector3f min() const override { return aabb.range[0]; }
  Vector3f max() const override { return aabb.range[1]; }
  Vector3f center() const override
  {
    return (aabb.range[0] + aabb.range[1]) / 2;
  }
  vector<Object3D *> getFaces() override { return {(Object3D *)this}; }

private:
  AABB aabb;
  KDTree *kdTree;
};

#endif
