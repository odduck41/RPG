#pragma once
#include <string>
#include "raylib.h"
#include "Textures.hpp"

namespace RPG {
    class GameObject {
    public:
        GameObject() = default;
        void setTexture(std::string filename);
    private:
        RPGTexture* texture_{};
    };
}