// Copyright 2023 Evgenzayts evgenzaytsev2002@yandex.ru

#include "include/DeEnCodingImage.hpp"

int main(int argc, char *argv[]) {
    std::string image = "input-files/image.bmp";
    std::string message = "input-files/message.txt";
    auto DecodeEncodeImage = new DeEnCodingImage(image, message);

    return 0;
}
