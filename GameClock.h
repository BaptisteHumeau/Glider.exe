#ifndef GAMECLOCK_H
#define GAMECLOCK_H

#include <SFML\Graphics.hpp>
#include <string>

class GameClock
{
private:
    sf::Text _textBox;
    sf::Font _font;

    int _time;

public:
    /**
     * @brief Construct a Game Clock object
     *
     * @param FONT path to .ttf file
     * @param WINDOW_SIZE_X size of sfml window - to set object position
     * @param WINDOW_SIZE_Y size of sfml window - to set object position
     */
    GameClock(const std::string FONT, const int WINDOW_SIZE_X, const int WINDOW_SIZE_Y);

    /**
     * @brief Set time to be displayed
     *
     * @param TIME
     */
    void SetTime(const int TIME);

    /**
     * @brief draw the glameclock object
     *
     * @param window sfml window reference
     */
    void draw(sf::RenderWindow &window);
};

#endif