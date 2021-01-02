#include "render.hpp"
#include <CL/sycl.hpp>
#include <iostream>
#include <limits>

using namespace sycl;

class image_generation;

Renderer::Renderer(const cxxopts::ParseResult &result)
    : queue_(sycl::default_selector{}),
      image_(result["width"].as<unsigned>(), result["height"].as<unsigned>()),
      image_path_(result["output"].as<std::string>()) {
  std::cout << "Running on " << queue_.get_device().get_info<sycl::info::device::name>()
            << std::endl;
}

void Renderer::render() {
  {
    // get buffers
    auto camera = scene_.get_camera();
    auto frame_buf = image_.get_buffer();
    auto spheres_buf = scene_.get_spheres_buffer();
    // create command  group
    queue_.submit([&](sycl::handler &cgh) {
      // get memory access
      auto spheres_ptr = spheres_buf.get_access<sycl::access::mode::read>(cgh);
      auto frame_ptr = frame_buf.get_access<sycl::access::mode::write>(cgh);
      // set up index space
      const auto global = sycl::range<2>(image_.get_height(), image_.get_width());
      const auto local = sycl::range<2>(8, 8);
      const auto index_space = sycl::nd_range<2>(global, local);
      // execute on device
      cgh.parallel_for<class image_generation>(index_space, [=](sycl::nd_item<2> item) {
        glm::vec2 pos{2.0f * item.get_global_id(1) / item.get_global_range().get(1) - 1.0f,
                      1.0f - 2.0f * item.get_global_id(0) / item.get_global_range().get(0)};
        Ray ray(camera.generate_ray(pos));
        float distance = std::numeric_limits<float>::infinity();
        glm::vec3 normal, color;
        for (unsigned i = 0; i < spheres_ptr.get_count(); ++i) {
          glm::vec3 new_pos, new_normal;
          float new_distance = spheres_ptr[i].intersect(ray, new_pos, new_normal);
          if (new_distance > 0.001f && new_distance < distance) {
            distance = new_distance;
            normal = new_normal;
          }
        }
        color = (normal + glm::vec3(1.0f)) / 2.0f;
        frame_ptr[item.get_global_linear_id()] = color * 255.999f;
      });
    });
  }
  std::cout << "Saving to " << image_path_ << std::endl;
  image_.save(image_path_);
}
