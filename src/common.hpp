#ifndef COMMON_HPP
#define COMMON_HPP

#include <glm/glm.hpp>

using Color = glm::u8vec3;

class Ray {
public:
  Ray(glm::vec3 orig, glm::vec3 dir, bool force_normalize = true)
      : orig_(orig), dir_(force_normalize ? glm::normalize(dir) : dir) {}
  glm::vec3 at(float t) const { return orig_ + dir_ * t; }
  glm::vec3 orig() const { return orig_; }
  glm::vec3 dir() const { return dir_; }

private:
  glm::vec3 orig_, dir_;
};

#endif
