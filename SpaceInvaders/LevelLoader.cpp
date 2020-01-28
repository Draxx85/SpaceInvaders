#include "LevelLoader.h"
#include "Level.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

int** LevelLoader::LoadLevel(int level)
{
	using namespace std;
    int** levelData = new int*[Level::skMaxEnemyGridHeight];

    std::stringstream filename;
    filename << "level" << level << ".txt";

    ifstream file;
    file.open(filename.str());

    for (int h = 0; h < Level::skMaxEnemyGridHeight; ++h)
    {
        levelData[h] = new int[Level::skMaxEnemyGridWidth];
        for (int w = 0; w < Level::skMaxEnemyGridWidth; ++w)
        {
            file >> levelData[h][w];
        }
    }

    file.close();

    return levelData;
}
