#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <SFML\Graphics.hpp>

class Instructions
{
private:
    sf::Texture _currentTexture;
    sf::Texture _textureNeutral;
    sf::Texture _textureLeft;
    sf::Texture _textureRight;
    sf::Texture _textureDive;
    sf::Texture _textureDiveLeft;
    sf::Texture _textureDiveRight;
    sf::Sprite _image;

public:
    /**
     * @brief Construct a new Instructions object
     *
     * @param WINDOW_SIZE_Y sfml window size for positioning
     */
    Instructions(const int WINDOW_SIZE_Y);

    /**
     * @brief Set the sprite texture - matches current user action
     *
     * @param textureNum number related to texture id
     */
    void setTexture(const int textureNum);

    /**
     * @brief draws the instruction object
     *
     * @param window sfml window reference
     */
    void draw(sf::RenderWindow &window);
};

#endif