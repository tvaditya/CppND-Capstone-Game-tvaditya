#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "wall.h"
#include "slowers.h"
#include "obstacles.h"


class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, Wall &wall);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;
  Wall wall;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;


  // If snake hits this obstacle it will speed up */
  std::shared_ptr<Obstacles> _obstacles;
  void PlaceObstacles();

  std::shared_ptr<Slowers> _slowers;
  void PlaceSlowers();

  int score{0};
  int _numberOfObstacles;
  int _numberOfSlowers;

  void PlaceFood();
  void Update();
};

#endif
