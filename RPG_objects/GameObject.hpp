#pragma once
#include <string>
#include "raylib.h"

class GameObject {
public:
    GameObject(std::string filename)
        : texture_(LoadTextureFromImage(LoadImage(std::move(filename).c_str()))) {}
private:
    Texture2D texture_;
};