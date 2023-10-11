// Copyright 2023 Evgenzayts evgenzaytsev2002@yandex.ru

#ifndef ENCODING_IMAGE_MESSAGE_DEENCODINGIMAGE_HPP
#define ENCODING_IMAGE_MESSAGE_DEENCODINGIMAGE_HPP

#include <iostream>

class DeEnCodingImage {
public:
    DeEnCodingImage(std::string& pathImage, std::string& message);

    [[maybe_unused]] void setImage(std::string& pathImage);
    std::string& getImage();
    [[maybe_unused]] void setMessage(std::string& message);
    std::string& getMessage();
    void decodeMessage();
    void encodeMessage();

private:
    std::string message;
    std::string pathImage;
};


#endif //ENCODING_IMAGE_MESSAGE_DEENCODINGIMAGE_HPP
