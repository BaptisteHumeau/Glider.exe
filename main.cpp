/* CSCI 200: Final Project: FP - GLIDER.EXE

  Author: BAPTISTE HUMEAU
  Resources used:
  1 - SFML documentation.
        - Source: https://www.sfml-dev.org/documentation/2.6.0/group__graphics.php
  2- Passing functions as arguments.
        - Source: https://www.geeksforgeeks.org/passing-a-function-as-a-parameter-in-cpp/

A glider simulator game - find lift, avoid obstacles!

See ProjectPaper.txt in the same directory as this file for a full program description.
 */

#include "Glider.h"
#include "Altimeter.h"
#include "Thermal.h"
#include "Obstacle.h"
#include "Gamelog.h"
#include "instructions.h"
#include "IntroScreen.h"
#include "GameOverScreen.h"
#include "GameClock.h"

#include "PtrVectorFunctions.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace sf;

const bool VISIBLE_THERMALS = false; // for testing purposes. Should be set to false on final compile time.

const int WINDOW_SIZE_X = 1600; // factor of 16 is best for full screen
const int WINDOW_SIZE_Y = 900;  // factor of 9 is best for full screen

const std::string GAME_TITLE = "glider.exe";                     // Game title
const std::string FONT_TITLE = "Data/FontFiles/RobotCrush.ttf";  // Font path title
const std::string FONT_BODY = "Data/FontFiles/Gameplay.ttf";     // Font path body
const std::string FONT_SMALL = "Data/FontFiles/RetroGaming.ttf"; // Font path small text

const int STARTING_ALTITUDE = 100;                           // Starting altitude
const double GLIDER_FORWARD_SPEED = 1.4;                     // Forward speed
const double GLIDER_DIVE_SPEED = GLIDER_FORWARD_SPEED * 2.5; // Increased speed when pressing up arrow
const double GLIDER_TURN_SPEED = GLIDER_FORWARD_SPEED * 1.7; // Turn radius. Higher numers turn tighter
const double TURN_SINK_RATE = -0.05;                         // turning or diving increases the glider sink rate.

const sf::Color COLOR_NEUTRAL = sf::Color(255, 255, 255); // default color
const sf::Color COLOR_THERM_1 = sf::Color(255, 204, 204); // color thermal intensity 1
const sf::Color COLOR_THERM_2 = sf::Color(255, 153, 153); // color thermal intensity 2
const sf::Color COLOR_THERM_3 = sf::Color(255, 102, 102); // color thermal intensity 3
const sf::Color COLOR_THERM_4 = sf::Color(255, 51, 0);    // color thermal intensity 4
const sf::Color COLOR_THERM_5 = sf::Color(204, 0, 102);   // color thermal intensity 5
const sf::Color COLOR_THEME = COLOR_THERM_2;              // Theme color for the game. Match a color above for consistency

const int MAX_THERMALS = 20;             // Thermal count never to exceed
const int MIN_THERMALS = 8;              // Thermal count never to go below
const int INITIAL_THERMAL_COUNT = 8;     // Thermal count at start of game
const int THERMAL_CREATION_INTERVAL = 5; // in seconds. How often will thermals appear / be deleted.

const double initialObstacleInterval = 5;      // in seconds. How often will obstacles appear.
const int OBSTACLE_INTERVAL_INCREASE_RATE = 3; // in seconds. Smaller values make the game harder.
const int MAX_OBSTACLE_SPEED = 3;              // obstacle max speed
const int MIN_OBSTACLE_SPEED = 1;              // obstacle min speed

const int TRAIL_LENGHT = 30;                 // Trail marks glider path. Number of circles that make up trail.
const int TRAIL_TRANSPARENCY_INCREMENT = 10; // increments transparency of trail circles as they get farther from glider.
const double TRAIL_FREQUENCY = 0.2;          // inseconds. How far apart will trail circles be (smaller values -> smaller gap).

const int DRIFT_INTERVAL = 15;  // in seconds. Drift to simulate changing wind directions and speed.
const double DRIFT_RANGE = 1.5; // diameter of values range, will be centered at 0. 1/2 range = max drift speed.

