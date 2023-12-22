#ifndef INTROSCREEN_H
#define INTROSCREEN_H

#include "Gamelog.h"
#include <SFML\Graphics.hpp>
#include <string>

class IntroScreen
{
private:
    sf::Text _title;
    sf::Font _fontTitle;

    sf::Text _scoresText;
    sf::Font _fontBody;

    sf::Text _datesText;
    sf::Font _fontDates;

    sf::Text _clearConfirmation1;
    sf::Text _clearConfirmation2;

    sf::Sprite _instructions;
    sf::Texture _instructionsTexture;

    int _highScoreAltitude;
    std::string _highScoreAltDate;
    int _highScoreDuration;
    std::string _highScoreDurDate;

public:
    /**
     * @brief Construct a new Intro Screen object
     *
     * @param CONTENTS text content
     * @param COLOR text color
     * @param FONT_PATH_TITLE path to .ttf file for title
     * @param FONT_PATH_BODY path to .ttf file for body
     * @param FONT_PATH_DATES path to .ttf file for dates
     * @param WINDOW_SIZE_X sfml window size for positioning
     * @param WINDOW_SIZE_Y sfml window size for positionng
     */
    IntroScreen(const std::string CONTENTS, const sf::Color COLOR, const std::string FONT_PATH_TITLE, const std::string FONT_PATH_BODY,
                const std::string FONT_PATH_DATES, const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y);

    /**
     * @brief draws intro screen
     *
     * @param window sfml window reference
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief Set the highscores to be displayed
     *
     * @param ALTITUDE highest altitude
     * @param DURATION longest duration
     * @param DATE_ALT date of altitude high score
     * @param DATE_DUR date of duration high score
     */
    void setScores(const int ALTITUDE, const int DURATION, const std::string DATE_ALT, const std::string DATE_DUR);

    /**
     * @brief Draws confirmation message to clear high scores
     *
     * @param window sfml window reference
     */
    void drawClearConfirmation(sf::RenderWindow &window);
};

#endif