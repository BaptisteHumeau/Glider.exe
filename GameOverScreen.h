#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <SFML\Graphics.hpp>

class GameOverScreen
{
private:
    sf::Text _textBoxGameOver;
    sf::Text _textBoxStats;

    sf::Sprite _image;
    sf::Texture _imageTexture;
    sf::Font _fontTitle;
    sf::Font _fontBody;

public:
    /**
     * @brief Construct a new Game Over Screen object
     *
     * @param COLOR // text color for tiles, etc
     * @param FONT_TITLE_PATH // path to .ttf file for title
     * @param FONT_BODY // path to .ttf file for body
     * @param WINDOW_SIZE_X // sfml window size for object postioning
     * @param WINDOW_SIZE_Y // sfml window size for object postioning
     */
    GameOverScreen(const sf::Color COLOR, const std::string FONT_TITLE_PATH, const std::string FONT_BODY, const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y);

    /**
     * @brief draws game oveer screen
     *
     * @param window sfml window reference
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief Set the hiscores to be displayed based on current highscore values
     *
     * @param ALTITUDE // highest altitude reached
     * @param TIME // longest game
     */
    void setScores(const int ALTITUDE, const int TIME);
};

#endif