#include "instructions.h"

#include <iostream>
#include <SFML\Graphics.hpp>

Instructions::Instructions(const int WINDOW_SIZE_Y)
{
    if (!this->_textureNeutral.loadFromFile("Data/Images/Instructions2.png"))
    {
        std::cerr << "Error Loading Sprite. Default to triangle" << std::endl;
    }
    if (!this->_textureLeft.loadFromFile("Data/Images/Instructions2Left.png"))
    {
        std::cerr << "Error Loading Sprite. Default to triangle" << std::endl;
    }
    if (!this->_textureRight.loadFromFile("Data/Images/Instructions2Right.png"))
    {
        std::cerr << "Error Loading Sprite. Default to triangle" << std::endl;
    }
    if (!this->_textureDive.loadFromFile("Data/Images/Instructions2Dive.png"))
    {
        std::cerr << "Error Loading Sprite. Default to triangle" << std::endl;
    }
    if (!this->_textureDiveLeft.loadFromFile("Data/Images/Instructions2DiveLeft.png"))
    {
        std::cerr << "Error Loading Sprite. Default to triangle" << std::endl;
    }
    if (!this->_textureDiveRight.loadFromFile("Data/Images/Instructions2DiveRight.png"))
    {
        std::cerr << "Error Loading Sprite. Default to triangle" << std::endl;
    }

    this->_image.setScale(0.4, 0.4);
    this->_image.setPosition(30, WINDOW_SIZE_Y - 130);
    this->_currentTexture = this->_textureNeutral;
}

void Instructions::setTexture(const int textureNum)
{
    switch (textureNum)
    {
    case -1:
        this->_currentTexture = this->_textureLeft;
        break;
    case 1:
        this->_currentTexture = this->_textureRight;
        break;
    case 2:
        this->_currentTexture = this->_textureDive;
        break;
    case -3:
        this->_currentTexture = this->_textureDiveLeft;
        break;
    case 3:
        this->_currentTexture = this->_textureDiveRight;
        break;
    case 0:
        this->_currentTexture = this->_textureNeutral;
        break;

    default:
        break;
    }
}

void Instructions::draw(sf::RenderWindow &window)
{
    this->_image.setTexture(this->_currentTexture);
    window.draw(this->_image);
}