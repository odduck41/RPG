#include <stdbool.h>

#include "raylib.h"
#include "RPG_objects/Textures.hpp"


int main() {


    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Sprite animation");

    RPG::RPGTexture* object =
        new RPG::AnimatableTexture(
            "../assets/Orc.png",
            Rectangle{.x = 0., .y = 0., .width = 100., .height = 100.}, 6, RPG::Idle
            );

    object->setPosition({.x = .0f, .y = 0.f});
    reinterpret_cast<RPG::AnimatableTexture*>(object)->setFrameSpeed(12.);

    reinterpret_cast<RPG::AnimatableTexture*>(object)->setTexture<RPG::Attack>(
        "../assets/Orc.png",
        Rectangle{.x = 0., .y = 200., .width = 100., .height = 100.}, 4);
    // reinterpret_cast<RPG::AnimatableTexture*>(object)->setFrameSpeed<RPG::Attack>(8.);

    reinterpret_cast<RPG::AnimatableTexture*>(object)->setTexture<RPG::Walking>(
    "../assets/Orc.png",
        Rectangle{.x = 0., .y = 100., .width = 100., .height = 100.}, 8);

    reinterpret_cast<RPG::AnimatableTexture*>(object)->setAfterAnimation<RPG::Walking>([&]() {
            auto a = object->getPosition();
            a.x += 1.;
            object->setPosition(a);
    });

    object->setScaling(2);
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_E)) {
            reinterpret_cast<RPG::AnimatableTexture*>(object)->setAnimationTypeSmooth(RPG::Attack);
        } else if (IsKeyDown(KEY_D)) {
            reinterpret_cast<RPG::AnimatableTexture*>(object)->setAnimationTypeSmoothDropping(RPG::Walking);
        } else {
            reinterpret_cast<RPG::AnimatableTexture*>(object)->setAnimationTypeSmoothDropping(RPG::Idle);
        }

        object->update();

        BeginDrawing();

            ClearBackground(WHITE);
            object->draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}