#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <time.h>
using namespace std;
using namespace sf;

class Bullet {
public:


    sf::CircleShape shape;
    sf::Vector2f velocity;
    float maxSpeed;

    Bullet(float radius = 12.0f)
        : velocity(0.f, 0.f), maxSpeed(1.f)
    {
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Yellow);
    }
};


class Game {
public:
    Game() : window(sf::VideoMode(800, 600), "Game Window") {
        if (!dragonTexture.loadFromFile("img/dragon.png")) {
            // Handle error loading dragon texture
        }
        dragonSprite.setTexture(dragonTexture);
        dragonSprite.setScale(100.0f / dragonTexture.getSize().x, 100.0f / dragonTexture.getSize().y);
        dragonSprite.setPosition(375, 50);



        if (!backgroundTexture.loadFromFile("img/bg.jpg")) {
            // Handle error loading background texture
        }
        backgroundSprite.setTexture(backgroundTexture);



        if (!playerTexture.loadFromFile("img/player.png")) {
            // Handle error loading player texture
        }
        playerSprite.setTexture(playerTexture);
        playerSprite.setScale(100.0f / playerTexture.getSize().x, 100.0f / playerTexture.getSize().y);
        playerSprite.setPosition(350, 500);

        if (!opponentTexture.loadFromFile("img/opponent.png")) {
            // Handle error loading opponent texture
        }
        opponent1Sprite.setTexture(opponentTexture);
        opponent1Sprite.setScale(100.0f / opponentTexture.getSize().x, 100.0f / opponentTexture.getSize().y);
        opponent1Sprite.setPosition(200, 50);

        opponent2Sprite.setTexture(opponentTexture);
        opponent2Sprite.setScale(100.0f / opponentTexture.getSize().x, 100.0f / opponentTexture.getSize().y);
        opponent2Sprite.setPosition(375, 50);

        opponent3Sprite.setTexture(opponentTexture);
        opponent3Sprite.setScale(100.0f / opponentTexture.getSize().x, 100.0f / opponentTexture.getSize().y);
        opponent3Sprite.setPosition(550, 50);

        std::vector<Bullet> bullets;

    }

