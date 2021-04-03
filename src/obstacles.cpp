#include "obstacles.h"
#include <memory>
#include "coordinate.h"

Obstacles::Obstacles()
{
    _coordinates = std::unique_ptr<std::vector<Coordinate>>(new std::vector<Coordinate>);
}

void Obstacles::addCoordinate(const Coordinate &&coordinate)
{
    _coordinates->emplace_back(coordinate);
}

bool Obstacles::ObstacleCell(const Coordinate &&coordinate)
{
    for (const Coordinate &_coordinate : *_coordinates)
    {
        if (_coordinate == coordinate)
        {
            return true;
        }
    }
    return false;
}

void Obstacles::deleteObstacleCellAt(const Coordinate &&coordinate)
{
    /// Early exit.
    if (_coordinates->size() == 0)
    {
        return;
    }
    for (auto it = _coordinates->begin(); it != _coordinates->end();)
    {
        if (*it == coordinate)
        {
            it = _coordinates->erase(it);
        }
        else
        {
            ++it;
        }
    }
}

int Obstacles::count() const
{
    return _coordinates->size();
}

const std::vector<Coordinate> &Obstacles::getCoordinates() const
{
    return *_coordinates; // Copy will not be made due to RVO
}
