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
        [[nodiscard]] FORCE_INLINE virtual bool isTextureLoaded() const = 0;

        virtual ~TextureData() = 0;
    protected:
        FORCE_INLINE void _changeTextureData(std::string data) {
            data_ = std::move(data);
        }
        std::string data_{};
    };

    class SoloFileTexture : public TextureData {
    public:
        SoloFileTexture() = default;
        explicit SoloFileTexture(std::string data) : TextureData(std::move(data)) {
            if (IsWindowReady()) {
                texture_ = LoadTexture(data_.c_str());
            }
        }

        FORCE_INLINE void changeTexture(const std::string& filename) {
            _changeTextureData(filename);
            if (isTextureLoaded()) {
                unloadTexture();
                loadTexture();
            } else {
                loadTexture();
            }
        }

        FORCE_INLINE void loadTexture() override {
            if (IsWindowReady()) {
                texture_ = LoadTexture(data_.c_str());
            }
        }

        FORCE_INLINE void unloadTexture() override {
            if (IsTextureValid(texture_)) {
                UnloadTexture(texture_);
            }
        }

        [[nodiscard]] FORCE_INLINE bool isTextureLoaded() const override {
            return IsTextureValid(texture_);
        }

    private:
        Texture2D texture_{};
    };
}
