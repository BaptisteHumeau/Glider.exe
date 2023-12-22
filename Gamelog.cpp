#include "Gamelog.h"

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>

Gamelog::Gamelog(std::string fileName, const std::string FONT_PATH, const int WINDOW_SIZE_X)
{
    this->_fileName = fileName;

    if (!this->_font.loadFromFile(FONT_PATH))
    {
        std::cerr << "Error loading font.";
    }

    this->_textBoxAltitude.setPosition(WINDOW_SIZE_X / 2 - WINDOW_SIZE_X * 0.06 + 30, 10);
    this->_textBoxAltitude.setFont(this->_font);
    this->_textBoxAltitude.setCharacterSize(15);

    this->_textBoxDuration.setPosition(WINDOW_SIZE_X - 200, 10);
    this->_textBoxDuration.setFont(this->_font);
    this->_textBoxDuration.setCharacterSize(15);
}

void Gamelog::clear()
{
    std::ofstream file(this->_fileName, std::ofstream::trunc);
    file.close();

    this->_maxAltitude = 0;
    this->_maxDuration = 0;
    this->_altitudes.clear();
    this->_durations.clear();
    this->_dates.clear();
}

void Gamelog::addData(const int maxAltitude, const int duration)
{
    // Create file if it doesn't already exist
    std::ofstream fileWrite(this->_fileName, std::ios::out | std::ios::app);
    if (fileWrite.fail())
    {
        std::cerr << "Error opening Gamelog file." << std::endl;
        return;
    }

    // Get the current time
    std::time_t currentTime = std::time(nullptr);

    // Convert the current time to a tm struct
    std::tm *currentDate = std::localtime(&currentTime);

    // Format the date as mm-dd-yyyy
    std::string date = std::to_string(currentDate->tm_mon + 1) + "-" +
                       std::to_string(currentDate->tm_mday) + "-" +
                       std::to_string(currentDate->tm_year + 1900);

    fileWrite << maxAltitude << " " << duration << " " << date << std::endl;
    fileWrite.close();
}

void Gamelog::readData()
{
    std::ifstream fileRead(this->_fileName);

    if (fileRead.fail())
    {
        std::cerr << "Error reading Gamelog file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(fileRead, line))
    {
        std::istringstream iss(line);
        int altitude, duration;
        std::string date;

        // Extract altitude, duration, and date from each line
        if (iss >> altitude >> duration >> date)
        {
            _altitudes.push_back(std::to_string(altitude));
            _durations.push_back(std::to_string(duration));
            _dates.push_back(date);
        }
        else
        {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    fileRead.close();
}

void Gamelog::findHighScore()
{
    // Find altitude high score
    if (this->_altitudes.empty())
    {
        this->_maxAltitude = 0;
        this->_dateAltitude = "";
    }
    else
    {
        this->_maxAltitude = std::stoi(this->_altitudes[0]);
        this->_dateAltitude = this->_dates[0];

        for (unsigned int i = 1; i < this->_altitudes.size(); i++)
        {
            int altitude = std::stoi(this->_altitudes[i]);

            if (altitude > this->_maxAltitude)
            {
                this->_maxAltitude = altitude;
                this->_dateAltitude = this->_dates[i];
            }
        }
    }

    // find duration high score
    if (this->_durations.empty())
    {
        this->_maxDuration = 0;
        this->_dateDuration = "";
    }
    else
    {
        this->_maxDuration = std::stoi(this->_durations[0]);
        this->_dateDuration = this->_dates[0];

        for (unsigned i = 1; i < this->_durations.size(); i++)
        {
            int duration = std::stoi(this->_durations[i]);

            if (duration > this->_maxDuration)
            {
                this->_maxDuration = duration;
                this->_dateDuration = this->_dates[i];
            }
        }
    }
}

void Gamelog::draw(sf::RenderWindow &window)
{
    std::string toDisplayAltitude = "High score: " + std::to_string(this->_maxAltitude);
    this->_textBoxAltitude.setString(toDisplayAltitude);

    std::string toDisplayDuration = "Longest flight: " + std::to_string(this->_maxDuration);
    this->_textBoxDuration.setString(toDisplayDuration);

    window.draw(this->_textBoxAltitude);
    window.draw(this->_textBoxDuration);
}

int Gamelog::getAltitudeHighScore() const
{
    return this->_maxAltitude;
}

int Gamelog::getDurationHighScore() const
{
    return this->_maxDuration;
}

std::string Gamelog::getDurationDate() const
{
    return this->_dateDuration;
}

std::string Gamelog::getAltDate() const
{
    return this->_dateAltitude;
}