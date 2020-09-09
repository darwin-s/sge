// Copyright 2020 Dan Sirbu
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SGE_SPRITE_HPP
#define SGE_SPRITE_HPP

#include <SGE/Export.hpp>
#include <SGE/Texture.hpp>
#include <SGE/Drawable.hpp>
#include <SGE/Transformable.hpp>
#include <SGE/Vertex.hpp>
#include <SGE/Rectangle.hpp>
#include <glm/vec2.hpp>
#include <array>

namespace sge {
/**
 * \brief Sprite object
 *
 *
 * This object represents a sprite. A sprite is a quad which may have a texture,
 * and which can be moved freely. The size of the quad and it's texture coordinates
 * are separate, which means that if the texture is square, but the sprite is not,
 * then the texture may appear stretched, however this approach allows more
 * freedom for the user. The quad of the sprite represents a square with (0, 0)
 * as it's top left corner. The rest of the corners are defined by it's model size
 * (x = width, y = height of the square). The texture rectangle of the sprite is
 * a rectangle, where (0, 0) is the top left corner of the texture and (1, 1) is
 * the bottom right corner. A sprite can also be tinted with any color, which will
 * mix it's texture with the specified tint color.
 * Usage example:
 * \code
 * auto texture = std::make_shared<sge::Texture>("texture.png");
 * sge::Sprite character(texture);
 * //In the rendering loop
 * renderTarget.draw(character);
 * \endcode
 */
class SGE_API Sprite : public Drawable, public Transformable {
public:
    /**
     * \brief Create sprite
     *
     *
     * Creates a sprite from the specified parameters.
     * \param texture Pointer to texture to be used (can be nullptr to have no texture)
     * \param textureRect Texture rectangle to use (values from 0.0f to 1.0f)
     * \param size Model size of the sprite quad
     */
    explicit Sprite(std::shared_ptr<Texture> texture = nullptr,
                    const RectangleFloat& textureRect =
                        RectangleFloat(0.0f, 0.0f, 1.0f, 1.0f),
                    const glm::vec2& size = glm::vec2(1.0f, 1.0f));

    /**
     * \brief Set sprite texture
     * \param texture Pointer to texture (can be nullptr)
     */
    void setTexture(std::shared_ptr<Texture> texture);

    /**
     * \brief Set texture rectangle
     * \param textureRect Rectangle describing the texture coordinates
     */
    void setTextureRectangle(const RectangleFloat& textureRect);

    /**
     * \brief Set sprite tinting
     * \param tintColor Color to tint the sprite with
     */
    void setTint(const Color& tintColor);

    /**
     * \brief Set sprite model size
     * \param w Width of the model
     * \param h Height of the model
     */
    void setModelSize(float w, float h);

    /**
     * \brief Set sprite model size
     * \param size Size of the sprite model
     */
    void setModelSize(const glm::vec2& size);

    /**
     * \brief Get sprite texture
     * \return Pointer to the texture used by the sprite
     */
    [[nodiscard]] std::shared_ptr<Texture> getTexture() const;

    /**
     * \brief Get texture rectangle
     * \return Rectangle describing the texture coordinates used
     */
    [[nodiscard]] const RectangleFloat& getTextureRectangle() const;

    /**
     * \brief Get sprite tint color
     * \return Tint color of the sprite
     */
    [[nodiscard]] const Color& getTint() const;

    /**
     * \brief Get the bounds of the sprite model
     * \return Rectangle describing the sprite bounds in model space
     */
    [[nodiscard]] RectangleFloat getModelBounds() const;

    /**
     * \brief Get the bounds of the sprite
     * \return Rectangle describing the sprite bounds in world space
     */
    [[nodiscard]] RectangleFloat getWorldBounds() const;

protected:
    void draw(RenderTarget& target, RenderState renderState) const override;

private:
    std::shared_ptr<Texture> m_tex;
    std::array<Vertex, 4> m_vertices;
    RectangleFloat m_textureRect;
};
}

#endif//SGE_SPRITE_HPP
