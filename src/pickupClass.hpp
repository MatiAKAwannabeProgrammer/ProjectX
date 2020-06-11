#ifndef PICKUPCLASS_HPP
#define PICKUPCLASS_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
class PickupClass
{
private:
    sf::CircleShape healthPickup;
    sf::CircleShape ammoPickup;
    int randX, randY;
    sf::FloatRect healthBounds, ammoBounds;
    bool hasBonus;

public:
    PickupClass();
    void drawHealthPickup(sf::RenderWindow& window);
    void drawAmmoPickup(sf::RenderWindow& window);
    void takePickup(std::vector<PickupClass>& ammoVec, std::vector<PickupClass>& healthVec, sf::Vector2f& playerPos, int& healthInt, bool& hasBonus);

};
#endif
