#ifndef GROUP_H
#define GROUP_H

#include <iostream>
#include <vector>

#include "hit.hpp"
#include "object3d.hpp"
#include "kdtree.hpp"
#include "ray.hpp"

class Group
{
public:
  Group(const vector<Object3D *> &objs)
  {
    for (auto obj : objs)
    {
      vector<Object3D *> newFaces = obj->getFaces();
      faces.insert(faces.end(), newFaces.begin(), newFaces.end());
    }
    kdTree = new KDTree(&faces);
  }
  ~Group() { delete kdTree; }

  // 对列表里所有物体都求一遍交点
  bool intersect(const Ray &r, Hit &h) { return kdTree->intersect(r, h); }

  int getGroupSize() { return faces.size(); }
  Object3D *operator[](const int &i)
  {
    if (i >= int(faces.size()) || i < 0)
    {
      std::cerr << "Index Error: i = " << i << std::endl;
      return nullptr;
    }
    return faces[i];
  }

private:
  KDTree *kdTree;
  vector<Object3D *> faces;
};

#endif
