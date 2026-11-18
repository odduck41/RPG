#pragma once

#include <string>

#include "raylib.h"

namespace RPG {
    struct File {
        std::string alias{};
        std::string path{};
        unsigned int width{};
        unsigned int height{};
    };

    struct TextureAnimation {
        std::string alias{};
        unsigned int frameAmount{};
        double frameSpeed{};
        bool cycled{};
    };


}