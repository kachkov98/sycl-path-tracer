#ifndef SCENE_HPP
#define SCENE_HPP

#include "common.hpp"
#include <CL/sycl.hpp>
#include <glm/gtx/intersect.hpp>
#include <limits>
#include <vector>

class Camera {
public:
  Camera(glm::vec3 look_from, glm::vec3 look_at, glm::vec3 up_dir, float vfov, float aspect_ratio,
         float aperture = 0.0f);
  Ray generate_ray(glm::vec2 pos) const {
    auto offset = glm::vec2(); // glm::diskRand(lens_radius_);
    auto ray_origin = camera_orig_ + u_ * offset.x + v_ * offset.y;
    auto ray_target = focus_point_ + u_ * pos.x * viewport_width_ + v_ * pos.y * viewport_height_;
    return Ray(ray_origin, ray_target - ray_origin);
  }

private:
  glm::vec3 camera_orig_, focus_point_, u_, v_;
  float viewport_width_, viewport_height_, lens_radius_;
};

class Material {
public:
  enum class Type { DIFF, SPEC, REFR };
  Material(glm::vec3 emission, glm::vec3 color, Type type)
      : emission_(emission), color_(color), type_(type) {}

  glm::vec3 get_color() const { return color_; }

private:
  glm::vec3 emission_, color_;
  Type type_;
};

class Sphere {
public:
  Sphere(glm::vec3 pos, float radius, Material material)
      : pos_(pos), radius_(radius), material_(material) {}

  float intersect(const Ray &ray, glm::vec3 &pos, glm::vec3 &normal) {
    float distance;
    if (glm::intersectRaySphere(ray.orig(), ray.dir(), pos_, radius_ * radius_, distance)) {
      glm::intersectRaySphere(ray.orig(), ray.dir(), pos_, radius_, pos, normal);
      return distance;
    }
    return std::numeric_limits<float>::infinity();
  }

  Material get_material() const { return material_; }

private:
  glm::vec3 pos_;
  float radius_;
  Material material_;
};

class Scene {
public:
  using SpheresBufType = cl::sycl::buffer<Sphere, 1>;
  Scene();
  const Camera &get_camera() const { return camera_; }
  SpheresBufType get_spheres_buffer() { return SpheresBufType(spheres_); }

private:
  Camera camera_;
  std::vector<Sphere> spheres_;
};

#endif
