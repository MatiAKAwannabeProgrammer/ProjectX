#include "boss.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

Boss::Boss()
{
    randX = (rand() % 1550) + 1;
    randY = (rand() % 850) + 1;
    boss.setFillColor(sf::Color::Cyan);
    boss.setSize(sf::Vector2f(40, 40));
    boss.setPosition(randX, randY);
    health = 15;
}
void Boss::drawBoss(sf::RenderWindow& window)
{
    window.draw(boss);
}

void Boss::bossMovement(float& deltaTime)
{
    boss.move(velocity * deltaTime);    
    bossBounds = boss.getGlobalBounds();
}

void Boss::getBossPos()
{
    bossPos = boss.getPosition();
}

void Boss::calculations(sf::Vector2f& playerPos)
{
    moveDir = playerPos - bossPos;
    moveDirNorm = moveDir / sqrtf(pow(moveDir.x, 2) + pow(moveDir.y, 2));
    velocity = moveDirNorm * 100.f;
}

void Boss::collision(std::vector<Boss>& bossVec, std::vector<Bullet>& bulletVec, int& scoreInt)
{
    for (int i = 0; i < bossVec.size(); i++)
    for (int j = 0; j < bulletVec.size(); j++){
        if (bossVec[i].bossBounds.contains(bulletVec[j].bulletPos)){
            bulletVec.erase(bulletVec.begin() + j);
            bossVec[i].health -= 1;
        }     
        if (bossVec[i].health <= 0 ){
            bossVec.erase(bossVec.begin() + i);
            scoreInt += 3;
        }
    }
}
