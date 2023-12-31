#ifndef OBJECTS_H
#define OBJECTS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <queue>

enum objState{coin, player, obstacle};
enum buttonState{normal, hovered, clicked};

class Objects
{
public:
    Objects(){};
    ~Objects();
    void resetObjects();

    // Background Functions
    void initBackground(int width, int height);
    void moveBackground(int width);
    
    // Player Functions
    void initPlayer(std::string playerFile, sf::IntRect rect);
    void movePlayer(sf::RenderWindow &window, int height);
    
    // Obstacle Functions
    Objects(int width, int height, std::string obstFile);
    void initObstacles(std::string obstFile, int width, int height, sf::Vector2f velocity);
    void updateObstacles(sf::RenderWindow& window, int width, int height, sf::FloatRect player, bool& failedGame);
    
    // Coin Functions
    Objects(std::string coinFile, sf::IntRect rect, int width, int height);
    void initCoins(int height, int width);
    void updateCoins(sf::RenderWindow& window, int width, int height, int& score, sf::FloatRect player);

    // Button Functions
    void initButton(std::string s, std::string text, sf::IntRect rect, sf::Vector2f position, sf::Vector2f size, sf::Color color);
    virtual void drawButton(sf::RenderTarget& target,sf::RenderStates states) const;
    void updateButton(sf::Event& e, sf::RenderWindow& window);
    sf::Uint32 getButtonState(){return btnState;};
    sf::Uint32 getObjState(){return objState;};
    sf::Vector2f getPosition(){return buttonPos;};
    
    // Sprite Animation
    void animateSprite();

    sf::Uint32 objState, btnState;
    sf::Font font;
    sf::Clock clock;
    sf::Clock spawnClock;

    // Background Variables
    sf::RectangleShape background[5], backgroundDupe[5];
    sf::Texture backTexture[5];
    float backgroundX[5], backgroundDupeX[5];
    float speeds[5] = {0.6, 0.9, 1.2, 1.5, 1.8};

    // Button Variables
    sf::Sprite button;
    sf::Texture normalButton, hoverButton, clickButton;
    sf::Vector2f buttonPos;
    sf::IntRect buttonRect;

    // Player Variables
    sf::Sprite player;
    sf::Texture playerTexture;
    sf::Vector2f moveUp, moveDown, idle;
    int playerX, playerY, playerSizeX, playerSizeY;
    sf::IntRect playerRect;

    //Obstacle Variables
    sf::Sprite obstSprite;
    sf::CircleShape obstHitBox;
    sf::FloatRect obstBounds;
    sf::Texture obstTexture;
    float obstSize;
    sf::Vector2f velocity;
    std::vector<Objects*> obstV;
    

    // Coin Variables
    sf::Sprite coin;
    sf::Texture coinTexture;
    sf::IntRect coinRect;
    sf::FloatRect coinBounds;
    int coinSize;
    std::vector<Objects*> coinV;
    


};

#endif
