#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Err.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "player.hpp"
#include "bullet.hpp"
#include "map.hpp"
#include "enemy.hpp"
#include <cmath>
#include <vector>

void calculations(sf::Vector2f& aimDir, sf::Vector2f& aimDirNorm, sf::Vector2f& currentPlayerPos, sf::Vector2f& mousePos);
void createBullet(sf::Vector2f, sf::Vector2f, std::vector<Bullet>&);
void updateBullet(std::vector<Bullet>&, float&);
void drawBullet(std::vector<Bullet>&, sf::RenderWindow&);
void createEnemy(std::vector<Enemy>&);
void updateEnemy(std::vector<Enemy>&, float&, sf::Vector2f&);
void drawEnemy(std::vector<Enemy>&, sf::RenderWindow&);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "PROJECT X");
    window.setFramerateLimit(60);

    Player player;
    sf::Vector2f currentPlayerPos;
    bool isFired = false;

    Map map;

    Enemy* enemyPtr;

    std::vector<Bullet> bulletVec;
    std::vector<Enemy> enemyVec;

    sf::Vector2f mousePos;
    sf::Vector2f aimDir, aimDirNorm, velocity;
    sf::Vector2f moveDir, moveDirNorm, enemyVelocity;

    sf::Clock deltaClock;
    sf::Clock bulletClock;
    sf::Clock enemyClock;
    float deltaTime;
    sf::Time bulletTime;
    sf::Time enemyTime;

    while (window.isOpen()){
        sf::Event event;

        // Start the clocks.
        deltaTime = deltaClock.restart().asSeconds();
        bulletTime = bulletClock.getElapsedTime();
        enemyTime = enemyClock.getElapsedTime();

        player.getPlayerPos(currentPlayerPos);
        mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear();
        
        calculations(aimDir, aimDirNorm, currentPlayerPos, mousePos);

        // Map.
        map.drawMap(window);

        //Player commands.
        player.playerMovement(deltaTime, currentPlayerPos);
        player.playerShooting(isFired, bulletTime, bulletClock, velocity, aimDirNorm);
        player.playerRotate(mousePos, currentPlayerPos);
        player.drawPlayer(window);

        // Bullet.
        if (isFired){
            createBullet(currentPlayerPos, velocity, bulletVec);
        }
        isFired = false;
        updateBullet(bulletVec, deltaTime);
        drawBullet(bulletVec, window);

        if (enemyTime.asMilliseconds() >= 550){
            createEnemy(enemyVec);
            enemyClock.restart();
        }
        updateEnemy(enemyVec, deltaTime, currentPlayerPos);
        drawEnemy(enemyVec, window);
        enemyPtr->collision(enemyVec, bulletVec);

        window.display();
    }
    return 0;
}

void calculations(sf::Vector2f& aimDir, sf::Vector2f& aimDirNorm, sf::Vector2f& currentPlayerPos, sf::Vector2f& mousePos)
{
    aimDir = mousePos - currentPlayerPos;
    aimDirNorm = aimDir / sqrtf(pow(aimDir.x, 2) + pow(aimDir.y, 2));
}

void createBullet(sf::Vector2f currentPlayerPos, sf::Vector2f velocity, std::vector<Bullet>& bulletVec)
{
    Bullet * bullet = new Bullet(currentPlayerPos, velocity);
    bulletVec.push_back(*bullet);
}

void updateBullet(std::vector<Bullet>& bulletVec, float& deltaTime)
{
    for (int i = 0; i < bulletVec.size(); i++){
        bulletVec[i].getBulletPos();
        bulletVec[i].moveBullet(deltaTime);

        if (bulletVec[i].bulletPos.x < 0 || bulletVec[i].bulletPos.x > 1600 ||
            bulletVec[i].bulletPos.y < 0 || bulletVec[i].bulletPos.y > 900){
            bulletVec.erase(bulletVec.begin() + i);
        }
    }
}

void drawBullet(std::vector<Bullet>& bulletVec, sf::RenderWindow& window)
{
    for (int i = 0; i < bulletVec.size(); i++){
        bulletVec[i].drawBullet(window);
    }
}

void createEnemy(std::vector<Enemy>& enemyVec)
{
    Enemy * enemy = new Enemy();
    enemyVec.push_back(*enemy);
}

void updateEnemy(std::vector<Enemy>& enemyVec, float& deltaTime, sf::Vector2f& currentPlayerPos)
{
    for (int i = 0; i < enemyVec.size(); i++){
        enemyVec[i].getEnemyPos();
        enemyVec[i].enemyMovement(deltaTime);
        enemyVec[i].calculations(currentPlayerPos);
    }
    
}

void drawEnemy(std::vector<Enemy>& enemyVec, sf::RenderWindow& window)
{
    for (int i = 0; i < enemyVec.size(); i++){
        enemyVec[i].drawEnemy(window);
    }
}
