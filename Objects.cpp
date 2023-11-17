#include "Objects.h"

//  BACKGROUND FUNCTIONS
/**
 * @brief Initialize background images
 * 
 * @param width 
 * @param height 
 */
void Objects::initBackground(int width, int height)
{
    // Randomize City Background
    sf::Time time = clock.restart();
    int randCity = 1 + static_cast<int>(time.asMicroseconds()) % 5;

    for(int i = 0; i < 5; i++)
    {
        backgroundX[i] = 0;
        backgroundDupeX[i] = width;

        background[i].setPosition(backgroundX[i], 0);
        background[i].setSize(sf::Vector2f(width, height));

        backgroundDupe[i].setPosition(backgroundDupeX[i], 0);
        backgroundDupe[i].setSize(sf::Vector2f(width, height));

        backTexture[i].loadFromFile("assets/city" + std::to_string(randCity) + "/" + std::to_string(i + 1) + ".png");
        
        background[i].setTexture(&backTexture[i]);
        backgroundDupe[i].setTexture(&backTexture[i]);
        
    }
}

/**
 * @brief Move background images
 * 
 */
void Objects::moveBackground(double dt, int width)
{

    for(int i = 0; i < 5; i++)
    {
        backgroundX[i] += speeds[i] * -dt;
        backgroundDupeX[i] += speeds[i] * -dt;

        if (backgroundX[i] <= -width)
        {
            backgroundX[i] = width;
        }

        if (backgroundDupeX[i] <= -width)
        {
            backgroundDupeX[i] = width;
        }
        
        background[i].setPosition(backgroundX[i], 0);
        backgroundDupe[i].setPosition(backgroundDupeX[i], 0);;
    }
    
}

// PLAYER FUNCTIONS
/**
 * @brief Initialize Player Object
 * 
 * @param playerFile 
 * @param rect 
 */
void Objects::initPlayer(std::string playerFile, sf::IntRect rect)
{
    playerX = 200;
    playerY = 200;
    playerSizeX = 3;
    playerSizeY = 3;
    playerRect = rect;
    playerTexture.loadFromFile(playerFile);
    player.setTexture(playerTexture);
    player.setTextureRect(playerRect);
    player.setPosition(sf::Vector2f(playerX, playerY));
    player.setScale(sf::Vector2f(playerSizeX, playerSizeY));
   
    objState = objState::player;
    clock.restart();
}

/**
 * @brief Move Player object
 * 
 * @param window 
 * @param event 
 * @param isKeyPressed 
 */
void Objects::movePlayer(sf::RenderWindow &window)
{
    sf::Vector2f moveUp;
    moveUp.x = 0;
    moveUp.y = -0.1;
    sf::Vector2f moveDown;
    moveDown.x = 0;
    moveDown.y = 0.05;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        
        player.move(moveUp);
        playerRect.top = 192;
    }
    else
    {
        player.move(moveDown);
        playerRect.top = 144;
    }
    window.draw(player);
}

// OBSTACLE FUNCTIONS
/**
 * @brief Initialize Obstacles object
 * 
 * @param obstFile 
 */
void Objects::initObstacles(std::string obstFile)
{
    obstSizeX = 1;
    obstSizeY = 1;
    obsTexture.loadFromFile(obstFile);
    obst.setTexture(obsTexture);
    obst.setScale(sf::Vector2f(obstSizeX, obstSizeY));
    obst.setPosition(000, 000);
}

/**
 * @brief Move Obstacles
 * 
 * @param window 
 */
void Objects::moveObstacles(sf::RenderWindow& window)
{
    sf::Vector2f position = obst.getPosition();
    
    if(position.x<0){
        srand(time(NULL));//might wanna do this @ constructor instead, resource hungry, but betters random #s
        sf::Time time = sf::seconds(0.1f);
        obst.setPosition(900, (rand() % 901));
    }
    window.draw(obst);
}

// COIN FUNCTIONS
/**
 * @brief Initialize Coins object
 * 
 * @param coinFile 
 */
void Objects::initCoins(std::string coinFile)
{
    coinSize = 4;
    coinTexture.loadFromFile(coinFile);
    coin.setTexture(coinTexture);
    coin.setScale(sf::Vector2f(coinSize, coinSize));
    coin.setPosition(000, 000);
    objState = objState::coin;
}

