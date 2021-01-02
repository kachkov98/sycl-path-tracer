#ifndef COMMON_HPP
#define COMMON_HPP

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using Color = glm::u8vec3;
using Extent = glm::uvec2;

struct Ray {
  glm::vec3 orig, dir;
};

#endif
