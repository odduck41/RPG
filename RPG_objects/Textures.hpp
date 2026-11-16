#pragma once
#include <algorithm>
#include <string>

#include "raylib.h"

namespace RPG {
    class RPGTexture {
    public:
        RPGTexture() = default;
        void show() {visible = true;}
        void hide() {visible = false;}

        virtual void update() = 0;
        virtual ~RPGTexture() = default;
    private:
        bool visible{true};
    };

    enum AnimationTypes {
        Still = 0,
        Attack = 1,
        Eating = 2,
        Fishing = 3
    };

    class AnimatableTexture : public RPGTexture {
    public:
        AnimatableTexture() = default;

        template<AnimationTypes type>
        void setTexture(std::string filename, const Rectangle& rect) {
            textures_[type] = LoadTexture(std::move(filename).c_str());
            rectangles_[type] = rect;
        }

        void setTexture(std::string filename, const Rectangle& rect) {
            textures_[type_] = LoadTexture(std::move(filename).c_str());
            rectangles_[type_] = rect;
        }

        template<AnimationTypes type>
        void setFrameSpeed(const std::size_t& speed) {
            frameSeed_[type] = speed;
        }

        void setFrameSpeed(const std::size_t& speed) {
            frameSeed_[type_] = speed;
        }

        std::size_t getFrameSpeed() const {
            return frameSeed_[type_];
        }

        void setAnimationType(const AnimationTypes& type) {
            type_ = type;
        }
        [[nodiscard]] AnimationTypes getAnimationType() const {
            return type_;
        }

        virtual void update() override {
            ++state_; state_ %= states_[type_];
            rectangles_[type_].x = state_ * textures_[type_].width / states_[type_];
        }

        virtual ~AnimatableTexture() override {
            std::ranges::for_each(textures_, UnloadTexture);
        };
    private:
        AnimationTypes type_{};
        int states_[4]{};
        int state_{};
        std::size_t frameSeed_[4]{};
        Texture2D textures_[4]{};
        Rectangle rectangles_[4]{};
    };
}