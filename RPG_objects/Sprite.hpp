#pragma once

#include <begin_code.h>

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


        FORCE_INLINE virtual void update() = 0;
        FORCE_INLINE virtual void draw() = 0;
        FORCE_INLINE virtual ~Sprite() = default;
    protected:
        bool visible_{true};
        Vector2 position_{};
        Vector2 scaling_{.x = 1., .y = 1.};
        double rotation_{0};
        TextureData* texture_data_{};
        Rectangle source_rectangle_{};
    };


}
