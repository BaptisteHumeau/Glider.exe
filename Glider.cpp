#include "Glider.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Glider::Glider(const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y)
{
    this->_useSprite = true;

    this->_xPos = WINDOW_SIZE_X / 2;
    this->_yPos = WINDOW_SIZE_Y - WINDOW_SIZE_Y / 3;
    this->_rotation = 0;
    this->_color = sf::Color::White;

    this->_originalXPos = this->_xPos;
    this->_originalYPos = this->_yPos;
    this->_originalRotation = this->_rotation;
    this->_originalColor = this->_color;

    if (!this->_textureStraight.loadFromFile("Data/Images/Glider2.png"))
    {
        std::cerr << "Error Loading Sprite. Default to triangle" << std::endl;
        this->_useSprite = false;
    }
    if (!this->_textureLeft.loadFromFile("Data/Images/Glider2TurnLeft.png"))
    {
        std::cerr << "Error Loading Sprite. Default to triangle" << std::endl;
        this->_useSprite = false;
    }
    if (!this->_textureRight.loadFromFile("Data/Images/Glider2TurnRight.png"))
    {
        std::cerr << "Error Loading Sprite. Default to triangle" << std::endl;
        this->_useSprite = false;
    }
    if (!this->_textureRight.loadFromFile("Data/Images/Glider2TurnRight.png"))
    {
        std::cerr << "Error Loading Sprite. Default to triangle" << std::endl;
        this->_useSprite = false;
    }

    this->_textureCurrent = this->_textureStraight;

    if (!this->_useSprite)
    {
        this->_color = sf::Color::White;
        this->_radius = 8;
        this->_triangle = sf::CircleShape(this->_radius, 3);
    }
}

void Glider::reset()
{
    this->_xPos = this->_originalXPos;
    this->_yPos = this->_originalYPos;
    this->_rotation = this->_originalRotation;
    this->_color = this->_originalColor;
    this->_textureCurrent = this->_textureStraight;
}

void Glider::draw(sf::RenderWindow &window)
{
    if (!this->_useSprite)
    {
        this->_triangle.setFillColor(this->_color);
        this->_triangle.setPosition(this->_xPos, this->_yPos);
        this->_triangle.setRadius(this->_radius);
        this->_triangle.setOrigin(this->_radius - 1, this->_radius - 1);
        this->_triangle.setRotation(this->_rotation);

        window.draw(this->_triangle);
    }

    else
    {
        this->_sprite = sf::Sprite(this->_textureCurrent);

        sf::Vector2f spriteCenter(this->_sprite.getLocalBounds().width / 2, this->_sprite.getLocalBounds().height / 2);

        this->_sprite.setColor(this->_color);
        this->_sprite.setOrigin(spriteCenter);
        this->_sprite.setPosition(this->_xPos, this->_yPos);
        this->_sprite.setRotation(this->_rotation);
        this->_sprite.setScale(0.05, 0.05);
        window.draw(this->_sprite);
    }
}

void Glider::updatePosition(const int DRIFT_DIRECTION, const double DRIFT_SPEED, const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y)
{
    float radians = -M_PI / 2 + this->_rotation * M_PI / 180;
    float moveX = std::cos(radians) * _forwardSpeed;
    float moveY = std::sin(radians) * _forwardSpeed;

    float newX = this->_xPos + moveX;
    float newY = this->_yPos + moveY;

    switch (DRIFT_DIRECTION) // apply drift
    {
    case 0:
        if (newX >= 0 && newX <= WINDOW_SIZE_X)
        {
            this->_xPos = newX;
        }

        if (newY >= 0 && newY <= WINDOW_SIZE_Y)
        {
            this->_yPos = newY;
        }
        break;
    case 1:
        if (newX >= 0 && newX <= WINDOW_SIZE_X)
        {
            this->_xPos = newX + DRIFT_SPEED;
        }

        if (newY >= 0 && newY <= WINDOW_SIZE_Y)
        {
            this->_yPos = newY;
        }
        break;
    case 2:
        if (newX >= 0 && newX <= WINDOW_SIZE_X)
        {
            this->_xPos = newX;
        }

        if (newY >= 0 && newY <= WINDOW_SIZE_Y)
        {
            this->_yPos = newY + DRIFT_SPEED;
        }
        break;

    default:
        break;
    }
}

void Glider::rotate(const double DIRECTION)
{
    this->_rotation += DIRECTION;
}

void Glider::getPostion(int &x, int &y)
{
    x = this->_xPos;
    y = this->_yPos;
}

void Glider::setSpeed(const double SPEED)
{
    this->_forwardSpeed = SPEED;
}

void Glider::updateTexture(const int DIRECTION)
{
    switch (DIRECTION)
    {
    case 0:
        this->_textureCurrent = this->_textureStraight;
        break;
    case 1:
        this->_textureCurrent = this->_textureRight;
        break;
    case -1:
        this->_textureCurrent = this->_textureLeft;
        break;
    default:
        break;
    }
}

void Glider::setColor(const sf::Color COLOR)
{
    this->_color = COLOR;
}