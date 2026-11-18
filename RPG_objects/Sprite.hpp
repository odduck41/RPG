#pragma once

#include <string>

#include "raylib.h"

namespace RPG {
    struct File {
        std::string alias{};
        std::string path{};
        unsigned int width{};
        unsigned int height{};
    };

    struct TextureAnimation {
        std::string alias{};
        unsigned int frameAmount{};
        double frameSpeed{};
        bool cycled{};
    };

    class Sprite {
    public:
        Sprite() = default;
        explicit Sprite(const Vector2& pos) : position_(pos) {}
        void show() {visible_ = true;}
        void hide() {visible_ = false;}

        void setPosition(const Vector2& pos) {
            position_ = pos;
        }
        [[nodiscard]] const Vector2& getPosition() const {
            return position_;
        }

        void setScaling(const Vector2& scaling) {
            scaling_ = scaling;
        }
        [[nodiscard]] const Vector2& getScaling() const {
            return scaling_;
        }

        void setRotation(const double& rotation) {
            rotation_ = rotation;
        }
        [[nodiscard]] const float& getRotation() const {
            return rotation_;
        }


        virtual void update() = 0;
        virtual void draw() = 0;
        virtual ~Sprite() = default;
    private:
        Vector2 position_{};
        Vector2 scaling_{.x = 1.f, .y = 1.f};
        float rotation_{0.f};
        bool visible_{true};
    };

}