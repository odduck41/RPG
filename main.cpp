#include "raylib.h"
#include "RPG_objects/Textures.hpp"


int main() {


    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Sprite animation");

    RPG::RPGTexture* object =
        new RPG::AnimatableTexture("../Solder-Walk.png", 8, RPG::Walking);
    object->setPosition({.x = 150.0f, .y = 80.f});
    object->setFrameSpeed(1.);
    object->setScaling(4);
    SetTargetFPS(60);

    int framesCounter = 0;

    while (!WindowShouldClose()) {
        ++framesCounter;
        if (framesCounter * object->getFrameSpeed() >= 60) {
            framesCounter = 0;
            object->update();
        }

        BeginDrawing();

            ClearBackground(WHITE);
            object->draw();

        EndDrawing();
    }
    return 0;
}