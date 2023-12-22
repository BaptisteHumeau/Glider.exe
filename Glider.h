#ifndef GLIDER_H
#define GLIDER_H

#include <SFML\Graphics.hpp>

class Glider
{
private:
    double _xPos;
    double _yPos;
    double _rotation;
    double _forwardSpeed;
    int _radius;
    sf::CircleShape _triangle;
    sf::Color _color;

    sf::Sprite _sprite;
    sf::Texture _textureStraight;
    sf::Texture _textureLeft;
    sf::Texture _textureRight;
    sf::Texture _textureCurrent;
    bool _useSprite;

    sf::Color _originalColor;
    double _originalXPos;
    double _originalYPos;
    double _originalRotation;

public:
    /**
     * @brief Construct a new Glider object
     *
     * @param WINDOW_SIZE_X sfml window size for positioning
     * @param WINDOW_SIZE_Y sfml window size for positioning
     */
    Glider(const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y);

    /**
     * @brief Resets glider to original parameters
     *
     */
    void reset();

    /**
     * @brief Set glider speed.
     *
     * @param SPEED
     */
    void setSpeed(const double SPEED);

    /**
     * @brief Draws glider object
     *
     * @param window sfml window reference
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief updates glider position bases on speed, direction, drift
     *
     * @param DRIFT_DIRECTION drift direction - simulates wind
     * @param DRIFT drift amplitude
     * @param WINDOW_SIZE_X sfml wndow size - to keep glider within window
     * @param WINDOW_SIZE_Y sfml wndow size - to keep glider within window
     */
    void updatePosition(const int DRIFT_DIRECTION, const double DRIFT, const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y);

    /**
     * @brief rotates the glider based on turns
     *
     * @param DIRECTION angle in degrees
     */
    void rotate(const double DIRECTION);

    /**
     * @brief updates reference glider coordinates
     *
     * @param x reference to glider x coordinate
     * @param y reference to glider y coordinate
     */
    void getPostion(int &x, int &y);

    /**
     * @brief updates sprite texture based on glider turns for basic animation
     *
     * @param DIRECTION direction of turn
     */
    void updateTexture(const int DIRECTION);

    /**
     * @brief Set glider color - based on thermal strength
     *
     * @param COLOR
     */
    void setColor(const sf::Color COLOR);
};

#endif