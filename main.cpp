#include <iostream>

#include "RPG_objects/Sprite.hpp"


int main() {
    InitWindow(800, 600, "Pumpkin");
    RPG::Frame frame;
    Texture texture = LoadTexture("../assets/Sunnyside_World_ARCHIVED_ASSETS/Sunnyside World/Sunnyside World - Gamemaker Studio/sprites/pumpkin_05/e5b34d16-0083-4af3-b94f-d4453f2cbe91.png");

    frame.setSourceRectangle({0, 0, 12, 14});
    frame.setDestinationRectangle({300, 300, 12, 14});
    frame.setScaling({5, 5});
    auto jump = [&]() {
        static float t = 0;
        auto destR = frame.getDestinationRectangle();
        destR.y = 300 + 10 * cos(t);
        frame.setDestinationRectangle(destR);
        t += 0.001;
    };

    while (!WindowShouldClose()) {
        jump();
        BeginDrawing();
            ClearBackground(WHITE);
            frame.draw(texture);
        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();
}