#ifndef CAMERA_H
#define CAMERA_H

#include "mystuff.hpp"
#include "ray.hpp"
#include <cmath>
#include <float.h>
#include <vecmath.h>

class Camera
{
public:
  Camera(const Vector3f &center, const Vector3f &direction, const Vector3f &up,
         int imgW, int imgH)
  {
    this->center = center;
    this->direction = direction.normalized();
    this->horizontal = Vector3f::cross(this->direction, up);
    this->up = Vector3f::cross(this->horizontal, this->direction);
    this->width = imgW;
    this->height = imgH;
  }

  // Generate rays for each screen-space coordinate
  virtual Ray generateRay(const Vector2f &point) = 0;
  virtual ~Camera() = default;

  int getWidth() const { return width; }
  int getHeight() const { return height; }

  void setCenter(const Vector3f &pos) { this->center = pos; }
  Vector3f getCenter() const { return this->center; }

  void setRotation(const Matrix3f &mat)
  {
    this->horizontal = mat.getCol(0);
    this->up = -mat.getCol(1);
    this->direction = mat.getCol(2);
  }
  Matrix3f getRotation() const
  {
    return Matrix3f(this->horizontal, -this->up, this->direction);
  }

  virtual void resize(int w, int h)
  {
    width = w;
    height = h;
  }

protected:
  // Extrinsic parameters
  Vector3f center;
  Vector3f direction;
  Vector3f up;
  Vector3f horizontal;
  // Intrinsic parameters
  int width;
  int height;
};

class PerspectiveCamera : public Camera
{
public:
  PerspectiveCamera(const Vector3f &center, const Vector3f &direction,
                    const Vector3f &up, int imgW, int imgH, float angle,
                    float f = 20.0f, float aperture = 1.0f)
      : Camera(center, direction, up, imgW, imgH), focalLength(f),
        aperture(aperture)
  {
    // angle is in radian.
    fovyd = angle / 3.1415 * 180.0;
    cx = (float)width / 2;
    cy = (float)height / 2;
    fx = fy = (float)height / (2 * tan(angle / 2));
  }

  void resize(int w, int h) override
  {
    fx *= (float)h / height;
    fy = fx;
    Camera::resize(w, h);
    cx = (float)width / 2;
    cy = (float)height / 2;
  }

  Ray generateRay(const Vector2f &pixel) override
  {

    float csx = focalLength * (pixel[0] - cx) / fx;
    float csy = focalLength * (pixel[1] - cy) / fy;
    float dx = Rand1() * aperture, dy = Rand1() * aperture;
    Vector3f d_Rc(csx - dx, -csy - dy, focalLength);
    Matrix3f R(horizontal, -up, direction);
    Vector3f d_Rw = (R * d_Rc).normalized();
    return Ray(center + horizontal * dx - up * dy, d_Rw);
  }

protected:
  float fx, fy, cx, cy;
  float fovyd;
  float focalLength, aperture;
};

#endif // CAMERA_H
