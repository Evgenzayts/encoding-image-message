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
        imageString += line;
    }
    inputImage.close();

    int8_t symbol1 = 0;
    for (int i = BMP_HEADER; i < ENCODE_HEADER; ++i) {
        static int iter = 0;
        symbol1 |= (imageString[i] & 1) << (7 - (iter % 8));
        if (iter % 8 == 7 && i != BMP_HEADER) {
            messageSize = (int)symbol1;
            symbol1 = 0;
        }
        ++iter;
    }

    int8_t symbol2 = 0;
    for (int i = ENCODE_HEADER; i < ENCODE_HEADER + messageSize * 8; ++i) {
        static int iter = 0;
            symbol2 |= (imageString[i] & 1) << (7 - (iter % 8));
        if (iter % 8 == 7 && i != ENCODE_HEADER) {
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
        imageString += line;
    }
    inputImage.close();

    for (int i = 0; i < 8; ++i) {
        int8_t symbol = (int8_t)messageSize;
        if (((symbol >> (7 - i)) & 1) == 1)
            imageString[BMP_HEADER + i * 8 + i] |= 1;
        else
            imageString[BMP_HEADER + i * 8 + i] &= 254;
    }

    for (int i = 0; i < messageSize; ++i) {
        if ((ENCODE_HEADER + i * 8 + 8) < imageString.size()) {
            messageSize =  i;
            break;
        }

        char symbol = message.at(i);
        for (int j = 0; j < 8; ++j) {
            if (((symbol >> (7 - j)) & 1) == 1)
                imageString[ENCODE_HEADER + i * 8 + j] |= 1;
            else
                imageString[ENCODE_HEADER + i * 8 + j] &= 254;
        }
    }

    outputImage.open(this->imageOutputPath);
    if(!outputImage.is_open())
        throw std::runtime_error("Не удалось открыть файл " + this->imageOutputPath);
    outputImage << imageString;
    outputImage.close();
}

void DeEnCodingImage::readMessage() {
    messageSize = (int)message.size();
    std::ifstream file(messageInputPath);
    if (!file.is_open())
        throw std::runtime_error("Не удалось открыть файл " + messageInputPath);
    std::string line;
    while(std::getline(file, line)) {
        message.append(line);
    }
    file.close();
}

void DeEnCodingImage::writeMessage() {
    std::ofstream file(messageOutputPath);
    if (!file.is_open())
        throw std::runtime_error("Не удалось открыть файл " + messageOutputPath);
    file << message;
    file.close();
}
