#pragma once
#include <algorithm>
#include <cassert>
#include <string>

#include "raylib.h"

namespace RPG {

    enum AnimationTypes {
        Idle,
        Walking,
        Running,
        Attack,
        Eating,
        Fishing
    };



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


        virtual void update() = 0;
        virtual void draw() = 0;
        virtual ~RPGTexture() = default;
    protected:
        bool visible_{true};
        Vector2 position_{};
        double scaling_{1};
        double rotation_{0};
    };



    class AnimatableTexture : public RPGTexture {
    public:
        AnimatableTexture() = default;

        AnimatableTexture(const std::string& filename, const Rectangle& rect, int states = 0, const AnimationTypes type = Idle) {
            type_ = type;
            setTexture(filename, rect);
            if (states == 0) {
                states = textures_[type].width / static_cast<int>(rect.width);
            }
            stateAmounts_[type] = states;
        }

        AnimatableTexture(const std::string& filename, const Rectangle& rect, const AnimationTypes type = Idle, int states = 0) {
            type_ = type;
            setTexture(filename, rect);
            if (states == 0) {
                states = textures_[type].width / static_cast<int>(rect.width);
            }
            stateAmounts_[type] = states;
        }

        AnimatableTexture(const std::string& filename, const int& states, const AnimationTypes type = Idle) {
            type_ = type;
            setTexture(filename, states);
        }




        template<AnimationTypes type>
        void setTexture(const std::string& filename, const Rectangle& rect) {
            textures_[type] = LoadTexture(std::move(filename).c_str());
            source_rectangles_[type] = rect;
            stateAmounts_[type] = textures_[type].width / static_cast<int>(rect.width);
        }

        void setTexture(const std::string& filename, const Rectangle& rect) {
            textures_[type_] = LoadTexture(std::move(filename).c_str());
            source_rectangles_[type_] = rect;
            stateAmounts_[type_] = textures_[type_].width / static_cast<int>(rect.width);
        }

        template<AnimationTypes type>
        void setTexture(const std::string& filename, const int& states) {
            textures_[type] = LoadTexture(std::move(filename).c_str());
            stateAmounts_[type] = states;

            assert(textures_[type].width % states == 0 && "MISMATCHING TEXTURE SIZE");

            source_rectangles_[type] = {
                .x = 0.f, .y = 0.f,
                .width = static_cast<float>(textures_[type].width) / static_cast<float>(states),
                .height = static_cast<float>(textures_[type].height)
            };
        }

        void setTexture(const std::string& filename, const int& states) {
            textures_[type_] = LoadTexture(std::move(filename).c_str());
            stateAmounts_[type_] = states;

            assert(textures_[type_].width % states == 0 && "MISMATCHING TEXTURE SIZE");

            source_rectangles_[type_] = {
                .x = 0.f, .y = 0.f,
                .width = static_cast<float>(textures_[type_].width) / static_cast<float>(states),
                .height = static_cast<float>(textures_[type_].height)
            };
        }




        template<AnimationTypes type>
        void setFrameSpeed(const double& speed) {
            // Frame changes every 1 / speed [secs]
            frameSpeed_[type] = speed;
        }

        void setFrameSpeed(const double& speed) {
            // Frame changes every 1 / speed [secs]
            frameSpeed_[type_] = speed;
        }

        template<AnimationTypes type>
        [[nodiscard]] double getFrameSpeed() const {
            return frameSpeed_[type];
        }

        [[nodiscard]] double getFrameSpeed() const {
            return frameSpeed_[type_];
        }




        void setAnimationType(const AnimationTypes& type) {
            type_ = type;
        }

        [[nodiscard]] const AnimationTypes& getAnimationType() const {
            return type_;
        }




        template<AnimationTypes type>
        void setStatesAmount(const int& amount) {
            stateAmounts_[type] = amount;
        }

        void setStatesAmount(const int& amount) {
            stateAmounts_[type_] = amount;
        }

        template<AnimationTypes type>
        [[nodiscard]] int getStatesAmount() const {
            return stateAmounts_[type];
        }

        [[nodiscard]] int getStatesAmount() const {
            return stateAmounts_[type_];
        }


        void update() override {
            if (frameCounter_ * frameSpeed_[type_] < 60) return;
            frameCounter_ = 0;
            ++actualState_; actualState_ %= stateAmounts_[type_];

            source_rectangles_[type_].x =
                static_cast<float>(actualState_) * source_rectangles_[type_].width;
        }

        void draw() override {
            if (!visible_) return;
            const Rectangle dest_rect = {
                .x = position_.x, .y = position_.y,
                .width = static_cast<float>(source_rectangles_[type_].width * scaling_),
                .height = static_cast<float>(source_rectangles_[type_].height * scaling_)
            };

            DrawTexturePro(textures_[type_], source_rectangles_[type_], dest_rect,
                            Vector2{.x = 0, .y = 0}, static_cast<float>(rotation_), WHITE);
            ++frameCounter_;
        }

        ~AnimatableTexture() override {
            std::ranges::for_each(textures_, UnloadTexture);
        };
    private:
        AnimationTypes type_{};
        int stateAmounts_[6]{};
        int actualState_{};
        double frameSpeed_[6]{}; // frameCounter[Frames] * frameSpeed[1/s] >= 60[FPS]
        int frameCounter_{0};
        Texture2D textures_[6]{};
        Rectangle source_rectangles_[6]{};

    };
}
