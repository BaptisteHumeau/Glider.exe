#include "Obstacle.h"

#include <SFML\Graphics.hpp>
#include <cstdlib>

Obstacle::Obstacle(const int X_POS, const int Y_POS, const double SPEED, const int DIRECTION)
{
    this->_speed = SPEED;
    this->_xPos = X_POS;
    this->_yPos = Y_POS;
    this->_direction = DIRECTION;
    this->_square.setSize(sf::Vector2f(10, 10));
    this->_square.setOrigin(sf::Vector2f(5, 5));
}

void Obstacle::updatePosition()
{
    switch (this->_direction)
    {
    case 0:
        this->_yPos += this->_speed;
        break;
    case 1:
        this->_xPos += this->_speed;
        break;

    default:
        break;
    }
}

void Obstacle::draw(sf::RenderWindow &window)
{
    this->_square.setPosition(this->_xPos, this->_yPos);
    window.draw(this->_square);
}

bool Obstacle::checkCollision(const int X_POS, const int Y_POS) const
{
    const int collisionRange = 6;

    if ((X_POS >= this->_xPos - collisionRange && X_POS <= this->_xPos + collisionRange) &&
        (Y_POS >= this->_yPos - collisionRange && Y_POS <= this->_yPos + collisionRange))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Obstacle::isOutOfBounds(const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y)
{
    if (this->_xPos < 0 || this->_xPos > WINDOW_SIZE_X || this->_yPos < 0 || this->_yPos > WINDOW_SIZE_Y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Obstacle createRandomObstacle(const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y, const int SPEED_MIN, const int SPEED_MAX)
{
    double speed = rand() / (double)RAND_MAX * (SPEED_MAX - SPEED_MIN) + SPEED_MIN;

    const int CHOICE = rand() % 4;
    int y, x, direction;

    switch (CHOICE)
    {
    case 0:
        x = rand() % WINDOW_SIZE_X;
        y = 10;
        direction = 0;
        break;
    case 1:
        x = rand() % WINDOW_SIZE_X;
        y = WINDOW_SIZE_Y - 10;
        speed = -speed;
        direction = 0;
        break;
    case 2:
        x = 10;
        y = rand() % WINDOW_SIZE_Y;
        direction = 1;
        break;
    case 3:
        x = WINDOW_SIZE_X - 10;
        y = rand() % WINDOW_SIZE_Y;
        speed = -speed;
        direction = 1;
        break;

    default:
        break;
    }

    Obstacle obs(x, y, speed, direction);

    return obs;
}
