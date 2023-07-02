#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "camera.hpp"
#include "group.hpp"
#include "image.hpp"
#include "light.hpp"
#include "material.hpp"
#include "mystuff.hpp"
#include "ray.hpp"
#include "scene_parser.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  for (int argNum = 1; argNum < argc; ++argNum)
  {
    std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
  }

  if (argc != 4)
  {
    std::cout << "Usage: ./bin/PA <input scene file> <output bmp file> <sample num>\n";
    return 1;
  }
  string inputFile = argv[1];
  string outputFile = argv[2];
  int samp_num = atoi(argv[3]);

  SceneParser sceneParser(inputFile.c_str());
  Camera *camera = sceneParser.getCamera();

  int width = camera->getWidth(), height = camera->getHeight();

  Image outImg(width, height);
  time_t start = time(NULL);
  cout << "Width: " << width << " Height: " << height << endl;

#pragma omp parallel for schedule(dynamic, 1) // OpenMP
  for (int x = 0; x < width; ++x)
  {
    float used = (time(NULL) - start), progress = (1. + x) / width;
    fprintf(stderr, "\rNow %5.2f%% Used: %.2f seconds", progress * 100., used);
    for (int y = 0; y < height; ++y)
    {
      Vector3f color = Vector3f::ZERO;
      for (int s = 0; s < samp_num; ++s)
      {
        Ray camRay = camera->generateRay(Vector2f(x + Rand1(), y + Rand1()));
        Group *group = sceneParser.getGroup();
        int trace_times = 0;
        Vector3f color_s = Vector3f::ZERO;

        Vector3f cf(1, 1, 1);
        while (true)
        {
          if (++trace_times > 15 || cf.max() < 1e-3)
            break;
          // 判断camRay是否和场景有交点,返回最近交点的数据,存储在hit中.
          Hit hit;
          if (!group->intersect(camRay, hit))
          {
            color_s += sceneParser.getBackgroundColor();
            break;
          }
          // Path Tracing
          camRay.origin += camRay.direction * hit.t;
          Material *material = hit.material;
          Vector3f refColor(hit.color), N(hit.normal);

          // Emission
          color_s += material->emission * cf;
          cf = cf * refColor;
          float simul_type = Rand2();
          if (simul_type <= material->type.x())
          { // diffuse
            float r1 = 2 * M_PI * Rand2();
            float r2 = Rand2(), r2s = sqrt(r2);
            Vector3f rotX, rotY;
            orthogonalize(N, rotX, rotY);
            camRay.direction = (rotX * cos(r1) * r2s + rotY * sin(r1) * r2s + N * sqrt(1 - r2)).normalized();
          }
          else if (simul_type <= material->type.x() + material->type.y())
          { // specular
            float cos = Vector3f::dot(camRay.direction, N);
            camRay.direction = (camRay.direction - N * (cos * 2)).normalized();
          }
          else
          { // refraction
            float n = material->refr;
            float R0 = ((1.0 - n) * (1.0 - n)) / ((1.0 + n) * (1.0 + n));
            if (Vector3f::dot(N, camRay.direction) > 0)
            {
              N.negate();
              n = 1 / n;
            }
            n = 1 / n;
            float cos_1 = -Vector3f::dot(camRay.direction, N);
            float cos_2_sqr = 1.0 - n * n * (1.0 - cos_1 * cos_1);
            float Rprob = R0 + (1.0 - R0) * pow(1.0 - cos_1, 5.0); // Schlick
            if (cos_2_sqr > 0 && Rand2() > Rprob)
              camRay.direction = ((camRay.direction * n) + (N * (n * cos_1 - sqrt(cos_2_sqr)))).normalized();
            else
              camRay.direction = (camRay.direction + N * (cos_1 * 2));
          }
        }
        color += color_s;
      }
      outImg.SetPixel(x, y, color / samp_num);
    }
  }

  outImg.SaveBMP(outputFile.c_str());
  return 0;
}
