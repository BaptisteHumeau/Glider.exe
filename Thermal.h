#ifndef THERMAL_H
#define THERMAL_H

#include <SFML\Graphics.hpp>

class Thermal
{
private:
    int _xPos;
    int _yPos;

    int _radiusInner;
    int _radiusOuter;

    double _strengthInner;
    double _strengthOuter;

    sf::CircleShape _circleInner;
    sf::CircleShape _circleOuter;

public:
    /**
     * @brief Construct a new Thermal object
     *
     * @param VISIBLE boolean to make thermals visible. For testing purposes - thermals should not be visible during game.
     * @param RADIUS_INNER radius for inner circle ("core") of thermal - the strongest part of the thermal
     * @param RADIUS_OUTER radius for outer circle of thermal - the weaker part of the thermal
     * @param STRENGTH_INNER strength of inner circle
     * @param STRENGTH_OUTER strength of outer circle
     * @param XPOS x coordinate of thermal
     * @param YPOS y coordinate of thermal
     */
    Thermal(const bool VISIBLE, const int RADIUS_INNER, const int RADIUS_OUTER, const double STRENGTH_INNER,
            const double STRENGTH_OUTER, const int XPOS, const int YPOS);

    /**
     * @brief draws thermal object
     *
     * @param window sfml window reference
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief checks if thermal contains the glider object
     *
     * @param OBJECT_POS_X glider x coordinate
     * @param OBJECT_POS_Y glider y coordinate
     * @return int related to whether the thermal contains an object, and in which circle (outer / inner). 1:inner, 2:outer, 0:does not contain.
     */
    int containsObject(const int OBJECT_POS_X, const int OBJECT_POS_Y) const;

    /**
     * @brief returns strength of inner circle
     *
     * @return double strength
     */
    double getInnerStrength() const;

    /**
     * @brief returns strength of outer circle
     *
     * @return double strength
     */
    double getOuterStrength() const;
};

/**
 * @brief helper function to ceate a Thermal object with random parametrization.
 * Randomizes position, inner and outer radii, inner and outer strength.
 *
 * @param VISIBLE boolean to make thermals visible. For testing purposes - thermals should not be visible during game.
 * @param WINDOW_SIZE_X sfml window size x for positioning
 * @param WINDOW_SIZE_Y sfml window size y for positioning
 * @return Thermal object
 */
Thermal createRandomThermal(const bool VISIBLE, const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y);

/**
 * @brief populates a vector of thermals with pointers to thermal objects
 *
 * @param vect reference to vector to be populated
 * @param COUNT number of thermals to popilate the vector
 * @param VISIBLE boolean to make thermals visible. For testing purposes - thermals should not be visible during game.
 * @param WINDOW_SIZE_X sfml window size x for positioning
 * @param WINDOW_SIZE_Y sfml window size y for positioning
 */
void populate_thermal_vector(std::vector<Thermal *> &vect, const int COUNT, const bool VISIBLE, const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y);

#endif