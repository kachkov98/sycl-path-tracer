# sycl-path-tracing
Simple [SYCL](https://www.khronos.org/sycl/) path tracing demo

### External libraries
1. [cxxopts](https://github.com/jarro2783/cxxopts)
2. [glm](https://github.com/g-truc/glm)
3. [json](https://github.com/nlohmann/json)
4. [stb](https://github.com/nothings/stb)

### Build prerequisites
1. [CMake](https://cmake.org/) (version >= 3.8)
2. [ComputeCpp](https://www.codeplay.com/solutions/ecosystem/) - Codeplay's SYCL implementation
2. [Conan](https://conan.io/) package manager
### Build
<pre>
mkdir build && cd build
cmake -DComputeCpp_DIR=&lt;Path to ComputeCpp&gt; -DCMAKE_CXX_COMPILER=compute++ -DCMAKE_BUILD_TYPE=Release -GNinja ..
cmake --build .
</pre>
### Useful links
**General**  
1. http://www.pbr-book.org/3ed-2018/contents.html  
2. https://raytracing.github.io/  

**GPU-specific**  
1. SYCL path tracing tutorial:  
https://www.codeplay.com/portal/blogs/2020/05/19/ray-tracing-in-a-weekend-with-sycl-basic-sphere-tracing.html  
https://www.codeplay.com/portal/blogs/2020/06/19/ray-tracing-in-a-weekend-with-sycl-part-2-pixel-sampling-and-material-tracing.html  
2. Wavefront path tracing  
https://indico.kfki.hu/event/189/contributions/61/attachments/129/404/AMD_raytracing_best_practices.pdf 
