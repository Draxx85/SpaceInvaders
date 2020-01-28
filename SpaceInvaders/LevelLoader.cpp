#include "LevelLoader.h"
#include "Level.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

const EEnemyTypes *LevelLoader::LoadLevel(int level)
{
	EEnemyTypes data[Level::skMaxEnemyGridHeight][Level::skMaxEnemyGridWidth];
    std::stringstream filename;
    filename << "Resources/level" << level << ".lvl";

    std::ifstream file;
    file.open(filename.str());
	unsigned int item;
    for (int i = 0; i < Level::skMaxEnemyGridHeight; ++i)
    {
        for (int j = 0; j < Level::skMaxEnemyGridWidth; ++j)
        {
            file >> item;
			data[i][j] = static_cast<EEnemyTypes>(item);
        }
    }

    file.close();

    return &data[0][0];
}
