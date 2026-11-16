#pragma once
#include "raylib.h"
#include <string>

namespace RPG {
    class RPGTexture {
    public:
        explicit RPGTexture(std::string filename)
            : image_(new Image(LoadImage(std::move(filename).c_str()))),
              texture_(new Texture2D(LoadTextureFromImage(*image_))) {}

        ~RPGTexture() {
            UnloadTexture(*texture_);
            UnloadImage(*image_);
        }
    private:
        Image* image_{};
        Texture2D* texture_{};
        Rectangle* rectangle_{};
    };
}