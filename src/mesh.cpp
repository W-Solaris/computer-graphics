#include "mesh.hpp"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

#include "Vector2f.h"
#include "Vector3f.h"
#include "AABB.hpp"
#include "object3d.hpp"
#include "kdtree.hpp"
#include "ray.hpp"
#include "triangle.hpp"

Mesh::Mesh(const char *filename, Material *m) : Object3D(m)
{
  std::vector<TriangleIndex> vIdx, tIdx, nIdx;
  std::vector<Vector3f> v, vn;
  std::vector<Vector2f> vt;
  std::ifstream f;
  f.open(filename);
  if (!f.is_open())
  {
    std::cout << "Cannot open " << filename << "\n";
    return;
  }
  std::string line;
  std::string vTok("v");
  std::string fTok("f");
  std::string vnTok("vn");
  std::string bslash("/"), space(" ");
  std::string tok;
  while (true)
  {
    std::getline(f, line);
    if (f.eof())
    {
      break;
    }
    if (line.size() < 3)
    {
      continue;
    }
    if (line.at(0) == '#')
    {
      continue;
    }
    std::stringstream ss(line);
    ss >> tok;
    if (tok == vTok)
    {
      Vector3f vec;
      ss >> vec[0] >> vec[1] >> vec[2];
      v.push_back(vec);
      aabb.updateRange(vec);
    }
    else if (tok == fTok)
    {
      TriangleIndex vId, nId;
      for (int i = 0; i < 3; ++i)
      {
        std::string str;
        ss >> str;
        std::vector<std::string> id = split(str, bslash);
        vId[i] = atoi(id[0].c_str()) - 1;
        if (id.size() > 2)
        {
          nId[i] = atoi(id[2].c_str()) - 1;
        }
      }
      vIdx.push_back(vId);
      nIdx.push_back(nId);
    }
  }
  f.close();
  for (int triId = 0; triId < (int)vIdx.size(); ++triId)
  {
    TriangleIndex &vIndex = vIdx[triId];
    this->triangles.push_back(
        (Object3D *)new Triangle(v[vIndex[0]], v[vIndex[1]], v[vIndex[2]], m));
    if (nIdx.size())
    {
      TriangleIndex &nIndex = nIdx[triId];
      if (nIndex.valid())
        ((Triangle *)triangles.back())
            ->setVNorm(vn[nIndex[0]], vn[nIndex[1]], vn[nIndex[2]]);
    }
  }
  kdTree = new KDTree(&triangles);
}

Mesh::~Mesh()
{
  for (int i = 0; i < int(triangles.size()); ++i)
    delete triangles[i];
  delete kdTree;
}

std::vector<std::string> Mesh::split(std::string str, std::string pattern)
{
  std::string::size_type pos;
  std::vector<std::string> result;
  str += pattern;
  int size = str.size();

  for (int i = 0; i < size; i++)
  {
    pos = str.find(pattern, i);
    if (int(pos) < size)
    {
      std::string s = str.substr(i, pos - i);
      result.push_back(s);
      i = pos + pattern.size() - 1;
    }
  }
  return result;
}
