#include <fstream>
#include <iostream>
#include <vector>

#include <string>
#include <sstream>
#include <nlohmann/json.hpp>

#include "raylib.h"
#include "RPG_objects/Sprite.hpp"

#define screenWidth 800
#define screenHeight 450
#define K 4.f

int main() {
    InitWindow(screenWidth, screenHeight, "Sprites");
    const auto sprite = new RPG::AnimatableSprite();
    sprite->setScaling({1. * K, 1. * K});
    sprite->addFile("Idle", {
                        .path = "../assets/Sunnyside_World_ARCHIVED_ASSETS/SUNNYSIDE_WORLD_CHARACTERS_PARTS_V0.3.1/IDLE/base_idle_strip9.png",
                        .sheet_width = 96, .sheet_height = 64
                    });
    sprite->addAnimation("Idle", RPG::TextureAnimation(9, true));
    sprite->addFile("Walk", {
                        .path = "../assets/Sunnyside_World_ARCHIVED_ASSETS/SUNNYSIDE_WORLD_CHARACTERS_PARTS_V0.3.1/WALKING/base_walk_strip8.png",
                        .sheet_width = 96, .sheet_height = 64
                    });
    // sprite->addAnimation("Walk", "Walk", RPG::TextureAnimation(8, true));

    auto hear = new RPG::AnimatableSprite();
    hear->setScaling({1. * K, 1. * K});
    hear->addFile("Idle", {
                      .path = "../assets/Sunnyside_World_ARCHIVED_ASSETS/SUNNYSIDE_WORLD_CHARACTERS_PARTS_V0.3.1/IDLE/spikeyhair_idle_strip9.png",
                      .sheet_width = 96, .sheet_height = 64
                  });
    hear->addAnimation("Idle", RPG::TextureAnimation(9, true));
    hear->addFile("Walk", {
                  .path = "../assets/Sunnyside_World_ARCHIVED_ASSETS/SUNNYSIDE_WORLD_CHARACTERS_PARTS_V0.3.1/WALKING/spikeyhair_walk_strip8.png",
                  .sheet_width = 96, .sheet_height = 64
              });


    // hear->addAnimation("Walk", "Walk", RPG::TextureAnimation(8, true));

    auto hand = new RPG::AnimatableSprite();
    hand->setScaling({1. * K, 1. * K});
    hand->addFile("Idle", {
                      .path = "../assets/Sunnyside_World_ARCHIVED_ASSETS/SUNNYSIDE_WORLD_CHARACTERS_PARTS_V0.3.1/IDLE/tools_idle_strip9.png",
                      .sheet_width = 96, .sheet_height = 64
                  });
    hand->addAnimation("Idle", RPG::TextureAnimation(9, true));
    hand->addFile("Walk", {
                      .path = "../assets/Sunnyside_World_ARCHIVED_ASSETS/SUNNYSIDE_WORLD_CHARACTERS_PARTS_V0.3.1/WALKING/tools_walk_strip8.png",
                      .sheet_width = 96, .sheet_height = 64
                  });
    // hand->addAnimation("Walk", "Walk", RPG::TextureAnimation(8, true));

    Vector2 how_to = {.x = 0., .y = 0.};
    sprite->addAnimation("Walk", "Walk", RPG::TextureAnimation(8, true), [&]() {
        auto pos = sprite->getPosition();
        pos.x += how_to.x * K * 2;
        pos.y += how_to.y * K * 2;
        sprite->setPosition(pos);
    });

    hand->addAnimation("Walk", "Walk", RPG::TextureAnimation(8, true), [&]() {
        auto pos = hand->getPosition();
        pos.x += how_to.x * K * 2;
        pos.y += how_to.y * K * 2;
        hand->setPosition(pos);
    });
    hear->addAnimation("Walk", "Walk", RPG::TextureAnimation(8, true), [&]() {
        auto pos = hear->getPosition();
        pos.x += how_to.x * K * 2;
        pos.y += how_to.y * K * 2;
        hear->setPosition(pos);
    });


    hear->addFile("Jump", {
                      .path = "../assets/Sunnyside_World_ARCHIVED_ASSETS/SUNNYSIDE_WORLD_CHARACTERS_PARTS_V0.3.1/JUMP/spikeyhair_jump_strip9.png",
                      .sheet_width = 96, .sheet_height = 64
                  });
    sprite->addFile("Jump", {
                        .path = "../assets/Sunnyside_World_ARCHIVED_ASSETS/SUNNYSIDE_WORLD_CHARACTERS_PARTS_V0.3.1/JUMP/base_jump_strip9.png",
                        .sheet_width = 96, .sheet_height = 64
                    });
    hand->addFile("Jump", {
      .path = "../assets/Sunnyside_World_ARCHIVED_ASSETS/SUNNYSIDE_WORLD_CHARACTERS_PARTS_V0.3.1/JUMP/tools_jump_strip9.png",
      .sheet_width = 96, .sheet_height = 64
  });
    sprite->addAnimation("Jump", "Jump", RPG::TextureAnimation(9, false, true));
    hear->addAnimation("Jump", "Jump", RPG::TextureAnimation(9, false, true));
    hand->addAnimation("Jump", "Jump", RPG::TextureAnimation(9, false, true));


    hear->addFile("Attack", {
                      .path = "../assets/Sunnyside_World_ARCHIVED_ASSETS/SUNNYSIDE_WORLD_CHARACTERS_PARTS_V0.3.1/ATTACK/spikeyhair_attack_strip10.png",
                      .sheet_width = 96, .sheet_height = 64
                  });
    sprite->addFile("Attack", {
                        .path = "../assets/Sunnyside_World_ARCHIVED_ASSETS/SUNNYSIDE_WORLD_CHARACTERS_PARTS_V0.3.1/ATTACK/base_attack_strip10.png",
                        .sheet_width = 96, .sheet_height = 64
                    });
    hand->addFile("Attack", {
      .path = "../assets/Sunnyside_World_ARCHIVED_ASSETS/SUNNYSIDE_WORLD_CHARACTERS_PARTS_V0.3.1/ATTACK/tools_attack_strip10.png",
      .sheet_width = 96, .sheet_height = 64
    });
    InitAudioDevice();
    const auto sound = LoadSound("../assets/sounds/568170__merrick079__sword-sound-1_16bit.wav");
    sprite->addAnimation("Attack", "Attack", RPG::TextureAnimation(10, false, true), [&]() {
        SetGamepadVibration(0, 0.6, 0.6, 0.1);
        if (!IsSoundPlaying(sound)) {
            PlaySound(sound);
        }
    });
    hear->addAnimation("Attack", "Attack", RPG::TextureAnimation(10, false, true));
    hand->addAnimation("Attack", "Attack", RPG::TextureAnimation(10, false, true));

    int fps = 60;
    // SetTargetFPS(fps);
#define gamepad 0
    auto last = std::chrono::steady_clock::now();
    int FPS = 0, counter = 0;
    while (!WindowShouldClose()) {

        sprite->update();
        hear->update();
        hand->update();
        if (IsKeyDown(KEY_K)) {
            --fps;
            SetTargetFPS(fps);
        } else if (IsKeyDown(KEY_I)) {
            ++fps;
            SetTargetFPS(fps);
        }
        if (IsKeyDown(KEY_SPACE) || IsGamepadButtonDown(0, 7)) {
            sprite->switchAnimation("Jump");
            hear->switchAnimation("Jump");
            hand->switchAnimation("Jump");
        } else if (IsKeyDown(KEY_E) || IsGamepadButtonDown(0, 6)) {
            sprite->switchAnimation("Attack");
            hear->switchAnimation("Attack");
            hand->switchAnimation("Attack");
        } else if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)) || (fabs(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X)) > 0.15
            ||
             fabs(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y)) > 0.15)) {
            how_to = {(float) IsKeyDown(KEY_D) - IsKeyDown(KEY_A) + GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X), (float) IsKeyDown(KEY_S) - IsKeyDown(KEY_W) + GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y)};
            if (IsKeyDown(KEY_A)) {
                hear->setScaling({1 * K, -1. * K});
                sprite->setScaling({1 * K, -1. * K});
                hand->setScaling({1 * K, -1. * K});
            } else if (IsKeyDown(KEY_D)) {
                hear->setScaling({1. * K, 1. * K});
                sprite->setScaling({1. * K, 1. * K});
                hand->setScaling({1. * K, 1. * K});
            } else if ((fabs(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X)) > 0.15)) {
                hear->setScaling({1. * K, 1.f * K * GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) / fabs(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X))});
                sprite->setScaling({1. * K, 1.f * K *  GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) / fabs(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X))});
                hand->setScaling({1. * K, 1.f * K *  GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) / fabs(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X))});
            }

            sprite->switchAnimation("Walk");
            hear->switchAnimation("Walk");
            hand->switchAnimation("Walk");
        } else {
            sprite->switchAnimation("Idle");
            hear->switchAnimation("Idle");
            hand->switchAnimation("Idle");
        }
        BeginDrawing();
            ClearBackground(BROWN);
            sprite->draw();
            hear->draw();
            hand->draw();
            const auto timer = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(timer - last).count() == 1) {
                FPS = counter;
                counter = 0;
                last = timer;
            }
            DrawText(std::format("FPS is {} \nActual FPS is {}", fps, FPS).c_str(), 0, 0, 10, WHITE);
        EndDrawing();
        ++counter;
    }
    CloseWindow();
    return 0;
}