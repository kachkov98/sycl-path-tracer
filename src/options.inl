("w,width",  "Image width",  cxxopts::value<unsigned>()->default_value("640"))
("h,height", "Image height", cxxopts::value<unsigned>()->default_value("480"))
("o,output", "Image output", cxxopts::value<std::string>()->default_value("result.png"))
