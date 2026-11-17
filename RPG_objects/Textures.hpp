#pragma once
#include <algorithm>
#include <cassert>
#include <functional>
#include <string>

#include "raylib.h"

namespace RPG {

    enum AnimationTypes {
        Idle,
        Walking,
        Running,
        Attack,
        Damaged,
        Dying,
        Eating,
        Fishing,
        Jump
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
        virtual ~RPGTexture() = default;
    protected:
        bool visible_{true};
        Vector2 position_{};
        Vector2 scaling_{1., 1.};
        double rotation_{0};
    };



    class AnimatableTexture : public RPGTexture {
    public:
        AnimatableTexture() = default;

        AnimatableTexture(const std::string& filename, const Rectangle& rect, int states = 0, const AnimationTypes type = Idle, const bool cycled = false) {
            type_ = type;
            setTexture(filename, rect);
            if (states == 0) {
                states = textures_[type].width / static_cast<int>(rect.width);
            }
            stateAmounts_[type] = states;
            cycled_[type] = cycled;
        }

        AnimatableTexture(const std::string& filename, const Rectangle& rect, const AnimationTypes type = Idle, int states = 0, const bool cycled = false) {
            type_ = type;
            setTexture(filename, rect);
            if (states == 0) {
                states = textures_[type].width / static_cast<int>(rect.width);
            }
            stateAmounts_[type] = states;
            cycled_[type] = cycled;
        }

        AnimatableTexture(const std::string& filename, const int& states, const AnimationTypes type = Idle, const bool cycled = false) {
            type_ = type;
            setTexture(filename, states);
            cycled_[type] = cycled;
        }




        template<AnimationTypes type>
        void setTexture(const std::string& filename, const Rectangle& rect, const bool cycled = false) {
            textures_[type] = LoadTexture(std::move(filename).c_str());
            source_rectangles_[type] = rect;
            stateAmounts_[type] = textures_[type].width / static_cast<int>(rect.width);

            cycled_[type] = cycled;
        }

        void setTexture(const std::string& filename, const Rectangle& rect, const bool cycled = false) {
            textures_[type_] = LoadTexture(std::move(filename).c_str());
            source_rectangles_[type_] = rect;
            stateAmounts_[type_] = textures_[type_].width / static_cast<int>(rect.width);

            cycled_[type_] = cycled;
        }

        template<AnimationTypes type>
        void setTexture(const std::string& filename, const Rectangle& rect, const int& amount, const bool cycled = false) {
            textures_[type] = LoadTexture(std::move(filename).c_str());
            source_rectangles_[type] = rect;
            stateAmounts_[type] = amount;

            cycled_[type] = cycled;
        }

        void setTexture(const std::string& filename, const Rectangle& rect, const int& amount, const bool cycled = false) {
            textures_[type_] = LoadTexture(std::move(filename).c_str());
            source_rectangles_[type_] = rect;
            stateAmounts_[type_] = amount;

            cycled_[type_] = cycled;
        }


        template<AnimationTypes type>
        void setTexture(const std::string& filename, const int& amount, const bool cycled = false) {
            textures_[type] = LoadTexture(std::move(filename).c_str());
            stateAmounts_[type] = amount;

            assert(textures_[type].width % amount == 0 && "MISMATCHING TEXTURE SIZE");

            source_rectangles_[type] = {
                .x = 0.f, .y = 0.f,
                .width = static_cast<float>(textures_[type].width) / static_cast<float>(amount),
                .height = static_cast<float>(textures_[type].height)
            };

            cycled_[type] = cycled;
        }

        void setTexture(const std::string& filename, const int& amount, const bool cycled = false) {
            textures_[type_] = LoadTexture(std::move(filename).c_str());
            stateAmounts_[type_] = amount;

            assert(textures_[type_].width % amount == 0 && "MISMATCHING TEXTURE SIZE");

            source_rectangles_[type_] = {
                .x = 0.f, .y = 0.f,
                .width = static_cast<float>(textures_[type_].width) / static_cast<float>(amount),
                .height = static_cast<float>(textures_[type_].height)
            };

            cycled_[type_] = cycled;
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
            if (type_ == type) {
                finished_ = false;
                return;
            }
            type_ = type;
            actualState_ = 0;
            frameCounter_ = 0;
            finished_ = false;
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



        template<AnimationTypes type>
        void setBeforeAnimation(const std::function<void()>& func) {
            functionsBefore_[type] = func;
        }

        void setBeforeAnimation(const std::function<void()>& func) {
            functionsBefore_[type_] = func;
        }

        template<AnimationTypes type>
        void setAfterAnimation(const std::function<void()>& func) {
            functionsAfter_[type] = func;
        }

        void setAfterAnimation(const std::function<void()>& func) {
            functionsAfter_[type_] = func;
        }



        [[nodiscard]] bool isFinished() const {
            return finished_;
        }

        void update() override {
            if (frameSpeed_[type_] == 0) frameSpeed_[type_] = 1.5 * stateAmounts_[type_];
            if (frameCounter_ * frameSpeed_[type_] < 60) return;
            frameCounter_ = 0;
            if (finished_ && !cycled_[type_]) return;
            ++actualState_;
            actualState_ %= stateAmounts_[type_];
            if (actualState_ == 0) {
                finished_ = true;
            } else {
                finished_ = false;
            }

            source_rectangles_[type_].x =
                static_cast<float>(actualState_) * source_rectangles_[type_].width;
        }

        void draw() override {
            if (!visible_) return;
            const Rectangle dest_rect = {
                .x = position_.x, .y = position_.y,
                .width = (source_rectangles_[type_].width * scaling_.x),
                .height = (source_rectangles_[type_].height * scaling_.y)
            };

            // DrawRectangleRec(dest_rect, GREEN);
            auto source_rect = source_rectangles_[type_];

            source_rect.height *= scaling_.x / fabs(scaling_.x);
            source_rect.width *= scaling_.y / fabs(scaling_.y);

            if (functionsBefore_[type_] != nullptr) functionsBefore_[type_]();
            DrawTexturePro(textures_[type_], source_rect, dest_rect,
                            Vector2{.x = 0, .y = 0}, static_cast<float>(rotation_), WHITE);
            if (functionsAfter_[type_] != nullptr) functionsAfter_[type_]();

            ++frameCounter_;
        }

        ~AnimatableTexture() override {
            std::ranges::for_each(textures_, UnloadTexture);
        };
    private:
        AnimationTypes type_{};
        int stateAmounts_[9]{};
        int actualState_{};
        double frameSpeed_[9]{}; // frameCounter[Frames] * frameSpeed[1/s] >= 60[FPS]
        int frameCounter_{0};
        Texture2D textures_[9]{};
        Rectangle source_rectangles_[9]{};
        std::function<void()> functionsBefore_[9]{};
        std::function<void()> functionsAfter_[9]{};
        bool finished_{};
        bool cycled_[9]{};
    };
}
