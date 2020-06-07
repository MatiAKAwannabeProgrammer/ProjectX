#ifndef TEXTCLASS_HPP
#define TEXTCLASS_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class TextClass
{
private:
    sf::Text score;
    sf::Text health;
    sf::Text menu;
    sf::Font font;

public:
    TextClass();
    void drawScore(sf::RenderWindow& window, int& scoreInt);
    void drawHealth(sf::RenderWindow& window, int& healthInt);
    void drawMenu(sf::RenderWindow& window);

};
#endif
