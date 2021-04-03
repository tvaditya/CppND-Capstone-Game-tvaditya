#ifndef FILEUTILS_H
#define FILEUTILS_H

struct ConfigParameters
{
    // Constructor
    ConfigParameters(const int numberOfSlowers,
                     const int numberOfObstacles)
        : _numberOfSlowers(numberOfSlowers),
          _numberOfObstacles(numberOfObstacles){};

    // getters
    int getNumberOfSlowers() const { return _numberOfSlowers; }
    int getNumberOfObstacles() const { return _numberOfObstacles; }

private:
    int _numberOfSlowers;
    int _numberOfObstacles;
};

namespace FileUtils
{
    // Path
    constexpr char configFilePath[] = "../configFiles/config.txt";

    // File Keys

    constexpr char numberOfSlowersKey[] = "numberOfSlowers";
    constexpr char numberOfObstaclesKey[] = "numberOfObstacles";

    // Config Parameters
    ConfigParameters getConfigFromFile();
}

#endif
