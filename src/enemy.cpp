#include "enemy.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

Enemy::Enemy()
{
    randX = (rand() % 1550) + 1;
    randY = (rand() % 850) + 1;
    enemy.setFillColor(sf::Color::Red);
    enemy.setSize(sf::Vector2f(20, 20));
    enemy.setPosition(randX, randY);
    //enemyTexture.loadFromFile("./content/enemy.png");
    health = 3;
}

void Enemy::drawEnemy(sf::RenderWindow& window)
{
    window.draw(enemy);
}

void Enemy::enemyMovement(float& deltaTime)
{
    enemy.move(velocity * deltaTime);    
    enemyBounds = enemy.getGlobalBounds();
}

void Enemy::getEnemyPos()
{
    enemyPos = enemy.getPosition();
}

void Enemy::calculations(sf::Vector2f& playerPos)
{
    moveDir = playerPos - enemyPos;
    moveDirNorm = moveDir / sqrtf(pow(moveDir.x, 2) + pow(moveDir.y, 2));
    velocity = moveDirNorm * 100.f;
}

void Enemy::collision(std::vector<Enemy>& enemyVec, std::vector<Bullet>& bulletVec, int& score)
{
    for (int i = 0; i < enemyVec.size(); i++)
    for (int j = 0; j < bulletVec.size(); j++){
        if (enemyVec[i].enemyBounds.contains(bulletVec[j].bulletPos)){
            bulletVec.erase(bulletVec.begin() + j);
            enemyVec[i].health -= 1;
        }     
        if (enemyVec[i].health <= 0 ){
            enemyVec.erase(enemyVec.begin() + i);
            score++;
        }
    }
}
