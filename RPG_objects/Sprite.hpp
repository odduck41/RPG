#pragma once

#include <functional>
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
        FORCE_INLINE Frame() = default;
        FORCE_INLINE Frame(const Rectangle& source, const Rectangle& dest) :
            sourceRect_(source), destRect_(dest) {}

        FORCE_INLINE void setSourceRectangle(const Rectangle& s_rct) {
            sourceRect_ = s_rct;
        }
        [[nodiscard]] FORCE_INLINE const Rectangle& getSourceRectangle() const { return sourceRect_; }

        FORCE_INLINE void setDestinationRectangle(const Rectangle& d_rct) {
            destRect_ = d_rct;
        }
        [[nodiscard]] FORCE_INLINE const Rectangle& getDestinationRectangle() const { return destRect_; }

        FORCE_INLINE void setScaling(const Vector2& scaling) {
            scaling_ = scaling;
        }
        [[nodiscard]] FORCE_INLINE const Vector2& getScaling() const { return scaling_; }

        FORCE_INLINE void setOrigin(const Vector2& origin) {
            origin_ = origin;
        }
        [[nodiscard]] FORCE_INLINE const Vector2& getOrigin() const { return origin_; }

        FORCE_INLINE void setRotation(const float& rotation) {
            rotation_ = rotation;
        }
        [[nodiscard]] FORCE_INLINE const float& getRotation() const { return rotation_; }

        FORCE_INLINE void setStaticAnimation(const std::function<void(Frame&)>& func) {
            animation_ = func;
        }

        FORCE_INLINE void startStaticAnimation() {
            started = true;
        }

        FORCE_INLINE void stopStaticAnimation() {
            started = false;
        }

        FORCE_INLINE void update() {
            if (started && animation_ != nullptr) animation_(*this);
        }

        FORCE_INLINE void draw(const Texture& texture) const {
            auto destRect = destRect_;
            destRect.height *= scaling_.x;
            destRect.width *= scaling_.y;

            DrawTexturePro(texture, sourceRect_, destRect, origin_, rotation_, WHITE);
        }

    private:
        Rectangle sourceRect_{};
        Rectangle destRect_{};

        Vector2 scaling_{.x = 1.f, .y = 1.f};
        Vector2 origin_{.x = 0.f, .y = 0.f};
        float rotation_{0.f};

        std::function<void(Frame&)> animation_{};
        bool started = false;
    };

    class Sprite {
    public:
        FORCE_INLINE Sprite() = default;

        FORCE_INLINE void setSourceRectangle(const Rectangle& s_rct) {
            frame_.setSourceRectangle(s_rct);
        }
        [[nodiscard]] FORCE_INLINE const Rectangle& getSourceRectangle() const {
            return frame_.getSourceRectangle();
        }

        FORCE_INLINE void setDestinationRectangle(const Rectangle& d_rct) {
            frame_.setDestinationRectangle(d_rct);
        }
        [[nodiscard]] FORCE_INLINE const Rectangle& getDestinationRectangle() const {
            return frame_.getDestinationRectangle();
        }

        FORCE_INLINE void setScaling(const Vector2& scaling) {
            frame_.setScaling(scaling);
        }
        [[nodiscard]] FORCE_INLINE const Vector2& getScaling() const {
            return frame_.getScaling();
        }

        FORCE_INLINE void setOrigin(const Vector2& origin) {
            frame_.setOrigin(origin);
        }
        [[nodiscard]] FORCE_INLINE const Vector2& getOrigin() const {
            return frame_.getOrigin();
        }

        FORCE_INLINE void setRotation(const float& rotation) {
            frame_.setRotation(rotation);
        }
        [[nodiscard]] FORCE_INLINE const float& getRotation() const {
            return frame_.getRotation();
        }

        FORCE_INLINE virtual void update() = 0;
        FORCE_INLINE virtual void draw() = 0;
        FORCE_INLINE virtual ~Sprite() = default;
    protected:
        Frame frame_;
    };

    class StaticSprite final : public Sprite {
    public:
        FORCE_INLINE StaticSprite() = default;
        FORCE_INLINE explicit StaticSprite(const std::string& filename) :
            texture_(LoadTexture(std::move(filename).c_str())) {}

        FORCE_INLINE void update() override {
            frame_.update();
        }

        FORCE_INLINE void setTexture(const std::string& filename) {
            if (IsTextureValid(texture_)) UnloadTexture(texture_);
            texture_ = LoadTexture(std::move(filename).c_str());
        }

        FORCE_INLINE void draw() override {
            frame_.draw(texture_);
        }

        FORCE_INLINE ~StaticSprite() override {
            if (IsTextureValid(texture_)) UnloadTexture(texture_);
        }
    private:
        Texture texture_{};
    };


    class AnimTime {
    public:
        FORCE_INLINE AnimTime() = default;
        FORCE_INLINE virtual bool shouldUpdate(const std::size_t&) = 0;
        FORCE_INLINE virtual ~AnimTime() = default;
    protected:
        std::chrono::milliseconds last_{};
    };

    class AnimSpeed final : public AnimTime {
    public:
        FORCE_INLINE AnimSpeed() = default;
        FORCE_INLINE explicit AnimSpeed(const float& t) : duration_(t) {};

        FORCE_INLINE void setDuration(const float& duration) {
            duration_ = duration;
        }
        [[nodiscard]] FORCE_INLINE const float& getDuration() const {
            return duration_;
        }

        FORCE_INLINE bool shouldUpdate(const std::size_t&) override {
            const auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()
            );

            if (static_cast<float>((now - last_).count()) * duration_ >= 1000.f) {
                last_ = now;
                return true;
            }
            return false;
        };

        FORCE_INLINE ~AnimSpeed() override = default;
    private:
        float duration_{};
    };


    struct TextureAnimation {
        float width{};
        float height{};
        std::size_t framesAmount{};

        bool cycled{true};
        bool asksFinishing{false};
    };

    class AnimatableSprite final : public Sprite {
    public:
        FORCE_INLINE AnimatableSprite() = default;

        FORCE_INLINE void addFile(const std::string& fileAlias, const std::string& file) {
            files_[fileAlias].texture = LoadTexture(file.c_str());
        }

        template<typename Updater = AnimSpeed> requires std::is_base_of_v<AnimTime, Updater>
        FORCE_INLINE void addAnimation(const std::string& fileAlias, const std::size_t& index,
            const std::string& animationAlias, const TextureAnimation& animation, const Updater& upd) {
            animations_[animationAlias].animation = animation;
            animations_[animationAlias].fileAlias = fileAlias;
            animations_[animationAlias].index = index;
            updater_[animationAlias] = new Updater(upd);
        }

        FORCE_INLINE void setAnimation(const std::string& animationAlias) {
            currentAnimationAlias_ = animationAlias;
            frame_.setSourceRectangle({
                0,
                animations_[currentAnimationAlias_].animation.height *
                                animations_[currentAnimationAlias_].index,
                animations_[currentAnimationAlias_].animation.width,
                animations_[currentAnimationAlias_].animation.height
            });

            frame_.setDestinationRectangle({
                0,
                0,
                animations_[currentAnimationAlias_].animation.width,
                animations_[currentAnimationAlias_].animation.height
            });
        }

        FORCE_INLINE void update() override {
            if (updater_[currentAnimationAlias_]->shouldUpdate(animations_[currentAnimationAlias_].currentFrame)) {
                ++animations_[currentAnimationAlias_].currentFrame
                    %= animations_[currentAnimationAlias_].animation.framesAmount;

                auto source = frame_.getSourceRectangle();
                source.x = source.width * animations_[currentAnimationAlias_].currentFrame;
                frame_.setSourceRectangle(source);
            }
            frame_.update();
        }

        FORCE_INLINE void draw() override {
            frame_.draw(files_[animations_[currentAnimationAlias_].fileAlias].texture);
        }

        FORCE_INLINE ~AnimatableSprite() override = default;
    private:
        struct TextureFile {
            Texture texture{};
        };

        struct TextureAnimationInfo {
            std::string fileAlias{};
            std::size_t index{};
            std::size_t currentFrame{};
            TextureAnimation animation{};
        };


        std::string currentAnimationAlias_{};
        std::unordered_map<std::string, TextureFile> files_;
        std::unordered_map<std::string, TextureAnimationInfo> animations_;
        std::unordered_map<std::string, AnimTime*> updater_{};
    };
}