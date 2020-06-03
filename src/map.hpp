#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
class Map
{
private:
    sf::Sprite map;
    sf::Texture mapTexture;

public:
    Map();
    void drawMap(sf::RenderWindow& window);

};
#endif
