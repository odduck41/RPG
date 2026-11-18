#pragma once
#include <algorithm>
#include <cassert>
#include <functional>
#include <map>
#include <string>
#include <utility>

#include "raylib.h"

#define FORCE_INLINE __attribute__((__always_inline__)) __inline__

namespace RPG {

    class TextureData {
    public:
        TextureData() = default;
        explicit TextureData(std::string data) : data_(std::move(data)) {}

        FORCE_INLINE virtual void loadTexture() = 0;
        FORCE_INLINE virtual void unloadTexture() = 0;
        [[nodiscard]] FORCE_INLINE virtual bool isTextureLoaded() const = 0;

        virtual ~TextureData() = default;
    protected:
        FORCE_INLINE void _changeTextureData(std::string data) {
            data_ = std::move(data);
        }
        std::string data_{};
    };

    class SoloFileTexture : public TextureData {
    public:
        SoloFileTexture() = default;
        explicit SoloFileTexture(std::string data) : TextureData(std::move(data)) {}

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

        [[nodiscard]] FORCE_INLINE Texture2D& getTexture() {
            return texture_;
        }

        [[nodiscard]] FORCE_INLINE const Texture2D& getTexture() const {
            return texture_;
        }


        ~SoloFileTexture() override {
            if (SoloFileTexture::isTextureLoaded())
                SoloFileTexture::unloadTexture();
        }
    private:
        Texture2D texture_{};
    };

    template <typename T>
    concept TexturesStorageType = std::same_as<std::remove_cvref_t<T>, std::map<std::string, Texture2D>> or
            std::same_as<std::remove_cvref_t<T>, std::vector<Texture2D>> or
            std::same_as<std::remove_cvref_t<T>, std::unordered_map<std::string, Texture2D>>;

    template<typename Textures = std::map<std::string, Texture2D>> requires TexturesStorageType<Textures>
    class MultipleFileTexture : public TextureData {
    public:
        MultipleFileTexture() = default;
        explicit MultipleFileTexture(std::string data) : TextureData(std::move(data)) {}

        FORCE_INLINE void loadTexture() override {
            if (!IsWindowReady()) return;

            if constexpr (std::same_as<Textures, std::vector<Texture2D>>) {
                std::string filename;
                for (std::size_t i = 0; i < data_.size(); ++i) {
                    if (data_[i] == '\0') {
                        textures_.push_back(LoadTexture(filename.c_str()));
                        filename.clear();
                    } else {
                        filename += data_[i];
                    }
                }
            } else {
                std::string filename;
                for (std::size_t i = 0; i < data_.size(); ++i) {
                    if (data_[i] == '\0') {
                        textures_[std::to_string(i)] = LoadTexture(filename.c_str());
                        filename.clear();
                    } else {
                        filename += data_[i];
                    }
                }
            }
        }

        FORCE_INLINE void loadTextures(const std::vector<std::string>& names) {
            if (!IsWindowReady()) return;
            if constexpr (std::same_as<Textures, std::vector<Texture2D>>) {
                return;
            } else {
                std::string filename;
                for (std::size_t i = 0; i < data_.size(); ++i) {
                    if (data_[i] == '\0') {
                        textures_[names[i]] = LoadTexture(filename.c_str());
                        filename.clear();
                    } else {
                        filename += data_[i];
                    }
                }
            }
        }

        FORCE_INLINE void changeTextures(const std::vector<std::string>& names, std::string data) {
            unloadTexture();
            data_ = std::move(data);
            loadTextures(names);
        }

        FORCE_INLINE void changeTextures(const std::map<std::string, Texture2D>& textures) {
            unloadTexture();
            textures_ = textures;
        }

        FORCE_INLINE void changeTextures(const std::map<std::string, std::string>& textures) {
            unloadTexture();
            textures_.clear();
            for (auto& [f, s]: textures) {
                textures_[f] = LoadTexture(s.c_str());
            }
        }


        [[nodiscard]] FORCE_INLINE Textures& getTextures() {
            return textures_;
        }

        [[nodiscard]] FORCE_INLINE const Textures& getTextures() const {
            return textures_;
        }



        FORCE_INLINE void unloadTexture() override {
            if constexpr (std::same_as<Textures, std::vector<Texture2D>>) {
                std::for_each(textures_.begin(), textures_.end(), UnloadTexture);
            } else {
                std::for_each(textures_.begin(), textures_.end(), [](const auto& p) {
                    UnloadTexture(p.second);
                });
            }
        }

        [[nodiscard]] FORCE_INLINE bool isTextureLoaded() const override {
            if constexpr (std::same_as<Textures, std::vector<Texture2D>>) {
                return IsTextureValid(*textures_.begin());
            } else {
                return IsTextureValid(textures_.begin()->second);
            }
        }

        ~MultipleFileTexture() override {
            if (MultipleFileTexture::isTextureLoaded())
                MultipleFileTexture::unloadTexture();
        }
    private:
        Textures textures_{};
    };
}
