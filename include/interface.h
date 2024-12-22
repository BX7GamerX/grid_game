#ifndef INTERFACE_H
#define INTERFACE_H
#include <SFML/Graphics.hpp>
#include <string>
void draw_text(sf::RenderWindow& window, const std::string& text, const sf::Vector2f& position, const sf::Font& font, unsigned int size, const sf::Color& color);
void draw_rectangle(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
void draw_circle(sf::RenderWindow& window, const sf::Vector2f& position, float radius, const sf::Color& color);
void draw_sprite(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Texture& texture);
void draw_sprite(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Texture& texture, const sf::IntRect& texture_rect);
void main_loop(sf::RenderWindow& window);
void run_game();
void entry_point();
void test_audio();
void play_audio(const std::string& filename);

void test_mouse();


#endif // INTERFACE_H