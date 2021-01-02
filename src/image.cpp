#include "image.hpp"
#include <filesystem>
#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

void Image::save(std::string path) const {
  std::cout << "Saving to " << path << std::endl;
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
    std::cout << "Unsupported image type " << extension << std::endl;
}
