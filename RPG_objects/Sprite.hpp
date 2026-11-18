#pragma once
#include <algorithm>
#include <cassert>
#include <functional>
#include <string>
#include <utility>

#include "raylib.h"

#define FORCE_INLINE __attribute__((__always_inline__)) inline

namespace RPG {

    class TextureData {
    public:
        TextureData() = default;
        explicit TextureData(std::string data) : data_(std::move(data)) {}

        FORCE_INLINE virtual void loadTexture() = 0;
        FORCE_INLINE virtual void unloadTexture() = 0;
        FORCE_INLINE virtual bool isTextureLoaded() = 0;

        virtual ~TextureData() = 0;
    protected:
        FORCE_INLINE void _changeTextureData(std::string data) {
            data_ = std::move(data);
        }
        std::string data_{};
    };

}
