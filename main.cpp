#include <iostream>
#include <vector>

#include "RPG_objects/Sprite.hpp"


int main() {
    InitWindow(800, 600, "Pumpkin");
    std::vector<RPG::Sprite*> sprites;
    sprites.push_back(new RPG::AnimatableSprite());
    sprites[0]->setScaling({5, 5});
    dynamic_cast<RPG::AnimatableSprite*>(sprites[0])->addFile("Soldier", "../assets/Tiny RPG Character Asset Pack 01 v2.0 -Free Soldier&Orc/Characters(100x100 split)/Soldier/Soldier/Soldier.png");
    dynamic_cast<RPG::AnimatableSprite*>(sprites[0])->addAnimation("Soldier", 0, "Idle", {
        100, 100, 6
    }, RPG::AnimSpeed(20));
    dynamic_cast<RPG::AnimatableSprite*>(sprites[0])->setAnimation("Idle");
    while (!WindowShouldClose()) {
        sprites[0]->update();
        BeginDrawing();
            ClearBackground(WHITE);
            sprites[0]->draw();
        EndDrawing();
    }
    CloseWindow();
}