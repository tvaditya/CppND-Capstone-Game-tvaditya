#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "snake.h"
#include "wall.h"
#include "obstacles.h"
#include "slowers.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height, Wall &wall);
  ~Renderer();

  void Render(Snake const snake,
    SDL_Point const &food,
    const std::shared_ptr<Obstacles> obstacles,
    const std::shared_ptr<Slowers> slowers);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  SDL_Surface *obstacleSurface;
  SDL_Texture *obstacleTexture;

  SDL_Surface *slowerSurface;
  SDL_Texture *slowerTexture;

  Wall wall;

  void placeObstacles(const std::shared_ptr<Obstacles> obstacles) const;
  void placeSlowers(const std::shared_ptr<Slowers> slowers) const;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
