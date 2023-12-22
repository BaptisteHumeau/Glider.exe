#ifndef OBSTACLE_h
#define OBSTACLE_h

#include <SFML\Graphics.hpp>

class Obstacle
{
private:
    double _xPos;
    double _yPos;
    double _speed;
    int _direction;

    sf::RectangleShape _square;

public:
    /**
     * @brief Construct a new Obstacle object
     *
     * @param X_POS obstacle x coordinate
     * @param Y_POS obstacle y coordinate
     * @param SPEED obstacle speed
     * @param DIRECTION obstacle direction (1 of 4)
     */
    Obstacle(const int X_POS, const int Y_POS, const double SPEED, const int DIRECTION);

    /**
     * @brief draws obstacle object
     *
     * @param window reference to sfml window
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief updates obstacle position based on direction and speed
     *
     */
    void updatePosition();

    /**
     * @brief checks if glider has collided with obstacle
     *
     * @param X_POS glider x coordinate
     * @param Y_POS glider y coordinate
     * @return true if collision is detected
     * @return false if collision is not detected
     */
    bool checkCollision(const int X_POS, const int Y_POS) const;

    /**
     * @brief checks if obstacle is out of bounds - if true, main.cpp deletes obstacle object
     *
     * @param WINDOW_SIZE_X sfml window size
     * @param WINDOW_SIZE_Y sfml window size
     * @return true if out of bounds
     * @return false otherwise
     */
    bool isOutOfBounds(const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y);
};

/**
 * @brief helper function - Create an obstacle object with random parametrization for speed, direction, starting position
 *
 * @param WINDOW_SIZE_X sfml window size
 * @param WINDOW_SIZE_Y sfml window size
 * @param SPEED_MIN minimum value of possible speed range
 * @param SPEED_MAX maximum value of possible speed range
 * @return Obstacle object
 */
Obstacle createRandomObstacle(const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y, const int SPEED_MIN, const int SPEED_MAX);

#endif