#pragma once
#include <string>
#include "raylib.h"
#include "Texture.hpp"

namespace RPG {
    class GameObject {
    public:
        GameObject() = default;
        void setTexture(std::string filename);
    private:
        RPGTexture* texture_{};
    };
}