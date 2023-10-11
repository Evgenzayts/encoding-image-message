set(CMAKE_MINIMUM_REQUIRED_VERSION 14)
project(image-decode-encode)

add_executable(image-decode-encode include/DeEnCodingImage.hpp
                                   source/DeEnCodingImage.cpp
                                   main.cpp)
set(EXECUTABLE_OUTPUT_PATH $(PROJECT-SOURCE-DIR))