    void run() {
        sf::Font font;
        font.loadFromFile("arial.ttf");

        sf::Text Heading("Space Shooter Game", font, 80);
        Heading.setPosition(200, 70);

        sf::Text playButton("Play", font, 50);
        playButton.setPosition(200, 180);

        sf::Text instructionsButton("Instructions", font, 30);
        instructionsButton.setPosition(200, 250);

        sf::Text instructionsheading("Instructions", font, 50);
        instructionsheading.setPosition(20, 20);

        sf::Text Instructions1("The player of the Game can move in all possible directions", font, 20);
        Instructions1.setPosition(30, 80);
        sf::Text Instructions2("(right, left, up, down, and diagonally.The player can ", font, 20);
        Instructions2.setPosition(30, 120);
        sf::Text Instructions3("only fire to destroy the enemies.The player can also ", font, 20);
        Instructions3.setPosition(30, 160);
        sf::Text Instructions4("avail the add - ons options which would come after random", font, 20);
        Instructions4.setPosition(30, 200);
        sf::Text Instructions5("intervals.", font, 20);
        Instructions5.setPosition(30, 240);


        sf::Text InstructionsBack("Back.", font, 30);
        InstructionsBack.setPosition(30, 550);



        sf::Text highScoreButton("High Score and Players Names Display", font, 30);
        highScoreButton.setPosition(200, 300);

        sf::Text endButton("End", font, 30);
        endButton.setPosition(200, 350);


        sf::Text gameOverText("Game Over", font, 30);
        gameOverText.setPosition(200, 200);

        sf::Text playAgainButton("Play Again", font, 50);
        playAgainButton.setPosition(200, 240);

        sf::Text backButton("Back To the Main Menu", font, 30);
        backButton.setPosition(200, 320);


        sf::Text  Score("Score: 0 ", font, 25);
        Score.setPosition(20, 20);

        sf::Text Lives("Lifes: 3", font, 20);
        Lives.setPosition(700, 20);


        GameState currentState = GameState::MainMenu;


        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                        if (currentState == GameState::MainMenu) {
                            if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                currentState = GameState::GamePlay;
                            }
                            else if (instructionsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                currentState = GameState::Instructions;
                            }
                            else if (highScoreButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                currentState = GameState::HighScores;
                            }
                            else if (endButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                window.close();
                            }
                        }
                        else if (currentState == GameState::GamePlay) {
                            // Handle game logic and input
                            handlePlayerMovement();
                            opponentMovement();

                        }
                        else if (currentState == GameState::GameOver)
                        {
                            if (playAgainButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                currentState = GameState::GamePlay;
                            }
                            else if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                currentState = GameState::MainMenu;
                            }


                        }
                        else if (currentState == GameState::Instructions)
                        {
                            if (InstructionsBack.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                currentState = GameState::MainMenu;
                            }


                        }
                    }
                }
            }

            window.clear();

            if (currentState == GameState::MainMenu) {
                window.draw(backgroundSprite);
                window.draw(playButton);
                window.draw(instructionsButton);
                window.draw(highScoreButton);
                window.draw(endButton);
                
            }
            else if (currentState == GameState::GamePlay) {
                // Draw game objects

                window.draw(backgroundSprite);
                window.draw(Lives);
                window.draw(Score);

                


                if (cx.getElapsedTime().asSeconds() >= 6) {
                    window.draw(opponent1Sprite);
                    window.draw(opponent2Sprite);
                    window.draw(opponent3Sprite);

                    
                    opponentMovement();


                    


                    if (collision == true)
                    {
                        collision == false;
                        cout << "working";
                        currentState = GameState::GameOver;

                    }

                    checkCollisionofplayerbullets();
                    for (const auto& bullet : opponentBullets) {
                        window.draw(bullet.shape);
                    }

                    updateBullets();
                    for (const auto& bullet : bullets) {
                        window.draw(bullet.shape);
                    }

                    checkCollisionofPlayer();
                    checkCollisionWithPlayer();
                    

                }
               

               
                 if(score2==10)
                 { 
                     Score.setString("Score " + to_string(score));
                 }
                 else if (score2 == 20)
                 {
                     Score.setString("Score " + to_string(score));
                 }
                 else if (score2 == 30)
                 {
                     Score.setString("Score " + to_string(score));
                 }
             
                
                
                window.draw(playerSprite);
                updateBullets();
                handlePlayerMovement();
                

                if (life == 62) {
                    Lives.setString("Lifes: " + to_string(2));
                }
                if (life ==124) {
                    Lives.setString("Lifes: " + to_string(1));
                }
                



                if (hasDragon == true || dragontimer.getElapsedTime().asSeconds() >= 60) {

                    // Remove other opponents
                    opponent1Sprite.setPosition(2000.f, 2000.f);
                    opponent2Sprite.setPosition(2000.f, 2000.f);
                    opponent3Sprite.setPosition(2000.f, 2000.f);
                }
                if (hasDragon) {
                    handleDragonMovement();
                    window.draw(dragonSprite);
                    checkCollisionWithDragon();
                }


            }
            else if (currentState == GameState::GameOver) {
                playerSprite.setPosition(350, 500);

                window.draw(gameOverText);
                window.draw(playAgainButton);
                window.draw(backButton);





            }
            else if (currentState == GameState::Instructions) {
                // Draw instructions screen
                window.draw(backgroundSprite);
                window.draw(instructionsheading);
                window.draw(Instructions1);
                window.draw(Instructions2);
                window.draw(Instructions3);
                window.draw(Instructions4);
                window.draw(Instructions5);
                window.draw(InstructionsBack);








            }
            else if (currentState == GameState::HighScores) {
                // Draw high scores and players' names screen
            }


            window.display();
        }
    }

