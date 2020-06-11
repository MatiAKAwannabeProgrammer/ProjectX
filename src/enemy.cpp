#include "enemy.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

Enemy::Enemy(bool isBoss)
{
    randX = (rand() % 1550) + 1;
    randY = (rand() % 850) + 1;
    enemy.setPosition(randX, randY);
    //enemyTexture.loadFromFile("./content/enemy.png");
    if (isBoss){
        enemy.setSize(sf::Vector2f(40, 40));
        health = 15;
        enemy.setFillColor(sf::Color::Cyan);
    }else{
        enemy.setSize(sf::Vector2f(20, 20));
        health = 3;
        enemy.setFillColor(sf::Color::Red);
    }
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

void Enemy::collision(std::vector<Enemy>& enemyVec, std::vector<Bullet>& bulletVec, std::vector<Enemy>& bossVec, int& scoreInt)
{
    for (int i = 0; i < enemyVec.size(); i++)
    for (int j = 0; j < bulletVec.size(); j++){
        // Regular enemy.
        if (enemyVec[i].enemyBounds.contains(bulletVec[j].bulletPos)){
            bulletVec.erase(bulletVec.begin() + j);
            enemyVec[i].health -= 1;
        }     
        if (enemyVec[i].health <= 0 ){
            enemyVec.erase(enemyVec.begin() + i);
            scoreInt++;
        }
    }
    for (int i = 0; i < bossVec.size(); i++)
    for (int j = 0; j < bulletVec.size(); j++){
        // Regular enemy.
        if (bossVec[i].enemyBounds.contains(bulletVec[j].bulletPos)){
            bulletVec.erase(bulletVec.begin() + j);
            bossVec[i].health -= 1;
        }     
        if (bossVec[i].health <= 0 ){
            bossVec.erase(bossVec.begin() + i);
            scoreInt++;
        }
    }
}

void Enemy::enemyAttack(std::vector<Enemy>& enemyVec, std::vector<Enemy>& bossVec, sf::Vector2f& playerPos, int& healthInt)
{
    for (int i = 0; i < enemyVec.size(); i++){
        if (enemyVec[i].enemyBounds.contains(playerPos)){
            healthInt--;
            enemyVec.erase(enemyVec.begin() + i); 
        }
    }
    for (int i = 0; i < bossVec.size(); i++){
        if (bossVec[i].enemyBounds.contains(playerPos)){
            healthInt--;
            bossVec.erase(bossVec.begin() + i); 
        }
    }
}
