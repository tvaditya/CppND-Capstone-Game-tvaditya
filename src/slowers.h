
#ifndef SLOWERS_H
#define SLOWERS_H

#include <memory>
#include <vector>
#include "coordinate.h"

class Slowers
{
    public:
    // Constructor
    Slowers();

    void addCoordinate(const Coordinate &&coordinate);
    bool SlowerCell(const Coordinate &&coordinate) const;
    void deleteSlowerCellAt(const Coordinate &&coordinate);

    // Getter
    const std::vector<Coordinate> &getCoordinates() const;
    int count() const;

    private:
    std::unique_ptr<std::vector<Coordinate>> _coordinates;
};

#endif
