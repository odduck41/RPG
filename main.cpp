#include "raylib.h"
#include "RPG_objects/Textures.hpp"


int main() {


    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Sprite animation");

    RPG::RPGTexture* object =
        new RPG::AnimatableTexture("../assets/Solder-Walk.png", 8, RPG::Walking);
    object->setPosition({.x = 150.0f, .y = 80.f});
    object->setFrameSpeed(12.);
    object->setScaling(4);
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