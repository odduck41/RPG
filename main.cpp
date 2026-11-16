#include "raylib.h"
#include "RPG_objects/Textures.hpp"


int main() {


    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Sprite animation");

    RPG::RPGTexture* object = new RPG::AnimatableTexture;
    const auto obj = reinterpret_cast<RPG::AnimatableTexture*>(object);
    obj->setPosition({350.0f, 280.f});
    obj->setTexture("../raylib/examples/textures/resources/scarfy.png", 6);
    obj->setFrameSpeed(8);
    SetTargetFPS(60);

    int framesCounter = 0;

    while (!WindowShouldClose()) {
        ++framesCounter;
        if (framesCounter * obj->getFrameSpeed() >= 60) {
            framesCounter = 0;
            obj->update();
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawRectangle(400, 225, 100, 100, GREEN);

            object->draw();

        EndDrawing();
    }
    return 0;
}