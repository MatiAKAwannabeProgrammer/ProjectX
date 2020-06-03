#include "map.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

Map::Map()
{
    mapTexture.loadFromFile("./content/map.png");
    map.setTexture(mapTexture); 
}

void Map::drawMap(sf::RenderWindow& window)
{
    window.draw(map);
}