private:
    enum class GameState {
        MainMenu,
        GamePlay,
        Instructions,
        HighScores,
        GameOver
    };

    int opponentsCount;

    int life = 0;
    int score=0;
    int score2 = 0;

    

    Clock c1;
    Clock c2;
    Clock c3;
    Clock c4;
    vector<RectangleShape> b;

    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    sf::Texture opponentTexture;
    sf::Sprite opponent1Sprite;
    sf::Sprite opponent2Sprite;
    sf::Sprite opponent3Sprite;
    bool collision = false;
    std::vector<Bullet> bullets;
    std::vector<Bullet> opponentBullets;
    sf::Clock fireClock;
    sf::Clock fireClock1;
    sf::Clock fireClock2;
    sf::Clock fireClock3;
    // Clock for tracking the time between opponent shots
    sf::Time fireInterval = sf::seconds(2);

    bool hasDragon = false;
    sf::Texture dragonTexture;
    sf::Sprite dragonSprite;




    bool opponent1MovingRight = true;
    bool opponent2MovingRight = true;
    bool opponent3MovingRight = true;

    Clock dragontimer;
    Clock dragonC;
    Clock cx;
    int count = 0;



   

   












    void checkCollisionWithPlayer() {
        // Get the bounding rectangle of the player sprite
        sf::FloatRect playerBounds = playerSprite.getGlobalBounds();

        // Check for collision between opponent bullets and the player
        for (const auto& bullet : opponentBullets) {
            sf::FloatRect bulletBounds = bullet.shape.getGlobalBounds();

            if (bulletBounds.intersects(playerBounds)) {
                // Collision detected, end the program
                
                    count += 1;
                    life += 1;


                  
                if (count == 140) {
                    
                    collision = true;
                    count = 0;

                }
                
                
               

            }
        }
    }



    void checkCollisionofplayerbullets() {
        // Check collision between player bullets and opponents
        for (size_t i = 0; i < bullets.size(); i++) {
            sf::FloatRect bulletBounds = bullets[i].shape.getGlobalBounds();

            if (opponent1Sprite.getGlobalBounds().intersects(bulletBounds)) {
                // Remove opponent1
                opponent1Sprite.setPosition(2000.f, 2000.f); // Move off-screen
                bullets.erase(bullets.begin() + i); // Remove bullet
                i--;
                opponentsCount += 1;
                score2 = 10;
                score += 10;
                
            }
            else if (opponent2Sprite.getGlobalBounds().intersects(bulletBounds)) {
                // Remove opponent2
                opponent2Sprite.setPosition(2000.f, 2000.f); // Move off-screen
                bullets.erase(bullets.begin() + i); // Remove bullet
                i--;
                opponentsCount += 1;
                score2 = 20;
                score += 10;
            }
            else if (opponent3Sprite.getGlobalBounds().intersects(bulletBounds)) {
                // Remove opponent3
                opponent3Sprite.setPosition(2000.f, 2000.f); // Move off-screen
                bullets.erase(bullets.begin() + i); // Remove bullet
                i--;
                opponentsCount += 1;
                score2 = 30;
                score += 10;
            }

        }

        if (opponentsCount == 3)
        {
            hasDragon = true;
        }




    }
    void handlePlayerMovement() {

        // Player movement controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            playerSprite.move(-1, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            playerSprite.move(1, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            playerSprite.move(0, -1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            playerSprite.move(0, 1);

        // Ensure the player stays within the window boundaries
        if (playerSprite.getPosition().x < 0) {
            playerSprite.setPosition(0, playerSprite.getPosition().y);
        }

        if (playerSprite.getPosition().x > 720) {
            playerSprite.setPosition(720, playerSprite.getPosition().y);
        }

        if (playerSprite.getPosition().y < 0) {
            playerSprite.setPosition(playerSprite.getPosition().x, 0);
        }

        if (playerSprite.getPosition().y > 520) {
            playerSprite.setPosition(playerSprite.getPosition().x, 520);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

            if (c4.getElapsedTime().asSeconds() >= 0.5) {
                Bullet bullet;
                bullet.shape.setPosition(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2.f, playerSprite.getPosition().y);
                bullet.velocity.y = -bullet.maxSpeed;
                bullets.push_back(bullet);
                c4.restart();
            }
        }

    }
    void updateBullets() {
        int bulletsFired = 0; // Counter for the number of bullets fired in a second

        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].shape.move(bullets[i].velocity);

            // Remove the bullet if it goes off-screen
            if (bullets[i].shape.getPosition().y + bullets[i].shape.getGlobalBounds().height < 0) {
                bullets.erase(bullets.begin() + i);
                i--;
            }
        }

        for (size_t i = 0; i < opponentBullets.size(); i++) {
            opponentBullets[i].shape.move(opponentBullets[i].velocity);

            // Remove the bullet if it goes off-screen
            if (opponentBullets[i].shape.getPosition().y > window.getSize().y) {
                opponentBullets.erase(opponentBullets.begin() + i);
                i--;
            }
        }

        // Limit the number of bullets fired per second
        if (bulletsFired >= 2) {
            return; // Exit the function if the maximum number of bullets is reached
        }

        // Check if it's time to fire a new bullet
        if (fireClock.getElapsedTime() >= fireInterval) {
            // Create a new bullet
            Bullet newBullet;
            // Set the position and velocity of the bullet
            // ...
            // Add the bullet to the bullets vector
            bullets.push_back(newBullet);

            // Increase the bulletsFired counter
            bulletsFired++;

            // Restart the fire clock
            fireClock.restart();
        }
    }





    void checkCollisionofPlayer() {


        // Get the bounding rectangles of the player and opponents
        sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
        sf::FloatRect opponent1Bounds = opponent1Sprite.getGlobalBounds();
        sf::FloatRect opponent2Bounds = opponent2Sprite.getGlobalBounds();
        sf::FloatRect opponent3Bounds = opponent3Sprite.getGlobalBounds();



        // Check for collision between player and opponents
        if (playerBounds.intersects(opponent1Bounds)
            || playerBounds.intersects(opponent2Bounds)
            || playerBounds.intersects(opponent3Bounds)) {
            // Game over logic

            collision = true;
        }
    }


    void opponentMovement() {

        // Update opponent1 movement
        if (opponent1MovingRight) {
            opponent1Sprite.move(2.0f, 0.0f);
            if (opponent1Sprite.getPosition().x > 800 - opponent1Sprite.getGlobalBounds().width) {
                opponent1MovingRight = false;
            }
        }
        else {
            opponent1Sprite.move(-2.0f, 0.0f);
            if (opponent1Sprite.getPosition().x < 0) {
                opponent1MovingRight = true;
            }
        }

        // Update opponent2 movement
        if (opponent2MovingRight) {
            opponent2Sprite.move(2.0f, 0.0f);
            if (opponent2Sprite.getPosition().x > 800 - opponent2Sprite.getGlobalBounds().width) {
                opponent2MovingRight = false;
            }
        }
        else {
            opponent2Sprite.move(-2.0f, 0.0f);
            if (opponent2Sprite.getPosition().x < 0) {
                opponent2MovingRight = true;
            }
        }

        // Update opponent3 movement
        if (opponent3MovingRight) {
            opponent3Sprite.move(2.0f, 0.0f);
            if (opponent3Sprite.getPosition().x > 800 - opponent3Sprite.getGlobalBounds().width) {
                opponent3MovingRight = false;
            }
        }
        else {
            opponent3Sprite.move(-2.0f, 0.0f);
            if (opponent3Sprite.getPosition().x < 0) {
                opponent3MovingRight = true;
            }
        }





        // Opponent firing logic


        if (c1.getElapsedTime().asSeconds() >= 2)
        {
            // Create bullet for opponent 1
            Bullet opponent1Bullet;
            opponent1Bullet.shape.setPosition(opponent1Sprite.getPosition().x + opponent1Sprite.getGlobalBounds().width / 2.f, opponent1Sprite.getPosition().y + opponent1Sprite.getGlobalBounds().height);
            opponent1Bullet.velocity.y = opponent1Bullet.maxSpeed;
            opponentBullets.push_back(opponent1Bullet);
            c1.restart();

            // Restart the fire clock for opponent 1

        }
        if (c2.getElapsedTime().asSeconds() >= 3)
        {
            // Create bullet for opponent 1
            Bullet opponent2Bullet;
            opponent2Bullet.shape.setPosition(opponent2Sprite.getPosition().x + opponent2Sprite.getGlobalBounds().width / 2.f, opponent2Sprite.getPosition().y + opponent2Sprite.getGlobalBounds().height);
            opponent2Bullet.velocity.y = opponent2Bullet.maxSpeed;
            opponentBullets.push_back(opponent2Bullet);
            c2.restart();

            // Restart the fire clock for opponent 1

        }
        if (c3.getElapsedTime().asSeconds() >= 5)
        {
            // Create bullet for opponent 1
            Bullet opponent3Bullet;
            opponent3Bullet.shape.setPosition(opponent3Sprite.getPosition().x + opponent3Sprite.getGlobalBounds().width / 2.f, opponent3Sprite.getPosition().y + opponent3Sprite.getGlobalBounds().height);
            opponent3Bullet.velocity.y = opponent3Bullet.maxSpeed;
            opponentBullets.push_back(opponent3Bullet);
            c3.restart();

            // Restart the fire clock for opponent 1

        }



    }
    void oppbulletshape()
    {

    }



    void handleDragonMovement() {
        const float dragonSpeed = 2.0f;

        // Randomly select a direction for the Dragon opponent
        int directionX = (rand() % 3) - 1; // -1, 0, or 1
        int directionY = (rand() % 3) - 1; // -1, 0, or 1

        // Calculate the new position for the Dragon
        float newPosX = dragonSprite.getPosition().x + (dragonSpeed * directionX);
        float newPosY = dragonSprite.getPosition().y + (dragonSpeed * directionY);


        if (dragonC.getElapsedTime().asSeconds() >= 2)
        {
            // Create bullet for opponent 1
            Bullet opponent4Bullet;
            opponent4Bullet.shape.setPosition(dragonSprite.getPosition().x + dragonSprite.getGlobalBounds().width / 2.f, dragonSprite.getPosition().y + dragonSprite.getGlobalBounds().height);
            opponent4Bullet.velocity.y = opponent4Bullet.maxSpeed;
            opponentBullets.push_back(opponent4Bullet);
            dragonC.restart();

            // Restart the fire clock for opponent 1

        }

        // Keep the Dragon within the screen boundaries


        if (dragonSprite.getPosition().x < 0) {
            dragonSprite.setPosition(0, dragonSprite.getPosition().y);
        }

        if (dragonSprite.getPosition().x > 720) {
            dragonSprite.setPosition(720, dragonSprite.getPosition().y);
        }

        if (dragonSprite.getPosition().y < 0) {
            dragonSprite.setPosition(dragonSprite.getPosition().x, 0);
        }

        if (dragonSprite.getPosition().y > 520) {
            dragonSprite.setPosition(dragonSprite.getPosition().x, 520);
        }


        // Set the new position for the Dragon
        dragonSprite.setPosition(newPosX, newPosY);
    }

    void checkCollisionWithDragon() {
        // Get the bounding rectangle of the player and Dragon
        sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
        sf::FloatRect dragonBounds = dragonSprite.getGlobalBounds();

        // Check for collision between player and Dragon
        if (playerBounds.intersects(dragonBounds)) {
            // Game over logic
            collision = true;
        }
    }





};

int main() {
    Game game;
    game.run();

    return 0;
}
