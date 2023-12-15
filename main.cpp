//
// Created by evgen on 11.10.2023.
//
#include "DeEnCodingImage.hpp"

int main() {
    std::string inputMessage = "../inputData/message.txt";
    std::string inputImage = "../inputData/image.bmp";
    std::string outputMessage = "../outputData/message.txt";
    std::string outputImage = "../outputData/image.bmp";

    auto coder = DeEnCodingImage();
    coder.encodeMessage(inputImage, outputImage, inputMessage);
    coder.decodeMessage(outputImage, outputMessage);

    return 0;
}