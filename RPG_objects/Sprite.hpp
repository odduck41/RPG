#pragma once

#include <cassert>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <unordered_set>

#include "raylib.h"

namespace RPG {

    struct File {
        std::string path{};
        unsigned int sheet_width{};
        unsigned int sheet_height{};
    };

    struct TextureAnimation {
        std::string alias{};
        unsigned int frameAmount{};
        double frameSpeed{};
        bool cycled{};
    };

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

        void setRotation(const float& rotation) {
            rotation_ = rotation;
        }

        [[nodiscard]] const float& getRotation() const {
            return rotation_;
        }

        virtual void addFile(const std::string&, const File&) = 0;
        virtual void addFile(const File&) = 0;
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual ~Sprite() = default;
    protected:
        Vector2 position_{};
        Vector2 scaling_{.x = 1.f, .y = 1.f};
        float rotation_{0.f};
        bool visible_{true};
    };

    class AnimatableSprite : public Sprite {
    public:
        AnimatableSprite() = default;

        void addFile(const std::string& file_alias, const File& file) final {
            if (file_paths_.contains(file.path)) return;
            if (file_info_.contains(file_alias))
                throw std::runtime_error("Trying to write 2 different files with one alias");

            file_paths_.insert(file.path);

            file_info_[file_alias].file = file;
            file_info_[file_alias].texture = LoadTexture(file.path.c_str());

            assert(file_info_[file_alias].texture.width % file.sheet_width == 0 && "File width should divide sprite width!");
            assert(file_info_[file_alias].texture.height % file.sheet_height == 0 && "File height should divide sprite height!");

            file_info_[file_alias].free_sheets.resize(file_info_[file_alias].texture.height / file.sheet_height, false);
        }

        void addFile(const File&) final {
            throw std::runtime_error("Empty file_alias for animation!");
        }

        virtual void update() {}
        virtual void draw() {}

    private:
        std::unordered_set<std::string> file_paths_{};
        struct FileInfo_ {
            File file{};
            Texture2D texture{};
            std::vector<bool> free_sheets{};
            int current_sheet{};
        };
        std::map<std::string, FileInfo_> file_info_{};
    };
}