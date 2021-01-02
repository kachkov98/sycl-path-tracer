#ifndef RENDER_HPP
#define RENDER_HPP

#include "image.hpp"
#include "scene.hpp"
#include <CL/sycl.hpp>
#include <cxxopts.hpp>

namespace sycl = cl::sycl;

class Renderer {
public:
  Renderer(const cxxopts::ParseResult &result);
  void render();

private:
  sycl::queue queue_;
  Image image_;
  Scene scene_;
  std::string image_path_;
};

#endif
