#ifndef ALTIMETER_H
#define ALTIMETER_H

#include <SFML\Graphics.hpp>

class Altimeter
{
private:
    double _altitude;
    double _originalAltitude;

    sf::Text _textBox;
    sf::Font _font;

public:
    /**
     * @brief Construct a new Altimeter object
     *
     */
    Altimeter();

    /**
     * @brief Construct a new Altimeter object
     *
     * @param STARTING_ALTITUDE // Altitude at begginning of game
     * @param FONT_PATH // Path to .ttf file
     */
    Altimeter(const int STARTING_ALTITUDE, const std::string FONT_PATH);

    /**
     * @brief Reset altimeter to starting parameters
     *
     */
    void reset();

    /**
     * @brief Draw the altimeter object
     *
     * @param window sfml window reference
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief Update altimeter altitude
     *
     * @param VALUE Altitude with which to update - based on thermal strength or sink rate
     */
    void updateAltitude(const double VALUE);

    /**
     * @brief Return altitude
     *
     * @return int altitude
     */
    int getAltitude() const;

    /**
     * @brief Set altimeter color - based on thermal strength
     *
     * @param COLOR
     */
    void setColor(const sf::Color COLOR);
};

#endif