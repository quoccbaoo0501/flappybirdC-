#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int GRID_SIZE = 20;
const float SNAKE_SPEED = 0.1f; // seconds per move

class Snake {
public:
    Snake() {
        body.push_back(sf::Vector2i(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
        direction = sf::Vector2i(1, 0);
    }

    void move() {
        sf::Vector2i newHead = body.front() + direction;
        body.insert(body.begin(), newHead);
        body.pop_back();
    }

    void grow() {
        body.push_back(body.back());
    }

    void setDirection(sf::Vector2i newDirection) {
        if (newDirection.x * direction.x + newDirection.y * direction.y == 0) {
            direction = newDirection;
        }
    }

    bool checkCollision() {
        sf::Vector2i head = body.front();
        if (head.x < 0 || head.x >= WINDOW_WIDTH / GRID_SIZE ||
            head.y < 0 || head.y >= WINDOW_HEIGHT / GRID_SIZE) {
            return true;
        }
        for (size_t i = 1; i < body.size(); ++i) {
            if (body[i] == head) {
                return true;
            }
        }
        return false;
    }

    std::vector<sf::Vector2i> body;
    sf::Vector2i direction;
};

sf::Vector2i generateFood(const Snake& snake) {
    sf::Vector2i food;
    do {
        food.x = rand() % (WINDOW_WIDTH / GRID_SIZE);
        food.y = rand() % (WINDOW_HEIGHT / GRID_SIZE);
    } while (std::find(snake.body.begin(), snake.body.end(), food) != snake.body.end());
    return food;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game");
    window.setVerticalSyncEnabled(true);

    Snake snake;
    sf::Vector2i food = generateFood(snake);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            snake.setDirection(sf::Vector2i(-1, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            snake.setDirection(sf::Vector2i(1, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            snake.setDirection(sf::Vector2i(0, -1));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            snake.setDirection(sf::Vector2i(0, 1));
        }

        if (clock.getElapsedTime().asSeconds() >= SNAKE_SPEED) {
            snake.move();
            clock.restart();

            if (snake.body.front() == food) {
                snake.grow();
                food = generateFood(snake);
            }

            if (snake.checkCollision()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        // Draw snake
        for (const auto& segment : snake.body) {
            sf::RectangleShape rect(sf::Vector2f(GRID_SIZE - 1, GRID_SIZE - 1));
            rect.setPosition(segment.x * GRID_SIZE, segment.y * GRID_SIZE);
            rect.setFillColor(sf::Color::Green);
            window.draw(rect);
        }

        // Draw food
        sf::RectangleShape foodRect(sf::Vector2f(GRID_SIZE - 1, GRID_SIZE - 1));
        foodRect.setPosition(food.x * GRID_SIZE, food.y * GRID_SIZE);
        foodRect.setFillColor(sf::Color::Red);
        window.draw(foodRect);

        window.display();
    }

    return 0;
}
