#include "scene.hpp"

Camera::Camera(glm::vec3 look_from, glm::vec3 look_at, glm::vec3 up_dir, float vfov,
               float aspect_ratio, float aperture)
    : camera_orig_(look_from), focus_point_(look_at), lens_radius_(aperture / 2.0f) {
  glm::vec3 dir = look_at - look_from;
  float focal_dist = dir.length();
  u_ = glm::normalize(glm::cross(up_dir, dir));
  v_ = glm::normalize(glm::cross(dir, u_));
  viewport_height_ = focal_dist * glm::tan(glm::radians(vfov) / 2.0f);
  viewport_width_ = viewport_height_ * aspect_ratio;
}

Scene::Scene()
    : camera_(glm::vec3{50.f, 52.f, 295.6f}, glm::vec3{50.f, 48.f, 200.f},
              glm::vec3{0.0f, -1.0f, 0.0f}, 165.0f, 640.f / 480.f) {
  spheres_.emplace_back(
      glm::vec3(1e5f + 1.f, 40.8f, 81.6f), 1e5f,
      Material(glm::vec3(0.0f), glm::vec3(.75f, .25f, .25f), Material::Type::DIFF)); // Left
  spheres_.emplace_back(
      glm::vec3(-1e5f + 99.f, 40.8f, 81.6f), 1e5f,
      Material(glm::vec3(0.0f), glm::vec3(.25f, .25f, .75f), Material::Type::DIFF)); // Right
  spheres_.emplace_back(
      glm::vec3(50.f, 40.8f, 1e5f), 1e5f,
      Material(glm::vec3(0.0f), glm::vec3(.75f, .75f, .75f), Material::Type::DIFF)); // Back
  spheres_.emplace_back(
      glm::vec3(50.f, 1e5f, 81.6f), 1e5,
      Material(glm::vec3(0.0f), glm::vec3(.75f, .75f, .75f), Material::Type::DIFF)); // Bottom
  spheres_.emplace_back(
      glm::vec3(50.f, -1e5f + 81.6f, 81.6f), 1e5f,
      Material(glm::vec3(0.0f), glm::vec3(.75f, .75f, .75f), Material::Type::DIFF)); // Top
  spheres_.emplace_back(glm::vec3(27.f, 16.5f, 47.f), 16.5f,
                        Material(glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
                                 Material::Type::SPEC)); // Mirror
  spheres_.emplace_back(glm::vec3(73.f, 16.5f, 78.f), 16.5f,
                        Material(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                                 Material::Type::REFR)); // Glass
  spheres_.emplace_back(
      glm::vec3(50.f, 681.6 - .27f, 81.6f), 600.f,
      Material(glm::vec3(12.f), glm::vec3(0.0f, 0.0f, 1.0f), Material::Type::DIFF)); // Light
}
