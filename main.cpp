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

    object->setScaling(2);
    SetTargetFPS(60);

    bool x = false;

    while (!WindowShouldClose()) {

        object->update();
        if (IsKeyPressed(KEY_D)) {
            x = !x;
        }
        if (x) {
            reinterpret_cast<RPG::AnimatableTexture*>(object)->setAnimationType(RPG::Attack);
        } else {
            reinterpret_cast<RPG::AnimatableTexture*>(object)->setAnimationType(RPG::Idle);

        }
        BeginDrawing();

            ClearBackground(WHITE);
            object->draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}