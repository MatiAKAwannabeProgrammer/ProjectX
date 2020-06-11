#include "pickupClass.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

PickupClass::PickupClass()
{
    healthPickup.setRadius(15.f);
    healthPickup.setFillColor(sf::Color::Yellow);
    ammoPickup.setRadius(15.f);
    ammoPickup.setFillColor(sf::Color::Green);
    randX = (rand() % 1550) + 1;
    randY = (rand() % 850) + 1;
    healthPickup.setPosition(randX, randY);
    ammoPickup.setPosition(randX, randY);
    healthBounds = healthPickup.getGlobalBounds();
    ammoBounds = ammoPickup.getGlobalBounds();
    hasBonus = false;
}

void PickupClass::drawHealthPickup(sf::RenderWindow& window)
{
    window.draw(healthPickup);
}

void PickupClass::drawAmmoPickup(sf::RenderWindow& window)
{
    window.draw(ammoPickup);
}

void PickupClass::takePickup(std::vector<PickupClass>& ammoVec, std::vector<PickupClass>& healthVec, sf::Vector2f& playerPos, int& healthInt, bool& hasBonus)
{
    for (int i = 0; i < healthVec.size(); i++){
        if (healthVec[i].healthBounds.contains(playerPos)){
            healthVec.erase(healthVec.begin() + i);
            if (healthInt < 3){
                healthInt++;
            }
        }
    } 
    for (int i = 0; i < ammoVec.size(); i++){
        if (ammoVec[i].ammoBounds.contains(playerPos)){
            ammoVec.erase(ammoVec.begin() + i);
            hasBonus = true;
        }
    }
}
