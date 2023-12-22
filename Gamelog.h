#ifndef GAMELOG_H
#define GAMELOG_H

#include <fstream>
#include <string>
#include <vector>
#include <SFML\Graphics.hpp>

class Gamelog
{

private:
    int _maxAltitude;
    int _maxDuration;
    std::string _dateAltitude;
    std::string _dateDuration;

    std::string _fileName;
    std::vector<std::string> _altitudes;
    std::vector<std::string> _durations;
    std::vector<std::string> _dates;

    sf::Text _textBoxAltitude;
    sf::Text _textBoxDuration;
    sf::Font _font;

public:
    /**
     * @brief Construct a Gamelog object
     *
     * @param fileName // Name of the output/input .txt file
     * @param FONT_PATH // Path to .ttf file
     * @param WINDOW_SIZE_X // sfml window size to set gamelog position
     */
    Gamelog(std::string fileName, const std::string FONT_PATH, const int WINDOW_SIZE_X);

    /**
     * @brief clears the gamelog .txt file and resets gamelog data
     *
     */
    void clear();

    /**
     * @brief Adds game data to game log .txt file
     *
     * @param maxAltitude Max altitude for a given game to be recorded
     * @param duration Max duration for a given game to be recorded
     */
    void addData(const int maxAltitude, const int duration);

    /**
     * @brief Reads data from gamelog .txt file and stores it in member data
     *
     */
    void readData();

    /**
     * @brief Calculates highscores
     *
     */
    void findHighScore();

    /**
     * @brief Draws the game log object (highscores)
     *
     * @param window
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief Return highest altitude in record
     *
     * @return int
     */
    int getAltitudeHighScore() const;

    /**
     * @brief Return longest duration in record
     *
     * @return int
     */
    int getDurationHighScore() const;

    /**
     * @brief Return date of duration highscore
     *
     * @return std::string
     */
    std::string getDurationDate() const;

    /**
     * @brief Return date of altitude highscore
     *
     * @return std::string
     */
    std::string getAltDate() const;
};

#endif
