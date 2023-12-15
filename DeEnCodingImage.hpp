//
// Created by evgen on 11.10.2023.
//

#ifndef ENCODING_IMAGE_MESSAGE_DEENCODINGIMAGE_HPP
#define ENCODING_IMAGE_MESSAGE_DEENCODINGIMAGE_HPP

#define SIZE_HEADER 8

#include <iostream>
#include <fstream>

class DeEnCodingImage {
public:
    std::string imageInputPath;
    std::string imageOutputPath;
    std::string messageInputPath;
    std::string messageOutputPath;
private:
    uint dataAddress;
    uint messageSize;
    std::string message;
    std::ifstream inputImage;
    std::ofstream outputImage;

public:
    void readMessage();
    void writeMessage();
    void decodeMessage(std::string& imageInputPath, std::string& messageOutputPath);
    void encodeMessage(std::string& imageInputPath, std::string& imageOutputPath, std::string& messageInputPath);
};


#endif //ENCODING_IMAGE_MESSAGE_DEENCODINGIMAGE_HPP
