#ifndef BOSS_HPP
#define BOSS_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <cmath>
#include "bullet.hpp"

class Boss
{
private:
    sf::RectangleShape boss;
    sf::Texture bossTexture;
    sf::Vector2f moveDir, moveDirNorm, velocity;
    sf::FloatRect bossBounds;
    int health;

    int randX, randY;

public:
    Boss();
    void bossMovement(float& deltaTime);
    void drawBoss(sf::RenderWindow& window);
    void getBossPos();
    void calculations(sf::Vector2f& playerPos);
    void collision(std::vector<Boss>& bossVec, std::vector<Bullet>& bulletVec, int& scoreInt);
    sf::Vector2f bossPos;

};
#endif
