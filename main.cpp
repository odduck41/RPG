#include <stdbool.h>
#include <iostream>

#include "raylib.h"
#include "RPG_objects/Textures.hpp"


int main() {


    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Sprite animation");

    RPG::RPGTexture* object =
        new RPG::AnimatableTexture(
            "../assets/FreeCharactersAnimationsAssetPack/SpriteSheets(96x96)/Monster_Slime/With_Shadows/Monster_Slime-Sheet.png",
            Rectangle{.x = 0., .y = 0., .width = 96., .height = 96.}, 6, RPG::Idle, true
            );

    object->setPosition({.x = .0f, .y = 0.f});
    reinterpret_cast<RPG::AnimatableTexture*>(object)->setFrameSpeed(12.);

    reinterpret_cast<RPG::AnimatableTexture*>(object)->setTexture<RPG::Attack>(
        "../assets/FreeCharactersAnimationsAssetPack/SpriteSheets(96x96)/Monster_Slime/With_Shadows/Monster_Slime-Sheet.png",
        Rectangle{.x = 0., .y = 4. * 96, .width = 96., .height = 96.}, 8, false);
    // reinterpret_cast<RPG::AnimatableTexture*>(object)->setFrameSpeed<RPG::Attack>(8.);

    reinterpret_cast<RPG::AnimatableTexture*>(object)->setTexture<RPG::Walking>(
    "../assets/FreeCharactersAnimationsAssetPack/SpriteSheets(96x96)/Monster_Slime/With_Shadows/Monster_Slime-Sheet.png",
        Rectangle{.x = 0., .y = 96., .width = 96., .height = 96.}, 8, true);

    reinterpret_cast<RPG::AnimatableTexture*>(object)->setTexture<RPG::Jump>(
"../assets/FreeCharactersAnimationsAssetPack/SpriteSheets(96x96)/Monster_Slime/With_Shadows/Monster_Slime-Sheet.png",
        Rectangle{.x = 0., .y = 2 * 96., .width = 96., .height = 96.}, 6, false
    );
    Vector2 how_to = {0. , 0.};
    auto func = [&]() {
            auto a = object->getPosition();
            a.x += how_to.x;
            a.y += how_to.y;
            object->setPosition(a);
    };


    auto condition = [&] () {
            return (reinterpret_cast<RPG::AnimatableTexture*>(object)->getAnimationType() != RPG::Attack &&
            reinterpret_cast<RPG::AnimatableTexture*>(object)->getAnimationType() != RPG::Jump)
                 or
            reinterpret_cast<RPG::AnimatableTexture*>(object)->isFinished();
    };
#define K 5.5f
    object->setScaling({1. * K, 1. * K});
    SetTargetFPS(60);
    int gamepad = 0;
    while (!WindowShouldClose()) {
        if ((IsKeyDown(KEY_E) || IsGamepadButtonDown(gamepad, 7)) && condition()) {
            reinterpret_cast<RPG::AnimatableTexture*>(object)->setAnimationType(RPG::Attack);
            reinterpret_cast<RPG::AnimatableTexture*>(object)->setAfterAnimation([&]() {
                SetGamepadVibration(gamepad, 0.01f * IsGamepadButtonDown(gamepad, 7),
                    0.01f * IsGamepadButtonDown(gamepad, 7), 0.001);
            });
        } else if ((IsKeyDown(KEY_SPACE) || IsGamepadButtonDown(gamepad, 6)) && condition()) {
            reinterpret_cast<RPG::AnimatableTexture*>(object)->setAnimationType(RPG::Jump);
        } else if (condition() &&
            (fabs(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X)) > 0.15
            ||
             fabs(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y)) > 0.15)
            ){
            reinterpret_cast<RPG::AnimatableTexture*>(object)->setAnimationType(RPG::Walking);

            how_to = {2 * GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X),
                        2 * GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y)};

            object->setScaling({K,
                K * (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X)
                    / fabs(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X)))});

            reinterpret_cast<RPG::AnimatableTexture*>(object)->setAfterAnimation(func);
        } else if (condition() && (IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D))) {
            reinterpret_cast<RPG::AnimatableTexture*>(object)->setAnimationType(RPG::Walking);

            how_to = {(float)IsKeyDown(KEY_D) - IsKeyDown(KEY_A),(float)IsKeyDown(KEY_S) - IsKeyDown(KEY_W)};

            if (IsKeyDown(KEY_A)) {
                object->setScaling({1 * K, -1. * K});
            } else if (IsKeyDown(KEY_D)) {
                object->setScaling({1. * K, 1. * K});
            }

            reinterpret_cast<RPG::AnimatableTexture*>(object)->setAfterAnimation(func);
        } else if (condition()) {
            reinterpret_cast<RPG::AnimatableTexture*>(object)->setAnimationType(RPG::Idle);
        }
        object->update();

        BeginDrawing();

            ClearBackground(BROWN);
            object->draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}