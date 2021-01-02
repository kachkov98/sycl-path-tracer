#include "image.hpp"
#include <CL/sycl.hpp>
#include <cxxopts.hpp>

class image_generation;

int main(int argc, char **argv) {
  using namespace cl;

  cxxopts::Options options("path-tracer", "Simple SYCL path tracing demo");
  // clang-format off
  options.add_options()
    ("w,width",  "Image width",  cxxopts::value<unsigned>()->default_value("640"))
    ("h,height", "Image height", cxxopts::value<unsigned>()->default_value("480"))
    ("o,output", "Image output", cxxopts::value<std::string>()->default_value("result.png"))
    ("help", "Print help")
  ;
  // clang-format on

  auto result = options.parse(argc, argv);
  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  auto width = result["width"].as<unsigned>();
  auto height = result["height"].as<unsigned>();
  auto output_path = result["output"].as<std::string>();

  // create image
  Image image(width, height);

  // use default device selector
  sycl::default_selector selector;
  // create sycl queue
  sycl::queue queue(selector);
  // get device info
  std::cout << "Running on " << queue.get_device().get_info<sycl::info::device::name>() << "\n\n";
  {
    // set up frame buffer
    auto frame_buf = image.get_buffer();
    // create command  group
    queue.submit([&](sycl::handler &cgh) {
      // get memory access
      auto frame_ptr = frame_buf.get_access<sycl::access::mode::write>(cgh);
      // set up index space
      const auto global = sycl::range<2>(width, height);
      const auto local = sycl::range<2>(8, 8);
      const auto index_space = sycl::nd_range<2>(global, local);
      // execute on device
      cgh.parallel_for<class image_generation>(index_space, [=](sycl::nd_item<2> item) {
        const auto x_coord = item.get_global_id(0);
        const auto y_coord = item.get_global_id(1);
        const auto pixel_index = y_coord * width + x_coord;
        Color color{255.f * x_coord / width, 255.f * y_coord / height, 0};
        frame_ptr[pixel_index] = color;
      });
    });
  }

  // save image
  image.save(output_path);
  return 0;
}
