#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

class Player
{
private:
    sf::Sprite player;
    sf::Texture playerTexture;
    float speed;

    float a, b, angle;

public:
    Player();
    void getPlayerPos(sf::Vector2f& currentPos);
    void playerMovement(float& deltaTime, sf::Vector2f& currentPos);
    void playerShooting(bool& isFired, sf::Time& bulletTime, sf::Clock& bulletClock, sf::Vector2f& velocity, sf::Vector2f& aimDirNorm);
    void drawPlayer(sf::RenderWindow& window);
    void playerRotate(sf::Vector2f& mousePos, sf::Vector2f& currentPos);

};
#endif
