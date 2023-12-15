//
// Created by evgen on 11.10.2023.
//

#include "DeEnCodingImage.hpp"

void DeEnCodingImage::decodeMessage(std::string &imageInputPath, std::string &messageOutputPath) {
    this->message.clear();
    this->imageInputPath = imageInputPath;
    this->messageOutputPath = messageOutputPath;

    std::string imageString;
    inputImage.open(this->imageInputPath);
    if (!inputImage)
        throw std::runtime_error("Не удалось открыть файл " + this->imageInputPath);
    std::string line;
    while(std::getline(inputImage, line)) {
        imageString.append(line);
    }
    inputImage.close();

    dataAddress = (uint)imageString[0x0A];

    uint8_t symbol1 = 0;
    for (uint i = dataAddress; i < dataAddress + SIZE_HEADER; ++i) {
        symbol1 |= (imageString[i] & 1) << (7 - ((i - dataAddress) % 8));
        if (((i - dataAddress) % 8 == 7) && (i != dataAddress)) {
            messageSize = (uint8_t)symbol1;
        }
    }

    uint8_t symbol2 = 0;
    for (uint i = dataAddress + SIZE_HEADER; i < dataAddress + SIZE_HEADER + messageSize * 8; ++i) {
        static int iter = 0;
        symbol2 |= (imageString[i] & 1) << (7 - (iter % 8));
        if ((iter % 8 == 7) && (i != dataAddress + SIZE_HEADER)) {
            message.push_back((char)symbol2);
            symbol2 = 0;
        }
        ++iter;
    }

    writeMessage();
}

void DeEnCodingImage::encodeMessage(std::string& imageInputPath, std::string& imageOutputPath,
                                    std::string& messageInputPath) {
    this->imageOutputPath = imageOutputPath;
    this->imageInputPath = imageInputPath;
    this->messageInputPath = messageInputPath;

    readMessage();

    std::string imageString;
    inputImage.open(imageInputPath);
    if (!inputImage.is_open())
        throw std::runtime_error("Не удалось открыть файл " + this->imageInputPath);
    std::string line;
    while(std::getline(inputImage, line)) {
        imageString.append(line);
    }
    inputImage.close();

    dataAddress = (uint)imageString[0x0A];

    for (int i = 0; i < 8; ++i) {
        uint8_t symbol = (uint8_t)messageSize;
        if (((symbol >> (7 - i)) & 1) == 1)
            imageString[dataAddress + i] |= 1;
        else
            imageString[dataAddress + i] &= 254;
    }

    for (int i = 0; i < messageSize; ++i) {
        if ((dataAddress + SIZE_HEADER + i * 8 + 8) >= imageString.size()) {
            messageSize =  i;
            break;
        }

        char symbol = message.at(i);
        for (int j = 0; j < 8; ++j) {
            if (((symbol >> (7 - j)) & 1) == 1)
                imageString[dataAddress + SIZE_HEADER + i * 8 + j] |= 1;
            else
                imageString[dataAddress + SIZE_HEADER + i * 8 + j] &= 254;
        }
    }

    outputImage.open(this->imageOutputPath);
    if(!outputImage.is_open())
        throw std::runtime_error("Не удалось открыть файл " + this->imageOutputPath);
    outputImage << imageString;
    outputImage.close();
}

void DeEnCodingImage::readMessage() {
    std::ifstream file(messageInputPath);
    if (!file.is_open())
        throw std::runtime_error("Не удалось открыть файл " + messageInputPath);
    std::string line;
    while(std::getline(file, line)) {
        message.append(line);
    }
    file.close();
    messageSize = (uint)message.size();
}

void DeEnCodingImage::writeMessage() {
    std::ofstream file(messageOutputPath);
    if (!file.is_open())
        throw std::runtime_error("Не удалось открыть файл " + messageOutputPath);
    file << message;
    file.close();
}
