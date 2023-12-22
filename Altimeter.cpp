#include "Altimeter.h"

#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

Altimeter::Altimeter()
{
    this->_textBox = sf::Text();

    this->_textBox.setPosition(10, 10);
    this->_textBox.setCharacterSize(15);
    this->_textBox.setFillColor(sf::Color(255, 204, 0));
}

Altimeter::Altimeter(const int STARTING_ALTITUDE, const std::string FONT_PATH) : Altimeter()
{
    if (!this->_font.loadFromFile(FONT_PATH))
    {
        std::cerr << "Error loading font.";
    }
    this->_textBox.setFont(this->_font);

    if (STARTING_ALTITUDE > 0)
    {
        this->_altitude = STARTING_ALTITUDE;
        this->_originalAltitude = this->_altitude;
    }
    else
    {
        this->_altitude = 50;
    }
}

void Altimeter::reset()
{
    this->_altitude = this->_originalAltitude;
}

void Altimeter::draw(sf::RenderWindow &window)
{
    std::string toDisplay = "Altitude: " + std::to_string(int(this->_altitude));
    this->_textBox.setString(toDisplay);

    window.draw(this->_textBox);
}

void Altimeter::updateAltitude(const double VALUE)
{
    this->_altitude += VALUE;
}

int Altimeter::getAltitude() const
{
    return this->_altitude;
}

void Altimeter::setColor(const sf::Color COLOR)
{
    this->_textBox.setFillColor(COLOR);
}