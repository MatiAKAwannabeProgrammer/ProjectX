#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "bullet.hpp"

class Enemy
{
private:
    sf::RectangleShape enemy;
    sf::Texture enemyTexture;
    sf::Vector2f moveDir, moveDirNorm, velocity;
    sf::FloatRect enemyBounds;
    int health;

    int randX, randY;

public:
    Enemy();
    void enemyMovement(float& deltaTime);
    void drawEnemy(sf::RenderWindow& window);
    void getEnemyPos();
    void calculations(sf::Vector2f& playerPos);
    void collision(std::vector<Enemy>& enemyVec, std::vector<Bullet>& bulletVec, int& score);
    sf::Vector2f enemyPos;
    
};
#endif
