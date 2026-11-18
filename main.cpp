#include <iostream>
#include <vector>

#include <string>
#include <sstream>

#include "raylib.h"
#include "RPG_objects/Sprite.hpp"

#define screenWidth 800
#define screenHeight 450
#define K 4.f

int main() {
    InitWindow(screenWidth, screenHeight, "Sprites");
    const auto sprite = new RPG::AnimatableSprite();
    sprite->addFile("Soldier", {
        .path = "/Users/leo/programming/RPG/assets/FreeCharactersAnimationsAssetPack/SpriteSheets(96x96)/Human_Soldier_Sword_Shield/With_Shadows/Human_Soldier_Sword_Shield-Sheet.png",
        .sheet_width = 960 / 10, .sheet_height = 768 / 8
    });
    sprite->setScaling({1. * K, 1. * K});
    sprite->addAnimation("Idle", RPG::TextureAnimation(6, true));

    Vector2 how_to = {.x = 0., .y = 0.};
    sprite->addAnimation("Walk", RPG::TextureAnimation(8, true), [&]() {
        auto pos = sprite->getPosition();
        pos.x += how_to.x * K * 2;
        pos.y += how_to.y * K * 2;
        sprite->setPosition(pos);
    });

    sprite->addAnimation("Jump", RPG::TextureAnimation(6, false, true));

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        sprite->update();
        if (IsKeyDown(KEY_SPACE)) {
            sprite->switchAnimation("Jump");
        } else if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D))) {
            how_to = {(float)IsKeyDown(KEY_D) - IsKeyDown(KEY_A), (float)IsKeyDown(KEY_S) - IsKeyDown(KEY_W)};
            if (IsKeyDown(KEY_A)) {
                sprite->setScaling({1 * K, -1. * K});
            } else if (IsKeyDown(KEY_D)) {
                sprite->setScaling({1. * K, 1. * K});
            }
            sprite->switchAnimation("Walk");
        } else {
            sprite->switchAnimation("Idle");
        }
        BeginDrawing();
            ClearBackground(BROWN);
            sprite->draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}