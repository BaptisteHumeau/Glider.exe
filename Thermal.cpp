#include "Thermal.h"

#include <cstdlib>
#include <SFML\Graphics.hpp>

Thermal::Thermal(const bool VISIBLE, const int RADIUS_INNER, const int RADIUS_OUTER, const double STRENGTH_INNER,
                 const double STRENGTH_OUTER, const int XPOS, const int YPOS)
{
    this->_xPos = XPOS;
    this->_yPos = YPOS;

    this->_radiusInner = RADIUS_INNER;
    this->_radiusOuter = RADIUS_OUTER;
    this->_strengthInner = STRENGTH_INNER;
    this->_strengthOuter = STRENGTH_OUTER;

    this->_circleInner = sf::CircleShape();
    this->_circleOuter = sf::CircleShape();

    this->_circleInner.setFillColor(sf::Color::Transparent);
    this->_circleInner.setPosition(this->_xPos, this->_yPos);
    this->_circleInner.setRadius(this->_radiusInner);
    this->_circleInner.setOrigin(this->_radiusInner, this->_radiusInner);
    this->_circleOuter.setOrigin(this->_radiusOuter, this->_radiusOuter);

    this->_circleOuter.setFillColor(sf::Color::Transparent);
    this->_circleOuter.setPosition(this->_xPos, this->_yPos);
    this->_circleOuter.setRadius(this->_radiusOuter);

    if (VISIBLE)
    {
        this->_circleInner.setOutlineThickness(1);
        this->_circleInner.setOutlineColor(sf::Color::White);
        this->_circleInner.setFillColor(sf::Color(255, 255, 255, 15));

        this->_circleOuter.setOutlineThickness(1);
        this->_circleOuter.setOutlineColor(sf::Color::White);
        this->_circleOuter.setFillColor(sf::Color(255, 255, 255, 10));
    }
}

void Thermal::draw(sf::RenderWindow &window)
{
    window.draw(this->_circleOuter);
    window.draw(this->_circleInner);
}

double Thermal::getInnerStrength() const
{
    return this->_strengthInner;
}

double Thermal::getOuterStrength() const
{
    return this->_strengthOuter;
}

int Thermal::containsObject(const int OBJECT_POS_X, const int OBJECT_POS_Y) const
{
    int xLeftInner = this->_xPos - this->_radiusInner;
    int xRightInner = this->_xPos + this->_radiusInner;
    int yTopInner = this->_yPos - this->_radiusInner;
    int yBottomInner = this->_yPos + this->_radiusInner;

    int xLeftOuter = this->_xPos - this->_radiusOuter;
    int xRightOuter = this->_xPos + this->_radiusOuter;
    int yTopOuter = this->_yPos - this->_radiusOuter;
    int yBottomOuter = this->_yPos + this->_radiusOuter;

    if (OBJECT_POS_X > xLeftInner && OBJECT_POS_X < xRightInner && OBJECT_POS_Y > yTopInner && OBJECT_POS_Y < yBottomInner)
    {
        return 2;
    }
    if (OBJECT_POS_X > xLeftOuter && OBJECT_POS_X < xRightOuter && OBJECT_POS_Y > yTopOuter && OBJECT_POS_Y < yBottomOuter)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Thermal createRandomThermal(const bool VISIBLE, const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y)
{
    int outerRadius = rand() % (200 - 100) + 100;
    int innerRadius = rand() % (99 - 30) + 30;

    double outerStrength = rand() / (double)RAND_MAX * (0.5 - 0.1) + 0.1;
    double innerStrength = rand() / (double)RAND_MAX * (1 - 0.5) + 0.5;

    int posX = rand() % WINDOW_SIZE_X;
    int posY = rand() % WINDOW_SIZE_Y;

    Thermal therm(VISIBLE, innerRadius, outerRadius, innerStrength, outerStrength, posX, posY);

    return therm;
}

void populate_thermal_vector(std::vector<Thermal *> &vect, const int COUNT, const bool VISIBLE, const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y)
{
    for (int i = 0; i < COUNT; i++)
    {
        Thermal *newTherm = new Thermal(createRandomThermal(VISIBLE, WINDOW_SIZE_X, WINDOW_SIZE_Y));
        vect.push_back(newTherm);
    }
}