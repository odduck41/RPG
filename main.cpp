#include "raylib.h"
#include "RPG_objects/Textures.hpp"


int main() {


    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Sprite animation");

    RPG::RPGTexture* object =
        new RPG::AnimatableTexture(
            "../assets/Orc.png",
            Rectangle{0., 0., 100., 100.}, 6, RPG::Idle
            );

    object->setPosition({.x = .0f, .y = 0.f});
    object->setFrameSpeed(12.);
    object->setScaling(2);
    SetTargetFPS(60);


    while (!WindowShouldClose()) {

        object->update();

        BeginDrawing();

            ClearBackground(WHITE);
            object->draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}