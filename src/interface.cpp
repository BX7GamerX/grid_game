#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "interface.h"
void draw_text(sf::RenderWindow& window, const std::string& text, const sf::Vector2f& position, const sf::Font& font, unsigned int size, const sf::Color& color)
{
    sf::Text sfml_text;
    sfml_text.setFont(font);
    sfml_text.setString(text);
    sfml_text.setCharacterSize(size);
    sfml_text.setFillColor(color);
    sfml_text.setPosition(position);
    window.draw(sfml_text);
}

void draw_rectangle(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color)
{
    sf::RectangleShape rectangle;
    rectangle.setPosition(position);
    rectangle.setSize(size);
    rectangle.setFillColor(color);
    window.draw(rectangle);
}

void draw_circle(sf::RenderWindow& window, const sf::Vector2f& position, float radius, const sf::Color& color)
{
    sf::CircleShape circle;
    circle.setPosition(position);
    circle.setRadius(radius);
    circle.setFillColor(color);
    window.draw(circle);
}

void draw_sprite(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Texture& texture)
{
    sf::Sprite sprite;
    sprite.setPosition(position);
    sprite.setTexture(texture);
    window.draw(sprite);
}

void draw_sprite(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Texture& texture, const sf::IntRect& texture_rect)
{
    sf::Sprite sprite;
    sprite.setPosition(position);
    sprite.setTexture(texture);
    sprite.setTextureRect(texture_rect);
    window.draw(sprite);
}

void main_loop(sf::RenderWindow& window)
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        // Draw your game here
        window.display();
    }
}

void run_game()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game");
    main_loop(window);
}

#include <thread>

void entry_point()
{
    std::thread audio_thread(play_audio, "assets/theme.mp3");
    std::thread test_audio_thread(test_mouse);

    audio_thread.join();
    test_audio_thread.join();
}
void play_audio(const std::string& filename)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename))
    {
        return;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    // Keep the sound playing until it finishes
    while (sound.getStatus() == sf::Sound::Playing)
    {
        sf::sleep(sf::milliseconds(100));
    }
}
void test_audio() {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("assets/theme.mp3")) {
        return;
    }
    
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
    
    // Keep the sound playing
    sf::sleep(sf::seconds(2));
}


void  test_mouse(){
    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Grid Game");
    window.setFramerateLimit(60);

    // Create grid cell
    sf::RectangleShape cell(sf::Vector2f(50, 50));
    cell.setFillColor(sf::Color::White);
    cell.setOutlineThickness(1);
    cell.setOutlineColor(sf::Color::Black);

    // Track clicked cells
    bool clicked[16][12] = {false};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
                
            // Handle mouse clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Get grid coordinates
                    int gridX = event.mouseButton.x / 50;
                    int gridY = event.mouseButton.y / 50;
                    
                    // Toggle cell if within bounds
                    if (gridX >= 0 && gridX < 16 && gridY >= 0 && gridY < 12) {
                        clicked[gridX][gridY] = !clicked[gridX][gridY];
                    }
                }
            }
        }

        window.clear(sf::Color::Blue);

        // Draw grid
        for (int x = 0; x < 16; x++) {
            for (int y = 0; y < 12; y++) {
                cell.setPosition(x * 50, y * 50);
                cell.setFillColor(clicked[x][y] ? sf::Color::Red : sf::Color::White);
                window.draw(cell);
            }
        }

        window.display();
    }

}