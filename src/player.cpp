#include "player.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

Player::Player()
{
    playerTexture.loadFromFile("./content/player.png");
    player.setTexture(playerTexture);
    player.setPosition(sf::Vector2f(800.f, 400.f));
    speed = 200.f;
    player.scale(2.f, 2.f);
    player.setRotation(0);
    player.setOrigin(player.getTexture()->getSize().x/2, player.getTexture()->getSize().y/2);
}

void Player::drawPlayer(sf::RenderWindow& window)
{
    window.draw(player);
}

void Player::getPlayerPos(sf::Vector2f& currentPos)
{
    currentPos = player.getPosition();
}

void Player::playerMovement(float& deltaTime, sf::Vector2f& playerPos)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && playerPos.y + player.getLocalBounds().height/2 > 20){
        player.move(0, -speed * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && playerPos.y + player.getLocalBounds().height/2 < 890){
        player.move(0, speed * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && playerPos.x + player.getLocalBounds().width/2 > 20){
        player.move(-speed * deltaTime, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && playerPos.x + player.getLocalBounds().width/2 < 1580){
        player.move(speed * deltaTime, 0);
    }
}

void Player::playerShooting(bool& isFired, sf::Time& bulletTime, sf::Clock& bulletClock, sf::Vector2f& velocity, sf::Vector2f& aimDirNorm)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bulletTime.asMilliseconds() >= 100){
        isFired = true;
        velocity = aimDirNorm * 1000.f;
        bulletClock.restart();
    }
}

void Player::playerRotate(sf::Vector2f& mousePos, sf::Vector2f& currentPos)
{
    a = mousePos.x - currentPos.x;
    b = mousePos.y - currentPos.y;
    angle = -atan2(a, b) * 180 / 3.14159;
    player.setRotation(angle);
}
