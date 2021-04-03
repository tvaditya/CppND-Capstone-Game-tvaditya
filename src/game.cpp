#include "game.h"
#include <iostream>
#include <vector>
#include "SDL.h"
#include "coordinate.h"
#include "fileutils.h"


Game::Game(std::size_t grid_width, std::size_t grid_height, Wall &wall)
    : snake(grid_width, grid_height, wall),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)),
      wall(wall) {

  auto config = FileUtils::getConfigFromFile();
  _numberOfObstacles = config.getNumberOfObstacles();
  _numberOfSlowers = config.getNumberOfSlowers();

  _obstacles = std::shared_ptr<Obstacles>(new Obstacles());
  _slowers = std::shared_ptr<Slowers>(new Slowers());

  PlaceFood();

  PlaceObstacles();

  PlaceSlowers();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, _obstacles, _slowers);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }

    if (!wall.WallCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there is obstacle over here
  if (_obstacles->ObstacleCell(Coordinate(new_x, new_y)))
  {
    snake.speed += 0.02;
    _obstacles->deleteObstacleCellAt(Coordinate(new_x, new_y));
    return;
  }

  if (_slowers->SlowerCell(Coordinate(new_x, new_y)))
  {
    snake.speed -= 0.02;
   _slowers->deleteSlowerCellAt(Coordinate(new_x, new_y));
    return;
  }

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

// Place obstacles and play them in empty coordinates
void Game::PlaceObstacles()
{
  int x, y;
  while (true)
  {

    if (_numberOfObstacles == _obstacles->count())
    {
      return;
    }

    x = random_w(engine);
    y = random_h(engine);

    auto foodExistsAtThisCell = food.x == x && food.y == y;
    if (!snake.SnakeCell(x, y) && !foodExistsAtThisCell)
    {
      _obstacles->addCoordinate(Coordinate(x, y));
    }
  }
}

void Game::PlaceSlowers()
{
  int x, y;
  while (true)
  {
    /// Return if we meet the size requiremens.
    if (_numberOfSlowers == _slowers->count())
    {
      return;
    }

    /// Randomly generate the x and y coordinate.
    x = random_w(engine);
    y = random_h(engine);

    // Check that the location is not occupied by a (snake + food + obstacle) before placing
    // an obstacle.
    auto foodExistsAtThisCell = food.x == x && food.y == y;

    auto slowerExistsAtThisCell = _slowers->SlowerCell(Coordinate(x,y));
    if (!snake.SnakeCell(x, y) && !foodExistsAtThisCell && !slowerExistsAtThisCell)
    {
      _slowers->addCoordinate(Coordinate(x,y));
    }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
