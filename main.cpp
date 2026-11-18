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
    const auto sprite = new RPG::AnimatableSprite();
    sprite->setScaling(Vector2{3., 3.});
    sprite->addFile("Idle", {
        .path = "../assets/Farm RPG FREE 16x16 - Tiny Asset Pack/Character/Idle.png",
        .sheet_width = 128 / 4, .sheet_height = 96 / 3
    });
    sprite->addAnimation("Idle", RPG::TextureAnimation(4, 10, true));
    sprite->addAnimation("IdleBack", RPG::TextureAnimation(4, true));
    sprite->addAnimation("IdleRight", RPG::TextureAnimation(4, true));

    sprite->addFile("Walk", {
        .path = "../assets/Farm RPG FREE 16x16 - Tiny Asset Pack/Character/Walk.png",
        .sheet_width = 128 / 4, .sheet_height = 96 / 3
    });
    sprite->addAnimation("Walk", "Walk", RPG::TextureAnimation(4, true));
    sprite->addAnimation("WalkBack", "Walk", RPG::TextureAnimation(4, true));
    sprite->addAnimation("WalkRight", "Walk", RPG::TextureAnimation(4, true));

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        sprite->update();

        BeginDrawing();
            ClearBackground(BROWN);
            sprite->draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}