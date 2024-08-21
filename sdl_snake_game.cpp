#include <SDL2/SDL.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int GRID_SIZE = 20;
const int SNAKE_SPEED = 100; // milliseconds per move

struct Vector2i {
    int x, y;
    bool operator==(const Vector2i& other) const {
        return x == other.x && y == other.y;
    }
    Vector2i operator+(const Vector2i& other) const {
        return {x + other.x, y + other.y};
    }
};

class Snake {
public:
    Snake() {
        body.push_back({WINDOW_WIDTH / (2 * GRID_SIZE), WINDOW_HEIGHT / (2 * GRID_SIZE)});
        direction = {1, 0};
    }

    void move() {
        Vector2i newHead = body.front() + direction;
        body.insert(body.begin(), newHead);
    }

    void grow() {
        // The snake automatically grows in the move() method,
        // so we don't need to do anything extra here.
    }

    void setDirection(Vector2i newDirection) {
        if (newDirection.x * direction.x + newDirection.y * direction.y == 0) {
            direction = newDirection;
        }
    }

    bool checkCollision() {
        Vector2i head = body.front();
        // Check if snake hits the screen edges
        if (head.x < 0 || head.x >= WINDOW_WIDTH / GRID_SIZE ||
            head.y < 0 || head.y >= WINDOW_HEIGHT / GRID_SIZE) {
            return true;
        }
        // Check if snake touches itself
        for (size_t i = 1; i < body.size(); ++i) {
            if (body[i] == head) {
                return true;
            }
        }
        return false;
    }

    std::vector<Vector2i> body;
    Vector2i direction;
};

Vector2i generateFood(const Snake& snake) {
    Vector2i food;
    do {
        food.x = rand() % (WINDOW_WIDTH / GRID_SIZE);
        food.y = rand() % (WINDOW_HEIGHT / GRID_SIZE);
    } while (std::find(snake.body.begin(), snake.body.end(), food) != snake.body.end());
    return food;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    srand(static_cast<unsigned int>(time(nullptr)));
    Snake snake;
    Vector2i food = generateFood(snake);
    Uint32 lastMoveTime = SDL_GetTicks();

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:  snake.setDirection({-1, 0}); break;
                    case SDLK_RIGHT: snake.setDirection({1, 0});  break;
                    case SDLK_UP:    snake.setDirection({0, -1}); break;
                    case SDLK_DOWN:  snake.setDirection({0, 1});  break;
                }
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastMoveTime >= SNAKE_SPEED) {
            snake.move();
            lastMoveTime = currentTime;

            if (snake.body.front() == food) {
                food = generateFood(snake);
            } else {
                snake.body.pop_back(); // Remove tail only if food wasn't eaten
            }

            if (snake.checkCollision()) {
                // End the game
                running = false;
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw snake
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for (const auto& segment : snake.body) {
            SDL_Rect rect = {segment.x * GRID_SIZE, segment.y * GRID_SIZE, GRID_SIZE - 1, GRID_SIZE - 1};
            SDL_RenderFillRect(renderer, &rect);
        }

        // Draw food
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect foodRect = {food.x * GRID_SIZE, food.y * GRID_SIZE, GRID_SIZE - 1, GRID_SIZE - 1};
        SDL_RenderFillRect(renderer, &foodRect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
