#include "IntroScreen.h"

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

IntroScreen::IntroScreen(const std::string CONTENTS, const sf::Color COLOR, std::string FONT_PATH_TITLE, const std::string FONT_PATH_BODY,
                         const std::string FONT_PATH_DATES, const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y)
{
    // Load fonts
    if (!this->_fontTitle.loadFromFile(FONT_PATH_TITLE))
    {
        std::cerr << "Error loading font.";
    }

    if (!this->_fontBody.loadFromFile(FONT_PATH_BODY))
    {
        std::cerr << "Error loading font.";
    }
    if (!this->_fontDates.loadFromFile(FONT_PATH_DATES))
    {
        std::cerr << "Error loading font.";
    }

    // Set Title
    this->_title.setFont(this->_fontTitle);
    this->_title.setFillColor(COLOR);
    this->_title.setString(CONTENTS);
    this->_title.setCharacterSize(WINDOW_SIZE_X / 30);

    sf::FloatRect textBounds = this->_title.getGlobalBounds();
    float xPosTitle = (WINDOW_SIZE_X - textBounds.width) / 2;
    float yPosTitle = (WINDOW_SIZE_Y - textBounds.height) / 4;
    this->_title.setPosition(xPosTitle, yPosTitle);

    // Set High scores
    this->_scoresText.setFont(this->_fontBody);
    this->_scoresText.setFillColor(COLOR);
    this->_scoresText.setCharacterSize(WINDOW_SIZE_X / 100);
    this->_scoresText.setPosition(xPosTitle, yPosTitle + 60);

    // Set Dates
    this->_datesText.setFont(this->_fontDates);
    this->_datesText.setFillColor(sf::Color(230, 230, 230));
    this->_datesText.setCharacterSize(WINDOW_SIZE_X / 100);
    this->_datesText.setPosition(xPosTitle, yPosTitle + 57);

    // Set clear confirmation messsage
    this->_clearConfirmation1.setFont(this->_fontBody);
    this->_clearConfirmation1.setFillColor(COLOR);
    this->_clearConfirmation1.setCharacterSize(WINDOW_SIZE_X / 100);
    this->_clearConfirmation1.setPosition(xPosTitle, yPosTitle + 200);
    this->_clearConfirmation1.setString("Clear high scores?");

    this->_clearConfirmation2.setFont(this->_fontDates);
    this->_clearConfirmation2.setFillColor(sf::Color(230, 230, 230));
    this->_clearConfirmation2.setCharacterSize(WINDOW_SIZE_X / 100);
    this->_clearConfirmation2.setPosition(xPosTitle, yPosTitle + 225);
    this->_clearConfirmation2.setString("PRESS C TO CONFIRM\nPRESS Q TO CANCEL");

    // Set Instructions1
    if (!this->_instructionsTexture.loadFromFile("Data/Images/Instructions1.png"))
    {
        std::cerr << "Error loading instructions1.png" << std::endl;
    }
    this->_instructions = sf::Sprite(this->_instructionsTexture);
    this->_instructions.setScale(0.4, 0.4);
    this->_instructions.setPosition(30, WINDOW_SIZE_Y - 120);
}

void IntroScreen::draw(sf::RenderWindow &window)
{
    window.draw(this->_title);
    window.draw(this->_instructions);
    window.draw(this->_scoresText);
    window.draw(this->_datesText);
}

void IntroScreen::setScores(const int ALTITUDE, const int DURATION, const std::string DATE_ALT, const std::string DATE_DUR)
{
    this->_highScoreAltitude = ALTITUDE;
    this->_highScoreDuration = DURATION;
    this->_highScoreAltDate = DATE_ALT;
    this->_highScoreDurDate = DATE_DUR;

    this->_scoresText.setString("Highscore:  " + std::to_string(ALTITUDE) + "  ft" + "\n\nLongest flight:  " + std::to_string(DURATION) + "  secs");
    this->_datesText.setString("\n" + DATE_ALT + "\n\n" + DATE_DUR);
}

void IntroScreen::drawClearConfirmation(sf::RenderWindow &window)
{
    window.draw(this->_clearConfirmation1);
    window.draw(this->_clearConfirmation2);
}