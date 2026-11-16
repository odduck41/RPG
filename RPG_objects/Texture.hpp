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

        virtual ~AnimatableTexture() override {
            std::ranges::for_each(textures_, UnloadTexture);
        };
    private:
        int state_{};
        std::size_t frameSeed_{};
        Texture2D textures_[4]{};
        Rectangle rectangles_[4]{};
    };
}