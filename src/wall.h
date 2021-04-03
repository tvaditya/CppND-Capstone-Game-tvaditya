#ifndef WALL_H
#define WALL_H

#include "SDL.h"
#include <vector>

class Wall {
 public:
    Wall(int grid_width, int grid_height){
        this->grid_width = grid_width;
        this->grid_height = grid_height;

        placeWall();
    }

    std::vector<SDL_Point> get_wall();
     bool WallCell(int x, int y);

  private:
     void placeWall();
     std::vector <SDL_Point> wallPoints;
     size_t grid_width;
     size_t grid_height;
};


#endif
