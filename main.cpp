#include <iostream>
#include <vector>

#include <string>
#include <sstream>

#include "raylib.h"
#include "RPG_objects/Sprite.hpp"
#include "RPG_objects/Textures.hpp"

#define screenWidth 800
#define screenHeight 450

int main() {
    InitWindow(screenWidth, screenHeight, "Sprites");
    // std::vector<RPG::TextureData*> objects;
    // objects.push_back(new RPG::SoloFileTexture());
    // objects.push_back(new RPG::MultipleFileTexture<>());
    // objects.push_back(new RPG::MultipleFileTexture<std::vector<Texture2D>>());
    RPG::Sprite* sprite = new RPG::AnimatableSprite();
    sprite->addFile("Idle", {
        .path = "../assets/Farm RPG FREE 16x16 - Tiny Asset Pack/Character/Idle.png",
        .sheet_width = 128 / 4, .sheet_height = 96 / 3
    });
    CloseWindow();
    return 0;
}