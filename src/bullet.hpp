#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
class Bullet
{
private:
    sf::Sprite bullet;
    sf::Texture bulletTexture;
    sf::Vector2f velocity;

public:
    Bullet(sf::Vector2f& playerPos, sf::Vector2f& velocity);
    void drawBullet(sf::RenderWindow& window);
    void moveBullet(float& deltaTime);
    void getBulletPos();
    sf::Vector2f bulletPos;

};
#endif
