#include "wall.h"
#include <iostream>
#include "SDL.h"

void Wall::placeWall(){

    SDL_Point point;


    for(int i=0; i<grid_width/2; i++)
    {
        point.x = i + (grid_width/4);
        point.y = grid_height/3;
        wallPoints.push_back(point);
    }

}

 std::vector<SDL_Point> Wall::get_wall(){
     return wallPoints;
 }

 bool Wall::WallCell(int x, int y)
{
  for (auto const &item : wallPoints)
  {
    if (x == item.x && y == item.y)
    {
      return true;
    }
  }
  return false;
}
