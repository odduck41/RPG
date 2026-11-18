#include <iostream>
#include <vector>

#include <string>
#include <sstream>

#include "raylib.h"
#include "RPG_objects/Sprite.hpp"

#define screenWidth 800
#define screenHeight 450

int main() {
    // InitWindow(screenWidth, screenHeight, "Sprites");
    std::vector<RPG::TextureData*> objects;
    objects.push_back(new RPG::SoloFileTexture());
    objects.push_back(new RPG::MultipleFileTexture<>());
    objects.push_back(new RPG::MultipleFileTexture<std::vector<Texture2D>>());

    // CloseWindow();
    return 0;
}