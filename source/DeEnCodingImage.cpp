// Copyright 2023 Evgenzayts evgenzaytsev2002@yandex.ru

#include "../include/DeEnCodingImage.hpp"

DeEnCodingImage::DeEnCodingImage(std::string &pathImage, std::string &message)
    : pathImage(pathImage), message(message) {}

[[maybe_unused]] void DeEnCodingImage::setImage(std::string &pathImage) {
    pathImage = pathImage;
}

std::string &DeEnCodingImage::getImage() {
    return pathImage;
}

[[maybe_unused]] void DeEnCodingImage::setMessage(std::string &message) {
    message = message;
}

std::string &DeEnCodingImage::getMessage() {
    return message;
}

void DeEnCodingImage::decodeMessage() {

}

void DeEnCodingImage::encodeMessage() {

}
