#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "common.hpp"
#include <CL/sycl.hpp>
#include <string>

class Image {
public:
  using Buffer = cl::sycl::buffer<Color, 1>;

  Image(unsigned width, unsigned height)
      : width_(width), height_(height), image_data_(width * height) {}

  Extent get_extent() const { return {width_, height_}; }

  Buffer get_buffer() { return Buffer(image_data_); }

  void save(std::string path) const;

private:
  unsigned width_, height_;
  std::vector<Color> image_data_;
};

#endif
