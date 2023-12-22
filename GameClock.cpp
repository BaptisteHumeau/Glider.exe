#include "GameClock.h"

#include <string>
#include <iostream>

GameClock::GameClock(const std::string FONT, const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y)
{
    if (!this->_font.loadFromFile(FONT))
    {
        std::cerr << "Error loading font.";
    }

    this->_textBox.setFont(this->_font);
    this->_textBox.setCharacterSize(15);
    this->_textBox.setPosition(WINDOW_SIZE_X - 175, WINDOW_SIZE_Y - 45);
}

void GameClock::SetTime(const int TIME)
{
    std::string toDisplay = "Flight time: " + std::to_string(TIME);
    this->_textBox.setString(toDisplay);
}

void GameClock::draw(sf::RenderWindow &window)
{
    window.draw(this->_textBox);
}