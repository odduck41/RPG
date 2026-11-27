#pragma once

#include <raylib.h>
#include <type_traits>

#define FORCE_INLINE __attribute__((always_inline)) __inline__


namespace VectorOperations {
    template<class T>
    concept VectorType = std::is_same_v<Vector2, std::remove_cvref_t<T>> or
                         std::is_same_v<Vector3, std::remove_cvref_t<T>> or
                         std::is_same_v<Vector4, std::remove_cvref_t<T>>;

    template<VectorType Vector>
    FORCE_INLINE Vector& operator+=(Vector& a, const Vector& b) noexcept {
        a = Vector{
            .x = a.x + b.x, .y = a.y + b.y
        };
        if constexpr (requires {a.z;}) a.z += b.z;
        if constexpr (requires {a.w;}) a.w += b.w;
        return a;
    }

    template<VectorType Vector>
    FORCE_INLINE Vector operator+(Vector a, const Vector& b) noexcept {
        return a += b;
    }

    template<VectorType Vector>
    FORCE_INLINE Vector& operator-=(Vector& a, const Vector& b) noexcept {
        a = Vector{
            .x = a.x - b.x, .y = a.y - b.y
        };
        if constexpr (requires {a.z;}) a.z -= b.z;
        if constexpr (requires {a.w;}) a.w -= b.w;
        return a;
    }

    template<VectorType Vector>
    FORCE_INLINE Vector operator-(Vector a, const Vector& b) noexcept {
        return a -= b;
    }

    template<VectorType Vector, std::integral T>
    FORCE_INLINE Vector& operator*=(Vector& a, const T& b) {
        a.x *= static_cast<float>(b);
        a.y *= static_cast<float>(b);
        if constexpr (requires {a.z;}) a.z *= static_cast<float>(b);
        if constexpr (requires {a.w;}) a.w *= static_cast<float>(b);
        return a;
    }

    template<VectorType Vector, std::integral T>
    FORCE_INLINE Vector operator*(Vector a, const T& b) {
        return a *= b;
    }

    template<class Vector, class T> requires VectorType<Vector> and std::is_integral_v<T>
    FORCE_INLINE Vector& operator/=(Vector& a, T b) {
        a.x /= static_cast<float>(b);
        a.y /= static_cast<float>(b);
        if constexpr (requires {a.z;}) a.z /= static_cast<float>(b);
        if constexpr (requires {a.w;}) a.w /= static_cast<float>(b);
        return a;
    }

    template<class Vector, class T> requires VectorType<Vector> and std::is_integral_v<T>
    FORCE_INLINE Vector operator/(Vector a, T b) {
        return a /= b;
    }
}

namespace RPG {
    using namespace VectorOperations;

    class Frame {
    public:
        Frame() = default;
        Frame(const Rectangle& source, const Rectangle& dest) :
        sourceRect_(source), destRect_(dest) {}

        void setSourceRectangle(const Rectangle& s_rct) {
            sourceRect_ = s_rct;
        }
        [[nodiscard]] const Rectangle& getSourceRectangle() const { return sourceRect_; }

        void setDestinationRectangle(const Rectangle& d_rct) {
            destRect_ = d_rct;
        }
        [[nodiscard]] const Rectangle& getDestinationRectangle() const { return destRect_; }

        void setScaling(const Vector2& scaling) {
            scaling_ = scaling;
        }
        [[nodiscard]] const Vector2& getScaling() const { return scaling_; }

        void setOrigin(const Vector2& origin) {
            origin_ = origin;
        }
        [[nodiscard]] const Vector2& getOrigin() const { return origin_; }

        void setRotation(const float& rotation) {
            rotation_ = rotation;
        }
        [[nodiscard]] const float& getRotation() const { return rotation_; }

        void draw(const Texture& texture) const {
            auto destRect = destRect_;
            destRect.x *= scaling_.x;
            destRect.y *= scaling_.y;

            DrawTexturePro(texture, sourceRect_, destRect, origin_, rotation_, WHITE);
        }

    private:
        Rectangle sourceRect_{};
        Rectangle destRect_{};

        Vector2 scaling_{.x = 1.f, .y = 1.f};
        Vector2 origin_{.x = 0.f, .y = 0.f};
        float rotation_{0.f};
    };
}