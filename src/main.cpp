#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Err.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "player.hpp"
#include "bullet.hpp"
#include "map.hpp"
#include "enemy.hpp"
#include "boss.hpp"
#include "textClass.hpp"

#include <cmath>
#include <vector>

void calculations(sf::Vector2f&, sf::Vector2f&, sf::Vector2f&, sf::Vector2f&);
void createBullet(sf::Vector2f, sf::Vector2f, std::vector<Bullet>&);
void updateBullet(std::vector<Bullet>&, float&);
void drawBullet(std::vector<Bullet>&, sf::RenderWindow&);
void createEnemy(std::vector<Enemy>&, int&, bool&);
void updateEnemy(std::vector<Enemy>&, float&, sf::Vector2f&);
void drawEnemy(std::vector<Enemy>&, sf::RenderWindow&);
void createBoss(std::vector<Boss>&, int&, bool&);
void updateBoss(std::vector<Boss>&, float&, sf::Vector2f&);
void drawBoss(std::vector<Boss>&, sf::RenderWindow&);


int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "PROJECT X");
    window.setFramerateLimit(60);
    int maxEnemies = 10;
    int enemyCount = 0;
    int maxBosses = 1;
    int bossCount = 0;
    int healthInt = 3;
    int scoreInt = 0;
    bool roundInProgress = false;
    bool gameIsPaused = true;

    Player player;
    sf::Vector2f currentPlayerPos;
    bool isFired = false;

    TextClass score;
    TextClass menu;

    Map map;

    Enemy * enemyPtr;
    Boss * bossPtr;

    std::vector<Bullet> bulletVec;
    std::vector<Enemy> enemyVec;
    std::vector<Boss> bossVec;

    sf::Vector2f mousePos;
    sf::Vector2f aimDir, aimDirNorm, velocity;
    sf::Vector2f moveDir, moveDirNorm, enemyVelocity;

    sf::Clock deltaClock;
    sf::Clock bulletClock;
    sf::Clock enemyClock;
    sf::Clock restartClock;
    sf::Clock bossClock;
    float deltaTime;
    sf::Time bulletTime;
    sf::Time enemyTime;
    sf::Time restartTime;
    sf::Time bossTime;

    while (window.isOpen()){
        sf::Event event;

        // Start the clocks.
        deltaTime = deltaClock.restart().asSeconds();
        bulletTime = bulletClock.getElapsedTime();
        enemyTime = enemyClock.getElapsedTime();
        bossTime = bossClock.getElapsedTime();
        restartTime = restartClock.getElapsedTime();

        player.getPlayerPos(currentPlayerPos);
        mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (gameIsPaused && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                window.close();
            }
            if (gameIsPaused && sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                gameIsPaused = false;
            }
            
        }
        window.clear();
        
        calculations(aimDir, aimDirNorm, currentPlayerPos, mousePos);
        if (gameIsPaused){
            menu.drawMenu(window);
        }
        if (!gameIsPaused){
            // Map.
            map.drawMap(window);

            // Player commands.
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
            if (restartTime.asSeconds() >= 5 && !roundInProgress){
                roundInProgress = true;
            }
            if (enemyTime.asMilliseconds() >= 550 && enemyCount < maxEnemies && roundInProgress){
                createEnemy(enemyVec, enemyCount, roundInProgress);
                enemyClock.restart();
            }
            if (bossTime.asMilliseconds() >= 5000 && bossCount < maxBosses && roundInProgress){
                createBoss(bossVec, bossCount, roundInProgress);
                bossClock.restart();
            }
            if (enemyVec.size() == 0 && bossVec.size() == 0 && roundInProgress){
                roundInProgress = false; // Created so that every time all enemies are dead
                enemyCount = 0;         // even at round start the maxEnemies isn't increased.
                bossCount = 0;
                maxEnemies += 7;
                maxBosses += 2;
                restartClock.restart();
            }

            updateEnemy(enemyVec, deltaTime, currentPlayerPos);
            drawEnemy(enemyVec, window);
            enemyPtr->collision(enemyVec, bulletVec, scoreInt);

            updateBoss(bossVec, deltaTime, currentPlayerPos);
            drawBoss(bossVec, window);
            bossPtr->collision(bossVec, bulletVec, scoreInt);

            score.drawScore(window, scoreInt);


        }
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

void createEnemy(std::vector<Enemy>& enemyVec, int& enemyCount, bool& roundInProgress)
{
    Enemy * enemy = new Enemy();
    enemyVec.push_back(*enemy);
    enemyCount++;
    roundInProgress = true;
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
void createBoss(std::vector<Boss>& bossVec, int& bossCount, bool& roundInProgress)
{
    Boss * boss = new Boss();
    bossVec.push_back(*boss);
    bossCount++;
    roundInProgress = true;
}

void updateBoss(std::vector<Boss>& bossVec, float& deltaTime, sf::Vector2f& currentPlayerPos)
{
    for (int i = 0; i < bossVec.size(); i++){
        bossVec[i].getBossPos();
        bossVec[i].bossMovement(deltaTime);
        bossVec[i].calculations(currentPlayerPos);
    }
}

void drawBoss(std::vector<Boss>& bossVec, sf::RenderWindow& window)
{
    for (int i = 0; i < bossVec.size(); i++){
        bossVec[i].drawBoss(window);
    }
}
