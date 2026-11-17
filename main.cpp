#include "raylib.h"
#include "RPG_objects/Textures.hpp"


int main() {


    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Sprite animation");

    RPG::RPGTexture* object =
        new RPG::AnimatableTexture("../raylib/examples/textures/resources/scarfy.png", 6, RPG::Running);
    object->setPosition({.x = 350.0f, .y = 280.f});
    object->setFrameSpeed(8.); // Frame updates every 1/8 second
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