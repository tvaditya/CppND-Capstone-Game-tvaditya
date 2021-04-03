#include "renderer.h"
#include <iostream>
#include <string>
#include "obstacles.h"
#include "slowers.h"


Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height, Wall &wall)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height),
      wall(wall) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Aditya's Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  obstacleSurface = SDL_LoadBMP("../assets/rocket.bmp");
  obstacleTexture = SDL_CreateTextureFromSurface(sdl_renderer, obstacleSurface);

  slowerSurface = SDL_LoadBMP("../assets/unlit-bomb.bmp");
  slowerTexture = SDL_CreateTextureFromSurface(sdl_renderer, slowerSurface);
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake,
  SDL_Point const &food,
  const std::shared_ptr<Obstacles> obstacles,
  const std::shared_ptr<Slowers> slowers) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render WALL
  SDL_SetRenderDrawColor(sdl_renderer, 0, 255, 0, 0);
  for (size_t i = 0; i < wall.get_wall().size(); i++)
  {
   block.x = wall.get_wall()[i].x * block.w;
   block.y = wall.get_wall()[i].y * block.h;
   SDL_RenderFillRect(sdl_renderer, &block);
  }
  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Place speed obstacles
  placeObstacles(obstacles);

  // Place slowers
  placeSlowers(slowers);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

// Render speed obstacles
void Renderer::placeObstacles(const std::shared_ptr<Obstacles> obstacles) const
{
  for (const Coordinate &coordinate : obstacles->getCoordinates())
  {
    SDL_Rect obstacleRect;
    obstacleRect.w = screen_width / grid_width;
    obstacleRect.h = screen_height / grid_height;
    obstacleRect.x = coordinate.getXCoordinate() * obstacleRect.w;
    obstacleRect.y = coordinate.getYCoordinate() * obstacleRect.h;

    SDL_RenderCopy(sdl_renderer, obstacleTexture, NULL, &obstacleRect);
  }
}

void Renderer::placeSlowers(const std::shared_ptr<Slowers> slowers) const
{
  for (const Coordinate &coordinate : slowers->getCoordinates())
  {
    // Rect which will be hosting the booster
    SDL_Rect slowerRect;
    slowerRect.w = screen_width / grid_width;
    slowerRect.h = screen_height / grid_height;
    slowerRect.x = coordinate.getXCoordinate() * slowerRect.w;
    slowerRect.y = coordinate.getYCoordinate() * slowerRect.h;

    // Render the obstacles
    SDL_RenderCopy(sdl_renderer, slowerTexture, NULL, &slowerRect);
  }
}


void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
