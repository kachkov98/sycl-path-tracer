#include "render.hpp"
#include <cstdlib>

int main(int argc, char **argv) {
  try {
    cxxopts::Options options("path-tracer", "Simple SYCL path tracing demo");
    // clang-format off
    options.add_options()
      #include "options.inl"
      ("help", "Print help");
    // clang-format on

    auto result = options.parse(argc, argv);
    if (result.count("help")) {
      std::cout << options.help() << std::endl;
      return 0;
    }

    Renderer(result).render();
  } catch (const cxxopts::OptionException &e) {
    std::cout << "Option parser exception: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
  } catch (const sycl::exception &e) {
    std::cout << "SYCL synchronous exception: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
