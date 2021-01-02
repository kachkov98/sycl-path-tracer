#include "image.hpp"
#include <filesystem>
#include <stdexcept>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

void Image::save(std::string path) const {
  stbi_flip_vertically_on_write(1);
  std::string extension = std::filesystem::path(path).extension();
  if (extension == ".png")
    stbi_write_png(path.c_str(), width_, height_, Color::length(), image_data_.data(),
                   width_ * Color::length());
  else if (extension == ".bmp")
    stbi_write_bmp(path.c_str(), width_, height_, Color::length(), image_data_.data());
  else if (extension == ".tga")
    stbi_write_tga(path.c_str(), width_, height_, Color::length(), image_data_.data());
  else if (extension == ".jpg")
    stbi_write_jpg(path.c_str(), width_, height_, Color::length(), image_data_.data(), 100);
  else
    throw std::runtime_error("Unsupported image type " + extension);
}
