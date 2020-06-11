#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
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
#include "textClass.hpp"
#include "pickupClass.hpp"

#include <cmath>
#include <vector>

void calculations(sf::Vector2f&, sf::Vector2f&, sf::Vector2f&, sf::Vector2f&);
void createBullet(sf::Vector2f, sf::Vector2f, std::vector<Bullet>&, bool&);
void updateBullet(std::vector<Bullet>&, float&);
void drawBullet(std::vector<Bullet>&, sf::RenderWindow&);
void createEnemy(std::vector<Enemy>&, int&, bool&);
void updateEnemy(std::vector<Enemy>&, float&, sf::Vector2f&);
void drawEnemy(std::vector<Enemy>&, sf::RenderWindow&);
void createBoss(std::vector<Enemy>&, int&, bool&);
void updateBoss(std::vector<Enemy>&, float&, sf::Vector2f&);
void drawBoss(std::vector<Enemy>&, sf::RenderWindow&);
void createHPickup(std::vector<PickupClass>&);
void drawHPickup(std::vector<PickupClass>&, sf::RenderWindow&);
void createAPickup(std::vector<PickupClass>&);
void drawAPickup(std::vector<PickupClass>&, sf::RenderWindow& window);
void resetMatch(std::vector<Enemy>&, std::vector<Enemy>&, int&, int&);


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
    bool hasBonus = false;
    // Player.
    Player player;
    sf::Vector2f currentPlayerPos;
    bool isFired = false;
    //Text Class.
    TextClass score;
    TextClass health;
    TextClass menu;
    // Map.
    Map map;
    // Class pointers
    Enemy * enemyPtr;
    PickupClass * pickupPtr;
    // Vectors
    std::vector<Bullet> bulletVec;
    std::vector<Enemy> enemyVec;
    std::vector<Enemy> bossVec;
    std::vector<PickupClass> healthVec;
    std::vector<PickupClass> ammoVec;
    // Movement variables.
    sf::Vector2f mousePos;
    sf::Vector2f aimDir, aimDirNorm, velocity;
    sf::Vector2f moveDir, moveDirNorm, enemyVelocity;
    // Time/clocks.
    sf::Clock deltaClock;
    sf::Clock bulletClock;
    sf::Clock enemyClock;
    sf::Clock restartClock;
    sf::Clock bossClock;
    sf::Clock hpClock;
    sf::Clock ammoClock;
    sf::Clock bonusClock;
    float deltaTime;
    sf::Time bulletTime;
    sf::Time enemyTime;
    sf::Time restartTime;
    sf::Time bossTime;
    sf::Time hpTime;
    sf::Time ammoTime;
    sf::Time bonusTime;
    //Game loop.
    while (window.isOpen()){
        sf::Event event;
        // Start the clocks.
        deltaTime = deltaClock.restart().asSeconds();
        bulletTime = bulletClock.getElapsedTime();
        enemyTime = enemyClock.getElapsedTime();
        bossTime = bossClock.getElapsedTime();
        restartTime = restartClock.getElapsedTime();
        hpTime = hpClock.getElapsedTime();
        ammoTime = ammoClock.getElapsedTime();
        // Update positions.
        player.getPlayerPos(currentPlayerPos);
        mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
        //Poll Events.
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (gameIsPaused && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                window.close();
            }
            if (gameIsPaused && sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
                gameIsPaused = false;
                resetMatch(enemyVec, bossVec, scoreInt, healthInt);                
            }
            
        }
        window.clear();
        
        calculations(aimDir, aimDirNorm, currentPlayerPos, mousePos);
        if (healthInt <= 0){
            gameIsPaused = true;
        }
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
                createBullet(currentPlayerPos, velocity, bulletVec, hasBonus);
            }
            isFired = false;
            updateBullet(bulletVec, deltaTime);
            drawBullet(bulletVec, window);
            if (hasBonus){
                bonusTime = bonusClock.getElapsedTime();
            }
            if (bonusTime.asSeconds() >= 3){
                hasBonus = false; 
                bonusClock.restart();
            }
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
            if (hpTime.asSeconds() >= 15){
                createHPickup(healthVec);
                hpClock.restart();
            }
            if (ammoTime.asSeconds() >= 10){
                createAPickup(ammoVec);
                ammoClock.restart();
            }
            // EnemyUpdates.
            updateEnemy(enemyVec, deltaTime, currentPlayerPos);
            drawEnemy(enemyVec, window);
            if (enemyVec.size() > 0 || bossVec.size() > 0){
                enemyPtr->enemyAttack(enemyVec, bossVec, currentPlayerPos, healthInt);
                enemyPtr->collision(enemyVec, bulletVec, bossVec, scoreInt);
            }
            // Boss updates.
            updateBoss(bossVec, deltaTime, currentPlayerPos);
            drawBoss(bossVec, window);
            // Stat Display.
            score.drawScore(window, scoreInt);
            health.drawHealth(window, healthInt);
            // HealthPickup updates.
            pickupPtr->takePickup(ammoVec, healthVec, currentPlayerPos, healthInt, hasBonus);
            drawHPickup(healthVec, window);
            drawAPickup(ammoVec, window);
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

void createBullet(sf::Vector2f currentPlayerPos, sf::Vector2f velocity, std::vector<Bullet>& bulletVec, bool& hasBonus)
{
    Bullet * bullet = new Bullet(currentPlayerPos, velocity, hasBonus);
    bulletVec.push_back(*bullet);
}

void updateBullet(std::vector<Bullet>& bulletVec, float& deltaTime)
{
    for (int i = 0; i < bulletVec.size(); i++){
        bulletVec[i].getBulletPos();
        bulletVec[i].moveBullet(deltaTime);
        // Check if bullet is out of bounds.
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
    Enemy * enemy = new Enemy(false);
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
void createBoss(std::vector<Enemy>& bossVec, int& bossCount, bool& roundInProgress)
{
    Enemy * boss = new Enemy(true);
    bossVec.push_back(*boss);
    bossCount++;
    roundInProgress = true;
}

void updateBoss(std::vector<Enemy>& bossVec, float& deltaTime, sf::Vector2f& currentPlayerPos)
{
    for (int i = 0; i < bossVec.size(); i++){
        bossVec[i].getEnemyPos();
        bossVec[i].enemyMovement(deltaTime);
        bossVec[i].calculations(currentPlayerPos);
    }
}

void drawBoss(std::vector<Enemy>& bossVec, sf::RenderWindow& window)
{
    for (int i = 0; i < bossVec.size(); i++){
        bossVec[i].drawEnemy(window);
    }
}

void createHPickup(std::vector<PickupClass>& healthVec)
{
    PickupClass * healthPickup = new PickupClass();
    healthVec.push_back(*healthPickup);
}

void drawHPickup(std::vector<PickupClass>& healthVec, sf::RenderWindow& window)
{
    for (int i = 0; i < healthVec.size(); i++){
        healthVec[i].drawHealthPickup(window);
    }
}

void createAPickup(std::vector<PickupClass>& ammoVec)
{
    PickupClass * ammoPickup = new PickupClass();
    ammoVec.push_back(*ammoPickup);
}

void drawAPickup(std::vector<PickupClass>& ammoVec, sf::RenderWindow& window)
{
    for (int i = 0; i < ammoVec.size(); i ++){
        ammoVec[i].drawAmmoPickup(window);
    }
}

void resetMatch(std::vector<Enemy>& enemyVec, std::vector<Enemy>& bossVec, int& scoreInt, int& healthInt)
{
    enemyVec.clear();
    bossVec.clear();
    scoreInt = 0;
    healthInt = 3;
}