int main()
{
    srand(time(0)); // Seed rand() for random thermal / obstacle generation
    rand();

    int currMaxAlt = 0;         // max altitude for the current game
    int currentGliderPositionX; // current glider position - to be updated by reference by glider class
    int currentGliderPositionY; // current glider position - to be updated by reference by glider class

    int drift_direction = 0; // initial drift direction - simulate wind
    double drift_speed = 0;  // initial drift speed - simulate wind

    bool leftTurn = false;  // left turn bool - use bool for instant turning vs waiting for key held
    bool rightTurn = false; // left turn bool - use bool for instant turning vs waiting for key held
    bool dive = false;      // dive bool

    std::vector<CircleShape *> trail; // Declare trail vector to mark glider path.

    std::vector<Obstacle *> obstacles;                         // Create obstacle vector
    double obstacleCreationInterval = initialObstacleInterval; // initial starting interval for creation - will decrease over time.

    std::vector<Thermal *> thermals; // Create thermal vector.
    populate_thermal_vector(thermals, INITIAL_THERMAL_COUNT, VISIBLE_THERMALS, WINDOW_SIZE_X, WINDOW_SIZE_Y);

    Glider glider(WINDOW_SIZE_X, WINDOW_SIZE_Y);
    glider.setSpeed(GLIDER_FORWARD_SPEED);
    glider.setColor(COLOR_NEUTRAL);

    Altimeter altimeter(STARTING_ALTITUDE, FONT_BODY); // altimeter keeps track of glider altitude

    Gamelog gamelog("Data/TextFiles/Gamelog.txt", FONT_BODY, WINDOW_SIZE_X); // Initialize gamelog.
    gamelog.readData();
    gamelog.findHighScore();

    GameClock gameClock(FONT_BODY, WINDOW_SIZE_X, WINDOW_SIZE_Y); // initialize game clock (contains sf::text object)
    Instructions instructions(WINDOW_SIZE_Y);                     // in-game instructions
    IntroScreen introScreen(GAME_TITLE, COLOR_THEME, FONT_TITLE, FONT_BODY, FONT_SMALL, WINDOW_SIZE_X, WINDOW_SIZE_Y);
    GameOverScreen gameOverScreen(COLOR_THEME, FONT_TITLE, FONT_BODY, WINDOW_SIZE_X, WINDOW_SIZE_Y);

    // Initialize sfml objects
    RenderWindow window(VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), GAME_TITLE);
    Clock clockTrail;            // to update trail vector according to glider motion
    Clock clockMotion;           // to move objects
    Clock clockAltimeter;        // to update altimeter
    Clock clockThermalCreation;  // to create thermals
    Clock clockThermalCheck;     // to check whether glider is in thermal
    Clock clockGame;             // to keep track of overall game time
    Clock clockObstacle;         // to create obstacles
    Clock clockObstacleInterval; // to update obstacle interval
    Clock clockDrift;            // to change the drift direction and speed
    Clock clockPaused;           // to keep track of paused time

    bool gameOn = false;               // bool to start game
    bool gameOverOn = false;           // bool to escape game over screen
    bool gamePaused = false;           // bool to pause game
    int timePaused = 0;                // int to keep track of how long the game has been paused.
    bool clearScoresConfirmed = false; // To confirm user choice to clear high scores
    bool clearScoresCancelled = false; // To cancel user choice to clear high scores

    while (window.isOpen()) // Draw loop
    {
        while (gameOverOn) // while not escaped game over loop
        {
            window.clear();
            gameOverScreen.draw(window); // display game over screen
            window.display();

            Event gameOverEvent;
            while (window.pollEvent(gameOverEvent)) // Event handling
            {
                if (gameOverEvent.type == sf::Event::Closed ||
                    (gameOverEvent.type == Event::KeyPressed && (gameOverEvent.key.code == Keyboard::Escape || gameOverEvent.key.code == Keyboard::Q)))
                {
                    window.close();
                    return 0;
                }
                if (gameOverEvent.type == Event::KeyPressed && gameOverEvent.key.code == Keyboard::Up) // escape screen
                {
                    gameOverOn = false;
                }
            }
        }

        while (!gameOn) // While the user has not started the game.
        {
            // Clear previous game
            window.clear();
            drift_speed = 0;
            drift_direction = 0;
            currMaxAlt = 0;
            timePaused = 0;
            leftTurn = false;
            rightTurn = false;
            dive = false;
            obstacleCreationInterval = initialObstacleInterval;
            glider.reset();
            altimeter.reset();
            clear_ptr_vector(obstacles);
            clear_ptr_vector(trail);
            clear_ptr_vector(thermals);

            populate_thermal_vector(thermals, INITIAL_THERMAL_COUNT, VISIBLE_THERMALS, WINDOW_SIZE_X, WINDOW_SIZE_Y);

            // Update high score
            gamelog.readData();
            gamelog.findHighScore();
            int currHighAltitude = gamelog.getAltitudeHighScore();
            int currHighDuration = gamelog.getDurationHighScore();
            std::string altDate = gamelog.getAltDate();
            std::string durDate = gamelog.getDurationDate();

            // Display intro screen
            introScreen.setScores(currHighAltitude, currHighDuration, altDate, durDate);
            introScreen.draw(window);
            glider.draw(window);
            window.display();

            Event introEvent;
            while (window.pollEvent(introEvent)) // Intro even handling
            {
                // close window
                if (introEvent.type == sf::Event::Closed || (introEvent.type == Event::KeyPressed &&
                                                             (introEvent.key.code == Keyboard::Q || introEvent.key.code == Keyboard::Escape)))
                {
                    window.close();
                    return 0;
                }

                // start game if up arrow pressed
                else if (introEvent.type == sf::Event::KeyPressed && introEvent.key.code == Keyboard::Up)
                {
                    gameOn = true;
                    clockGame.restart();
                }

                // Clear scores loop
                else if (introEvent.type == sf::Event::KeyPressed && introEvent.key.code == Keyboard::C)
                {
                    // Display message while not confirmed or cancelled
                    while (!clearScoresConfirmed && !clearScoresCancelled)
                    {
                        window.clear();
                        introScreen.draw(window);
                        introScreen.drawClearConfirmation(window);
                        glider.draw(window);
                        window.display();

                        // Confirmation event handling
                        Event Confirm;
                        while (window.pollEvent(Confirm))
                        {
                            // Close window
                            if (Confirm.type == sf::Event::Closed || (Confirm.type == Event::KeyPressed && Confirm.key.code == Keyboard::Escape))
                            {
                                window.close();
                                return 0;
                            }

                            // Confirm clear scores
                            if (Confirm.type == sf::Event::KeyPressed && Confirm.key.code == Keyboard::C)
                            {
                                clearScoresConfirmed = true;
                            }

                            // Cancel clear scores
                            if (Confirm.type == sf::Event::KeyPressed && Confirm.key.code == Keyboard::Q)
                            {
                                clearScoresCancelled = true;
                            }
                        }
                    }

                    if (!clearScoresCancelled) // Clear scores if confirmed and not cancelled.
                    {
                        // Clear gamelog and redraw.
                        clearScoresConfirmed = false;
                        gamelog.clear();
                        gamelog.findHighScore();
                        int currHighAltitude = gamelog.getAltitudeHighScore();
                        int currHighDuration = gamelog.getDurationHighScore();
                        std::string altDate = gamelog.getAltDate();
                        std::string durDate = gamelog.getDurationDate();
                        introScreen.setScores(currHighAltitude, currHighDuration, altDate, durDate);
                        introScreen.draw(window);
                        window.display();
                    }
                    clearScoresCancelled = false; // reset bool for next loop
                }
            }
        }

        // Start Game!
        window.clear(); // Clear intro screen or previous loop.

        // In-game event handling
        Event event;
        while (window.pollEvent(event))
        {
            // End game
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Q)
            {
                gamelog.addData(currMaxAlt, clockGame.getElapsedTime().asSeconds() - timePaused);          // add game data to game log
                gameOverScreen.setScores(currMaxAlt, clockGame.getElapsedTime().asSeconds() - timePaused); // set gameoverscreen scores
                gameOn = false;                                                                            // end game
                gameOverOn = true;                                                                         // move to game over screen
                gamePaused = false;                                                                        // in case the user quits while the game is paused
            }
            // Quit program
            if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) || event.type == sf::Event::Closed)
            {
                window.close();
                return 0;
            }

            // Pause game
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::P)
            {
                if (gamePaused)
                {
                    gamePaused = false;
                }
                else
                {
                    gamePaused = true;
                }
            }
            // Detect left turn.
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left)
            {
                leftTurn = true;             // use bool for immediate turn - turn implemented with gilder motion
                instructions.setTexture(-1); // instructions keep track of movement
            }
            // Detect right turn.
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right)
            {
                rightTurn = true;           // use bool for immediate turn - turn implemented with gilder motion
                instructions.setTexture(1); // instructions keep track of movement
            }
            // Reset sprite and turn bools is turn key is released.
            if (event.type == Event::KeyReleased && (event.key.code == Keyboard::Left || event.key.code == Keyboard::Right))
            {
                glider.updateTexture(0);
                instructions.setTexture(0);
                leftTurn = false;
                rightTurn = false;
            }
            // Speed up if up arrow is pressed.
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
            {
                dive = true;
                instructions.setTexture(2);
            }
            // Return to normal speed if up arrow is released.
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Up)
            {
                dive = false;
                glider.setSpeed(GLIDER_FORWARD_SPEED);
                instructions.setTexture(0);
            }
            // Check if both up and right are pressed - for instructions update
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                instructions.setTexture(3);
            }
            // Check if both up and left are pressed - for instructions update
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                instructions.setTexture(-3);
            }
            // Check if a turn is released but the up arrow is still pressed - for instructions update
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && event.type == Event::KeyReleased)
            {
                instructions.setTexture(2);
            }
        }

        if (gamePaused) // if game is paused
        {
            Time elapsedPaused = clockPaused.getElapsedTime(); // keep track of how much time has been paused
            if (elapsedPaused.asSeconds() >= 1)
            {
                timePaused += 1;
                clockPaused.restart();
            }
            continue; // skip rest of loop if game is paused
        }

        // generate drift values
        Time elapsedDrift = clockDrift.getElapsedTime();
        if (elapsedDrift.asSeconds() >= DRIFT_INTERVAL)
        {
            drift_direction = rand() % 3;
            drift_speed = rand() / (double)RAND_MAX * (DRIFT_RANGE) - (DRIFT_RANGE / 2); // center range about 0
            clockDrift.restart();
        }

        // Update Obstacle creation interval
        Time elapsedObstacleCreation = clockObstacleInterval.getElapsedTime();
        if (elapsedObstacleCreation.asSeconds() >= OBSTACLE_INTERVAL_INCREASE_RATE)
        {
            if (obstacleCreationInterval - 0.1 > 0.01)
            {
                obstacleCreationInterval -= 0.1;
            }
            clockObstacleInterval.restart();
        }

        // Populate obstacle vector
        Time elapsedObstacle = clockObstacle.getElapsedTime();
        if (elapsedObstacle.asSeconds() >= obstacleCreationInterval)
        {
            push_back_ptr_vector(obstacles, &createRandomObstacle, WINDOW_SIZE_X, WINDOW_SIZE_Y, MIN_OBSTACLE_SPEED, MAX_OBSTACLE_SPEED);
            clockObstacle.restart();
        }

        // Animate thermals vector
        Time elapsedThermal = clockThermalCreation.getElapsedTime();
        if (elapsedThermal.asSeconds() >= THERMAL_CREATION_INTERVAL)
        {
            int choice = rand() % 2; // Choice: add or remove thermal
            switch (choice)
            {
            case 0: // Add
                push_back_ptr_vector(thermals, &createRandomThermal, VISIBLE_THERMALS, WINDOW_SIZE_X, WINDOW_SIZE_Y);

                break;
            case 1:                                 // Remove
                if (thermals.size() > MIN_THERMALS) // ensure thermal count never goes below minimum specified
                {
                    pop_front_ptr_vector(thermals);
                }
                break;
            default:
                break;
            }

            if (thermals.size() > MAX_THERMALS) // Ensure that thermal count never exceeds max thermal count
            {
                pop_front_ptr_vector(thermals);
            }
            clockThermalCreation.restart();
        }

        // Check if glider is within thermal.
        Time elapsedThermal2 = clockThermalCheck.getElapsedTime();
        if (elapsedThermal2.asSeconds() >= 0.2)
        {
            double thermStrenght = 0; // Thermals can stack. Accrue thermal strength.
            for (const Thermal *THERM : thermals)
            {
                switch (THERM->containsObject(currentGliderPositionX, currentGliderPositionY))
                {
                case 1: // Glider is in outer thermal ring
                    thermStrenght += THERM->getOuterStrength();
                    break;
                case 2: // Glider is in inner thermal ring
                    thermStrenght += THERM->getInnerStrength();
                    thermStrenght += THERM->getOuterStrength();
                    break;
                default:
                    break;
                }
            }

            if (thermStrenght == 0) // glider is outside of thermal
            {
                glider.setColor(COLOR_NEUTRAL);
                altimeter.setColor(COLOR_NEUTRAL);
            }
            if (thermStrenght > 0) // adjust color according to thermal strength
            {
                glider.setColor(COLOR_THERM_1);
                altimeter.setColor(COLOR_THERM_1);
            }
            if (thermStrenght > 0.5)
            {
                glider.setColor(COLOR_THERM_2);
                altimeter.setColor(COLOR_THERM_2);
            }
            if (thermStrenght > 1)
            {
                glider.setColor(COLOR_THERM_3);
                altimeter.setColor(COLOR_THERM_3);
            }
            if (thermStrenght > 1.5)
            {
                glider.setColor(COLOR_THERM_4);
                altimeter.setColor(COLOR_THERM_4);
            }
            if (thermStrenght > 2)
            {
                glider.setColor(COLOR_THERM_5);
                altimeter.setColor(COLOR_THERM_5);
            }

            altimeter.updateAltitude(thermStrenght); // increment altimeter altitude according to thermal strength
            clockThermalCheck.restart();
        }

        // Populate trail vector
        Time elapsedTrail = clockTrail.getElapsedTime();
        if (elapsedTrail.asSeconds() >= TRAIL_FREQUENCY)
        {
            CircleShape *trailCircle = new CircleShape(1);
            trailCircle->setPosition(currentGliderPositionX, currentGliderPositionY);
            trail.push_back(trailCircle);
            clockTrail.restart();
            glider.getPostion(currentGliderPositionX, currentGliderPositionY); // update position variables after loop - skips the first circle
        }
        if (trail.size() > TRAIL_LENGHT) // erase first circle
        {
            pop_front_ptr_vector(trail);
        }

        // Move glider, obstacles
        Time elapsedMotion = clockMotion.getElapsedTime();
        if (elapsedMotion.asSeconds() >= 0.02)
        {
            glider.updatePosition(drift_direction, drift_speed, WINDOW_SIZE_X, WINDOW_SIZE_Y); // move glider

            // Use bool for turns so that turns are immediate - instead of waiting to recognize a key hold.
            if (dive)
            {
                glider.setSpeed(GLIDER_DIVE_SPEED);
                altimeter.updateAltitude(TURN_SINK_RATE); // Speeding up reduces glide efficiency
            }
            if (leftTurn)
            {
                glider.rotate(-GLIDER_TURN_SPEED);
                altimeter.updateAltitude(TURN_SINK_RATE); // Turns decrease glide efficiency
                glider.updateTexture(-1);
            }
            if (rightTurn)
            {
                glider.rotate(GLIDER_TURN_SPEED);
                altimeter.updateAltitude(TURN_SINK_RATE); // Turns decrease glide efficiency
                glider.updateTexture(1);
            }

            for (auto it = obstacles.begin(); it != obstacles.end();) // move obstacles
            {
                (*it)->updatePosition();
                if ((*it)->isOutOfBounds(WINDOW_SIZE_X, WINDOW_SIZE_Y)) // Delete obstacle if it leaves window bounds
                {
                    delete *it;
                    *it = nullptr;
                    it = obstacles.erase(it);
                }
                else
                {
                    ++it;
                }
            }
            clockMotion.restart();
        }

        // decrease altimeter altitude over time
        Time elapsedAltimeter = clockAltimeter.getElapsedTime();
        if (elapsedAltimeter.asSeconds() >= 1)
        {
            altimeter.updateAltitude(-1);
            clockAltimeter.restart();
        }

        // Draw trail
        int transparency = 1;
        for (CircleShape *circle : trail)
        {
            circle->setFillColor(sf::Color(255, 255, 255, transparency));
            if (transparency + TRAIL_TRANSPARENCY_INCREMENT <= 255) // reduce transparency of circles farther from glider
            {
                transparency += TRAIL_TRANSPARENCY_INCREMENT;
            };
            window.draw(*circle);
        }

        // draw thermals, obstacles
        draw_ptr_vector(thermals, window);
        draw_ptr_vector(obstacles, window);

        // Draw glider, altimeter, gamelog, instructions
        glider.draw(window);
        altimeter.draw(window);
        gamelog.draw(window);
        instructions.draw(window);
        gameClock.SetTime(clockGame.getElapsedTime().asSeconds() - timePaused);
        gameClock.draw(window);

        // Display all
        window.display();

        // Update highest altitude for this game
        int currentAltitude = altimeter.getAltitude();
        if (currentAltitude > currMaxAlt)
        {
            currMaxAlt = currentAltitude;
        }

        // Game over once glider altitude is 0
        if (currentAltitude <= 0)
        {
            gamelog.addData(currMaxAlt, clockGame.getElapsedTime().asSeconds());
            gameOverScreen.setScores(currMaxAlt, clockGame.getElapsedTime().asSeconds());
            gameOn = false;
            gameOverOn = true;
        }

        // Game over if glider hits obstacle
        for (const Obstacle *obs : obstacles)
        {
            if (obs->checkCollision(currentGliderPositionX, currentGliderPositionY))
            {
                gamelog.addData(currMaxAlt, clockGame.getElapsedTime().asSeconds() - timePaused);
                gameOverScreen.setScores(currMaxAlt, clockGame.getElapsedTime().asSeconds() - timePaused);
                gameOn = false;
                gameOverOn = true;
            }
        }
    }
    return 0;
}