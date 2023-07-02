#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <iostream>
#include <vecmath.h>

#include "hit.hpp"
#include "ray.hpp"
#include "texture.h"

class Material
{
public:
  explicit Material(const Vector3f &color,
                    const Vector3f &s_color = Vector3f::ZERO,
                    float shininess = 0,
                    const Vector3f &e_color = Vector3f::ZERO, float reflect = 1,
                    Vector3f type = Vector3f(1, 0, 0),
                    const char *textureFile = "", const char *bumpFile = "")
      : color(color), specularColor(s_color), emission(e_color), shininess(shininess),
        refr(reflect), type(type), texture(textureFile), bump(bumpFile) {}
  virtual ~Material() = default;

  Vector3f getColor(float u, float v) const
  {
    if (!texture.pic)
      return color;
    else
      return texture.getColor(u, v);
  }

  Vector3f color;         // 颜色
  Vector3f specularColor; // 镜面反射系数
  Vector3f emission;      // 发光系数
  float shininess;        // 高光指数
  float refr;             // 折射率
  Vector3f type;          // 种类
  Texture texture, bump;  // 纹理
  float RELU(float x) { return x > 0 ? x : 0; }
};

#endif // MATERIAL_H
