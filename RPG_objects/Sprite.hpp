#pragma once

#include "Textures.hpp"

namespace RPG {

    class Sprite {
    public:
        Sprite() = default;
        explicit Sprite(Rectangle texture_rect)
            : source_rectangle_(std::move(texture_rect)) {}

        explicit Sprite(Vector2 pos)
            : position_(std::move(pos)) {}

        explicit Sprite(Rectangle texture_rect, Vector2 pos)
            : position_(std::move(pos)), source_rectangle_(std::move(texture_rect)) {}

        template<class T = std::map<std::string, Texture2D>> requires TexturesStorageType<T>
        explicit Sprite(const MultipleFileTexture<T>& texture) {
            texture_data_ = new MultipleFileTexture<T>(texture);
        }

        explicit Sprite(const SoloFileTexture& texture) {
            texture_data_ = new SoloFileTexture(texture);
        }

        FORCE_INLINE void show() {visible_ = true;}
        FORCE_INLINE void hide() {visible_ = false;}

        FORCE_INLINE void setPosition(const Vector2& pos) {
            position_ = pos;
        }
        [[nodiscard]] FORCE_INLINE const Vector2& getPosition() const {
            return position_;
        }

        FORCE_INLINE void setScaling(const Vector2& scaling) {
            scaling_ = scaling;
        }
        [[nodiscard]] FORCE_INLINE const Vector2& getScaling() const {
            return scaling_;
        }

        FORCE_INLINE void setRotation(const double& rotation) {
            rotation_ = rotation;
        }
        [[nodiscard]] FORCE_INLINE const double& getRotation() const {
            return rotation_;
        }

        FORCE_INLINE void setSourceRectangle(Rectangle rectangle) {
            source_rectangle_ = std::move(rectangle);
        }

        [[nodiscard]] FORCE_INLINE const Rectangle& getSourceRectangle() const {
            return source_rectangle_;
        }


        FORCE_INLINE virtual void update() = 0;
        FORCE_INLINE virtual void draw() = 0;
        FORCE_INLINE virtual ~Sprite() {
            delete texture_data_;
        };
    protected:
        Vector2 position_{};
        Vector2 scaling_{.x = 1.f, .y = 1.f};
        float rotation_{0.f};
        bool visible_{true};
        TextureData* texture_data_{};
        Rectangle source_rectangle_{};
    };

    class TextureAnimation {
    public:
        explicit TextureAnimation(const int& fA = 0, const double& fS = 0., std::function<void()> cb = nullptr)
            : framesAmount_(fA), frameSpeed_(fS), callback_(std::move(cb)) {}

        friend class AnimatableSprite;
    private:
        int framesAmount_{};
        double frameSpeed_{}; // FPS
        std::function<void()> callback_{};
    };

    class AnimatableSprite : public Sprite {
    public:
    private:

    };
}
