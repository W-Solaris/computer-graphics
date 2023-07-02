#ifndef KDTree_H
#define KDTree_H
#include <vecmath.h>

#include <map>
#include <vector>

#include "AABB.hpp"
#include "hit.hpp"
#include "object3d.hpp"
using std::map;
using std::vector;
#define INF 0x10000000

class KDTreeNode
{
public:
  Vector3f min, max;
  vector<Object3D *> *patches;
  KDTreeNode *left, *right;
  int l, r;
  bool inside(Object3D *patch)
  {
    Vector3f patchMin = patch->min();
    Vector3f patchMax = patch->max();
    return (patchMin.x() < max.x() ||
            (patchMin.x() == max.x() && patchMin.x() == patchMax.x())) &&
           (patchMax.x() > min.x() ||
            (patchMax.x() == min.x() && patchMin.x() == patchMax.x())) &&
           (patchMin.y() < max.y() ||
            (patchMin.y() == max.y() && patchMin.y() == patchMax.y())) &&
           (patchMax.y() > min.y() ||
            (patchMax.y() == min.y() && patchMin.y() == patchMax.y())) &&
           (patchMin.z() < max.z() ||
            (patchMin.z() == max.z() && patchMin.z() == patchMax.z())) &&
           (patchMax.z() > min.z() ||
            (patchMax.z() == min.z() && patchMin.z() == patchMax.z()));
  }
};

class KDTree
{
  int n;
  Vector3f **vertices;
  KDTreeNode *build(int depth, int d, vector<Object3D *> *patches,
                    const Vector3f &min, const Vector3f &max)
  {
    KDTreeNode *p = new KDTreeNode;
    p->min = min;
    p->max = max;
    Vector3f maxL, minR;
    if (d == 0)
    {
      maxL = Vector3f((p->min.x() + p->max.x()) / 2, p->max.y(), p->max.z());
      minR = Vector3f((p->min.x() + p->max.x()) / 2, p->min.y(), p->min.z());
    }
    else if (d == 1)
    {
      maxL = Vector3f(p->max.x(), (p->min.y() + p->max.y()) / 2, p->max.z());
      minR = Vector3f(p->min.x(), (p->min.y() + p->max.y()) / 2, p->min.z());
    }
    else
    {
      maxL = Vector3f(p->max.x(), p->max.y(), (p->min.z() + p->max.z()) / 2);
      minR = Vector3f(p->min.x(), p->min.y(), (p->min.z() + p->max.z()) / 2);
    }
    p->patches = new vector<Object3D *>;
    for (auto patch : *patches)
      if (p->inside(patch))
        p->patches->push_back(patch);

    const int max_patches = 256;
    const int max_depth = 22;

    if (p->patches->size() > max_patches && depth < max_depth)
    {
      p->left = build(depth + 1, (d + 1) % 3, p->patches, min, maxL);
      p->right = build(depth + 1, (d + 1) % 3, p->patches, minR, max);

      vector<Object3D *> *patchLeft = p->left->patches;
      vector<Object3D *> *patchRight = p->right->patches;
      map<Object3D *, int> cnt;
      for (auto patch : *patchLeft)
        cnt[patch]++;
      for (auto patch : *patchRight)
        cnt[patch]++;
      p->left->patches = new vector<Object3D *>;
      p->right->patches = new vector<Object3D *>;
      p->patches->clear();
      for (auto patch : *patchLeft)
        if (cnt[patch] == 1)
          p->left->patches->push_back(patch);
        else
          p->patches->push_back(patch);
      for (auto patch : *patchRight)
        if (cnt[patch] == 1)
          p->right->patches->push_back(patch);
    }
    else
      p->left = p->right = nullptr;
    return p;
  }

  void getPatches(KDTreeNode *p, vector<Object3D *> *patches)
  {
    p->l = patches->size();
    for (auto patch : *(p->patches))
      patches->push_back(patch);
    p->r = patches->size();
    if (p->left)
      getPatches(p->left, patches);
    if (p->right)
      getPatches(p->right, patches);
  }

public:
  KDTreeNode *root;
  vector<Object3D *> *patches;
  KDTree(vector<Object3D *> *patches)
  {
    Vector3f min = Vector3f(INF, INF, INF);
    Vector3f max = -min;
    for (auto patch : *patches)
    {
      min = minE(min, patch->min());
      max = maxE(max, patch->max());
    }
    root = build(1, 0, patches, min, max);
    this->patches = new vector<Object3D *>;
    getPatches(root, this->patches);
  }

  float cuboidIntersect(KDTreeNode *p, const Ray &ray) const
  {
    float t = INF;
    if (!p)
      return t;
    AABB(p->min, p->max).intersect(ray, t);
    return t;
  }

  bool intersect(const Ray &ray, Hit &hit) const
  {
    Object3D *nextpatch = nullptr;
    return intersect(root, ray, nextpatch, hit);
  }

  bool intersect(KDTreeNode *p, const Ray &ray, Object3D *&nextpatch,
                 Hit &hit) const
  {
    bool flag = false;
    for (int i = 0; i < int(p->patches->size()); ++i)
      if ((*p->patches)[i]->intersect(ray, hit))
      {
        nextpatch = (*p->patches)[i];
        flag = true;
      }
    float tl = cuboidIntersect(p->left, ray), tr = cuboidIntersect(p->right, ray);
    if (tl < tr)
    {
      if (hit.t <= tl)
        return flag;
      if (p->left)
        flag |= intersect(p->left, ray, nextpatch, hit);
      if (hit.t <= tr)
        return flag;
      if (p->right)
        flag |= intersect(p->right, ray, nextpatch, hit);
    }
    else
    {
      if (hit.t <= tr)
        return flag;
      if (p->right)
        flag |= intersect(p->right, ray, nextpatch, hit);
      if (hit.t <= tl)
        return flag;
      if (p->left)
        flag |= intersect(p->left, ray, nextpatch, hit);
    }
    return flag;
  }
};

#endif // !KDTree_H