#include "bullet.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

Bullet::Bullet(sf::Vector2f& playerPos, sf::Vector2f& velocity, bool& hasBonus)
{
    bullet.setPosition(playerPos);
    if (hasBonus){
        bulletTexture.loadFromFile("./content/bullet2.png");
    }else{
        bulletTexture.loadFromFile("./content/bullet.png");
    }
    bullet.setTexture(bulletTexture);
    this->velocity = velocity;
}

void Bullet::drawBullet(sf::RenderWindow& window)
{
    window.draw(bullet);
}

void Bullet::moveBullet(float& deltaTime)
{
    bullet.move(velocity * deltaTime);
}

void Bullet::getBulletPos()
{
    bulletPos = bullet.getPosition();
}
