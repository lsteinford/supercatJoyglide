#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>

class Game
{
public:
    Game(int winSizeX, int winSizeY, std::string gameName);
    void events();
    void display();
    bool gameRunning();
    void drawText(sf::Text& t);
    void drawRect(sf::RectangleShape& rect);
    void drawSprite(sf::Sprite sprite);
    void drawCircle(sf::CircleShape& circ);
    void clear();
    sf::Event e;
    sf::RenderWindow window;
    clock_t startTime;

    sf::Clock clock;
private:
    
};

#endif