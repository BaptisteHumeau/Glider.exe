#include "GameOverScreen.h"

#include <SFML\Graphics.hpp>
#include <iostream>

GameOverScreen::GameOverScreen(const sf::Color COLOR, const std::string FONT_TITLE, const std::string FONT_BODY, const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y)
{
    if (!this->_fontTitle.loadFromFile(FONT_TITLE))
    {
        std::cerr << "Error loading font.";
    }

    if (!this->_fontBody.loadFromFile(FONT_BODY))
    {
        std::cerr << "Error loading font.";
    }
    if (!this->_imageTexture.loadFromFile("Data/Images/Instructions3.png"))
    {
        std::cerr << "Error Loading Sprite" << std::endl;
    }

    this->_textBoxGameOver.setFont(this->_fontTitle);
    this->_textBoxGameOver.setFillColor(COLOR);
    this->_textBoxGameOver.setString("game over");
    this->_textBoxGameOver.setCharacterSize(WINDOW_SIZE_X / 30);

    sf::FloatRect textBounds = this->_textBoxGameOver.getGlobalBounds();
    float xPosTitle = (WINDOW_SIZE_X - textBounds.width) / 2;
    float yPosTitle = (WINDOW_SIZE_Y - textBounds.height) / 4;
    this->_textBoxGameOver.setPosition(xPosTitle, yPosTitle);

    this->_textBoxStats.setFont(this->_fontBody);
    this->_textBoxStats.setFillColor(sf::Color(230, 230, 230));
    this->_textBoxStats.setCharacterSize(WINDOW_SIZE_X / 100);
    this->_textBoxStats.setPosition(xPosTitle, yPosTitle + 60);

    this->_image.setTexture(this->_imageTexture);
    this->_image.setPosition(30, WINDOW_SIZE_Y - 90);
    this->_image.setScale(0.4, 0.4);
}

void GameOverScreen::draw(sf::RenderWindow &window)
{
    window.draw(this->_textBoxGameOver);
    window.draw(this->_textBoxStats);
    window.draw(this->_image);
}

void GameOverScreen::setScores(const int ALTITUDE, const int TIME)
{
    std::string toDisplay = "Max altitude: " + std::to_string(ALTITUDE) + " ft\nFlight Time: " + std::to_string(TIME) + " secs";
    this->_textBoxStats.setString(toDisplay);
}