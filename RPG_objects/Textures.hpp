#pragma once
#include <algorithm>
// #include <cassert>
#include <string>

#include "raylib.h"

namespace RPG {
    class RPGTexture {
    public:
        RPGTexture() = default;
        explicit RPGTexture(const Vector2& pos) : position_(pos) {}
        void show() {visible_ = true;}
        void hide() {visible_ = false;}

        void setPosition(const Vector2& pos) {
            position_ = pos;
        }
        [[nodiscard]] const Vector2& getPosition() const {
            return position_;
        }

        void setScaling(const double& scaling) {
            scaling_ = scaling;
        }
        [[nodiscard]] const double& getScaling() const {
            return scaling_;
        }

        void setRotation(const double& rotation) {
            rotation_ = rotation;
        }
        [[nodiscard]] const double& getRotation() const {
            return rotation_;
        }


        virtual void setFrameSpeed(const double& speed) = 0;

         [[nodiscard]] virtual double getFrameSpeed() const {
            return 1.;
        }

        virtual void update() = 0;
        virtual void draw() = 0;
        virtual ~RPGTexture() = default;
    protected:
        bool visible_{true};
        Vector2 position_{};
        double scaling_{1};
        double rotation_{0};
    };

    enum AnimationTypes {
        Still,
        Going,
        Running,
        Attack,
        Eating,
        Fishing
    };

    class AnimatableTexture : public RPGTexture {
    public:
        AnimatableTexture() = default;

        AnimatableTexture(const std::string& filename, const Rectangle& rect, const AnimationTypes type = Still) {
            setAnimationType(type);
            setTexture(filename, rect);
        }

        AnimatableTexture(const std::string& filename, const int& states, const AnimationTypes type = Still) {
            setAnimationType(type);
            setTexture(filename, states);
        }

        template<AnimationTypes type>
        void setTexture(const std::string& filename, const Rectangle& rect) {
            textures_[type] = LoadTexture(std::move(filename).c_str());
            source_rectangles_[type] = rect;
            states_[type] = textures_[type].width / static_cast<int>(rect.width);
        }

        void setTexture(const std::string& filename, const Rectangle& rect) {
            textures_[type_] = LoadTexture(std::move(filename).c_str());
            source_rectangles_[type_] = rect;
            states_[type_] = textures_[type_].width / static_cast<int>(rect.width);
        }

        template<AnimationTypes type>
        void setTexture(const std::string& filename, const int& states) {
            textures_[type] = LoadTexture(std::move(filename).c_str());
            states_[type] = states;

            source_rectangles_[type] = {
                .x = 0.f, .y = 0.f,
                .width = static_cast<float>(textures_[type].width) / static_cast<float>(states),
                .height = static_cast<float>(textures_[type].height)
            };
        }

        void setTexture(const std::string& filename, const int& states) {
            textures_[type_] = LoadTexture(std::move(filename).c_str());
            states_[type_] = states;

            source_rectangles_[type_] = {
                .x = 0.f, .y = 0.f,
                .width = static_cast<float>(textures_[type_].width) / static_cast<float>(states),
                .height = static_cast<float>(textures_[type_].height)
            };
        }

        template<AnimationTypes type>
        void setFrameSpeed(const double& speed) {
            // Frame changes every 1 / speed [secs]
            frameSeed_[type] = speed;
        }

        void setFrameSpeed(const double& speed) final {
            // Frame changes every 1 / speed [secs]
            frameSeed_[type_] = speed;
        }

        [[nodiscard]] double getFrameSpeed() const final {
            return frameSeed_[type_];
        }

        void setAnimationType(const AnimationTypes& type) {
            type_ = type;
        }
        [[nodiscard]] const AnimationTypes& getAnimationType() const {
            return type_;
        }

        void update() override {
            ++state_; state_ %= states_[type_];

            source_rectangles_[type_].x =
                static_cast<float>(textures_[type_].width * state_)
                        /
                static_cast<float>(states_[type_]);
        }

        void draw() override {
            if (!visible_) return;
            const Rectangle dest_rect = {
                .x = position_.x, .y = position_.y,
                .width = static_cast<float>(textures_[type_].width) / static_cast<float>(states_[type_]),
                .height = static_cast<float>(textures_[type_].height)
            };

            DrawTexturePro(textures_[type_], source_rectangles_[type_], dest_rect,
                            Vector2{.x = 0, .y = 0}, rotation_, WHITE);
        }

        ~AnimatableTexture() override {
            std::ranges::for_each(textures_, UnloadTexture);
        };
    private:
        AnimationTypes type_{};
        int states_[6]{};
        int state_{};
        double frameSeed_[6]{}; // frameCounter[Frames] * frameSpeed[1/s] >= 60[FPS]
        Texture2D textures_[6]{};
        Rectangle source_rectangles_[6]{};

    };
}
