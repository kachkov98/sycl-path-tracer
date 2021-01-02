#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "common.hpp"
#include <CL/sycl.hpp>
#include <string>

class Image {
public:
  using ImageBufType = cl::sycl::buffer<Color, 1>;

  Image(unsigned width, unsigned height)
      : width_(width), height_(height), image_data_(width * height) {}

  unsigned get_width() const { return width_; }

  unsigned get_height() const { return height_; }

  ImageBufType get_buffer() { return ImageBufType(image_data_); }

  void save(std::string path) const;

private:
  unsigned width_, height_;
  std::vector<Color> image_data_;
};

#endif
