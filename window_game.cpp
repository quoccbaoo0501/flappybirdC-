#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Window Game");
    sf::CircleShape player(50.f);
    player.setFillColor(sf::Color::Green);
    player.setPosition(400, 300);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move(-5.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move(5.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.move(0.f, -5.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.move(0.f, 5.f);

        window.clear();
        window.draw(player);
        window.display();
    }

    return 0;
}