/**
 * @brief Move Coins
 * 
 * @param window 
 */
void Objects::moveCoins(sf::RenderWindow& window)
{
    sf::Vector2f position = coin.getPosition();
    
    if(position.x<0){
        srand(time(NULL));//might wanna do this @ constructor instead, resource hungry, but betters random #s
        sf::Time time = sf::seconds(0.1f);
        coin.setPosition(900, (rand() % 901));
    }
    window.draw(coin);
}

/**
 * @brief Animates sprites for coins and player
 * 
 */
void Objects::animateSprite(Objects& object)
{

    sf::Time elapsed = clock.getElapsedTime();
    double elapsedTime = elapsed.asSeconds();

    if(object.getObjState() == objState::player)
    {
       if(elapsedTime > 0.08f)
        {
            if(playerRect.left == 128)
            {
                playerRect.left = 0;
            } else {
                playerRect.left += 64;
            }

            player.setTextureRect(playerRect);
            
        }
    } else if(object.getObjState() == objState::coin){
        
        if(elapsedTime > 0.07f)
            {
                if(coinRect.left == 54)
                {
                    coinRect.left = 0;
                } else {
                    coinRect.left += 9;
                }

                coin.setTextureRect(coinRect);
            }
    }
    clock.restart();
}

// BUTTON FUNCTIONS
/**
 * @brief Initialize Buttons
 * 
 * @param s 
 * @param position 
 * @param size 
 * @param color 
 */
void Objects::initButton(std::string s, std::string text, sf::IntRect rect, sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
    normalButton.loadFromFile("assets/button/normal.png");
    hoverButton.loadFromFile("assets/button/hover.png");
    clickButton.loadFromFile("assets/button/pressed.png");
    button.setTexture(normalButton);

    // temporary until final button is drawn. This will be used with the button.png from lab9 and is needed to rotate the button
    // to give the "pushed" look
    sf::Vector2u imageSize = normalButton.getSize();
    button.setOrigin(imageSize.x/2, imageSize.y/2);
    buttonPos = position;
    button.setPosition(buttonPos);

    //button color
    // buttonColor = color;
    // button.setColor(buttonColor);

    button.setScale(size);

    btnState = buttonState::normal;
}

/**
 * @brief Draw Button
 * 
 * @param target 
 * @param states 
 */
void Objects::drawButton(sf::RenderTarget& target,sf::RenderStates states) const
{
    target.draw(button, states);
    target.draw(buttonText, states);
}

/**
 * @brief Detect if mouse is over button
 * 
 * @param e 
 * @param window 
 */
void Objects::updateButton(sf::Event& e, sf::RenderWindow& window)
{
    //Allow window to be expanded without breaking
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

    bool mouseInButton =    worldPos.x >= button.getPosition().x - button.getGlobalBounds().width/2
                            && worldPos.x <= button.getPosition().x + button.getGlobalBounds().width/2
                            && worldPos.y >= button.getPosition().y - button.getGlobalBounds().height/2
                            && worldPos.y <= button.getPosition().y + button.getGlobalBounds().height/2;
    if(e.type == sf::Event::MouseMoved)
    {
        if(mouseInButton)
        {
            btnState = buttonState::hovered;
        }
        else
        {
            btnState = buttonState::normal;
        }
    }
    if (e.type == sf::Event::MouseButtonPressed)
    {
        if(e.mouseButton.button==sf::Mouse::Left)
        {
            if(mouseInButton)
            {
                btnState = buttonState::clicked;
            }
            else
            {
                btnState = buttonState::normal;
            }
        }
    }
    if (e.type == sf::Event::MouseButtonReleased)
    {
        if (e.mouseButton.button==sf::Mouse::Left)
        {
            if(mouseInButton)
            {
                btnState = buttonState::hovered;
            }
            else
            {
                btnState = buttonState::normal;
            }
        }
    }
    switch(btnState)
    {
        case buttonState::normal:
        {
            button.setTexture(normalButton);
            break;
        }
        case buttonState::hovered:
        {
            button.setTexture(hoverButton);
            break;
        }
        case buttonState::clicked:
        {
            button.setTexture(clickButton);
            break;
        }
    }
}