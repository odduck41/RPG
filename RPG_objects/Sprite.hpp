#pragma once

#include "Textures.hpp"

namespace RPG {

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
        [[nodiscard]] const double& getRotation() const {
            return rotation_;
        }


        virtual void update() = 0;
        virtual void draw() = 0;
        virtual ~Sprite() = default;
    protected:
        bool visible_{true};
        Vector2 position_{};
        Vector2 scaling_{.x = 1., .y = 1.};
        double rotation_{0};
        TextureData* texture_data_{};
    };
}
