#include <fstream>
#include "fileutils.h"
#include <string>
#include <sstream>

ConfigParameters FileUtils::getConfigFromFile()
{
    std::ifstream filestream(FileUtils::configFilePath);

    int _numberOfSlowers, _numberOfObstacles = 10;
    if (filestream.is_open())
    {
        std::string line;
        while (std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            std::string key, value;
            linestream >> key >> value;
            if (key == FileUtils::numberOfSlowersKey)
            {
                _numberOfSlowers = std::stoi(value);
            }
            else if (key == FileUtils::numberOfObstaclesKey)
            {
                _numberOfObstacles = std::stoi(value);
            }
        }
    }
    return ConfigParameters(_numberOfSlowers, _numberOfObstacles);
}
