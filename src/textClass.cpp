#include "textClass.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

TextClass::TextClass()
{
    font.loadFromFile("./content/arial_narrow_7.ttf");
    score.setPosition(sf::Vector2f(5.f, 5.f));
    score.setFont(font);
    score.setFillColor(sf::Color::Black);
    score.setOutlineColor(sf::Color::White);
    score.setOutlineThickness(1.f);
    score.setCharacterSize(15.f);

    health.setPosition(sf::Vector2f(5.f, 20.f));
    health.setFont(font);
    health.setFillColor(sf::Color::Black);
    health.setOutlineColor(sf::Color::White);
    health.setOutlineThickness(1.f);
    health.setCharacterSize(15.f);

    menu.setPosition(sf::Vector2f(750.f, 400.f));
    menu.setFont(font);
    menu.setFillColor(sf::Color::Black);
    menu.setOutlineColor(sf::Color::White);
    menu.setOutlineThickness(1.f);
    menu.setCharacterSize(25.f);

}

void TextClass::drawScore(sf::RenderWindow& window, int& scoreInt)
{
    score.setString("Score: " + std::to_string(scoreInt));   
    window.draw(score);
}

void TextClass::drawHealth(sf::RenderWindow& window, int& healthInt)
{
    health.setString("Health: " + std::to_string(healthInt));
    window.draw(health);
}

void TextClass::drawMenu(sf::RenderWindow& window)
{
    menu.setString("PROJECT X\n[Q] Quit\n[R] Restart");
    window.draw(menu);
}
