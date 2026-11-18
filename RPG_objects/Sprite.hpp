#pragma once
#include <algorithm>
#include <cassert>
#include <functional>
#include <string>
#include <utility>

#include "raylib.h"

#define FORCE_INLINE __attribute__((__always_inline__)) inline

namespace RPG {

    class SoloFileTexture {
    public:
        SoloFileTexture() = default;
        explicit SoloFileTexture(std::string filename) : filename_(std::move(filename)) {
            if (IsWindowReady()) {
                texture_ = LoadTexture(filename_.c_str());
            }
        }

        FORCE_INLINE void loadTexture() {
            if (!IsTextureValid(texture_)) {
                if (IsWindowReady()) {
                    texture_ = LoadTexture(filename_.c_str());
                }
            }
        }

        FORCE_INLINE void unloadTexture() const {
            if (IsTextureValid(texture_)) {
                UnloadTexture(texture_);
            }
        }

        [[nodiscard]] FORCE_INLINE bool isTextureLoaded() const {
            return IsTextureValid(texture_);
        }

        FORCE_INLINE void changeTexture(std::string filename) {
            filename_ = std::move(filename);
            unloadTexture();
            loadTexture();
        }

        virtual ~SoloFileTexture() {
            if (IsTextureValid(texture_)) {
                UnloadTexture(texture_);
            }
        };
    protected:
        Texture2D texture_{};
        std::string filename_{};
    };

    class MultipleFileTexture {

    };

}
