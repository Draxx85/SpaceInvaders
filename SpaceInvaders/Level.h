#pragma once

enum EEnemyTypes
{
	BlankEnemyType = 0,
	GreenType = 4,
	RedType = 6,
	BlueType = 8,
	BossType = 10,
	Explosion = 11, 
};

class Level
{
public:
	Level();
	~Level();
	const EEnemyTypes *BuildLevel(int layout);

	static const int skMaxEnemyGridWidth = 10;
	static const int skMaxEnemyGridHeight = 6;
private:
	const EEnemyTypes *m_EnemyArray;
	//I did write a text parser to build levels for me but I hit an issue so I left this as is. 
	//This should of been done by reading in level files and building the levels up like that
	//This just generally would of allowed more flexability and would of made level building easier
	const EEnemyTypes Level1[Level::skMaxEnemyGridHeight][Level::skMaxEnemyGridWidth] =
	{
		{RedType, GreenType, GreenType, RedType, RedType, RedType, GreenType, RedType,GreenType,GreenType},
		{GreenType, RedType, RedType, BlankEnemyType, BlueType, BlankEnemyType, RedType, GreenType,GreenType,GreenType},
		{RedType, RedType, GreenType, BlueType, BlueType, BlueType, RedType, GreenType,GreenType,RedType},
		{RedType, RedType, GreenType, BlankEnemyType, BlueType, BlankEnemyType, RedType, GreenType,GreenType,GreenType},
		{RedType, RedType, GreenType, GreenType, GreenType, GreenType, RedType, RedType,GreenType,GreenType},
		{BlankEnemyType, BlankEnemyType, BlankEnemyType, BlankEnemyType, BlankEnemyType, BlankEnemyType, BlankEnemyType, BlankEnemyType,BlankEnemyType,BlankEnemyType}
	};
	const EEnemyTypes Level2[Level::skMaxEnemyGridHeight][Level::skMaxEnemyGridWidth] =
	{
		{BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType,BlueType,BlueType},
		{RedType, RedType, RedType, RedType, RedType, RedType, RedType, RedType,RedType,RedType},
		{RedType, RedType, RedType, RedType, RedType, RedType, RedType, RedType,RedType,RedType},
		{GreenType, GreenType, GreenType, GreenType, GreenType, GreenType, GreenType, GreenType,GreenType,GreenType},
		{GreenType, GreenType, GreenType, GreenType, GreenType, GreenType, GreenType, GreenType,GreenType,GreenType},
		{BlankEnemyType, BlankEnemyType, BlankEnemyType, BlankEnemyType, BlankEnemyType, BlankEnemyType, BlankEnemyType, BlankEnemyType,BlankEnemyType,BlankEnemyType}
	};
	const EEnemyTypes Level3[Level::skMaxEnemyGridHeight][Level::skMaxEnemyGridWidth] = {
		{BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType,BlueType,BlueType},
		{RedType, RedType, RedType, RedType, RedType, RedType, RedType, RedType,RedType,RedType},
		{RedType, RedType, RedType, RedType, RedType, RedType, RedType, RedType,RedType,RedType},
		{RedType, RedType, RedType, RedType, RedType, RedType, RedType, RedType,RedType,RedType},
		{GreenType, GreenType, GreenType, GreenType, GreenType, GreenType, GreenType, GreenType,GreenType,GreenType},
		{GreenType, GreenType, GreenType, GreenType, GreenType, GreenType, GreenType, GreenType,GreenType,GreenType}
	};
	const EEnemyTypes Level4[Level::skMaxEnemyGridHeight][Level::skMaxEnemyGridWidth] = {
		{BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType,BlueType,BlueType},
		{RedType, RedType, BlueType, RedType, RedType, BlueType, RedType, RedType,RedType,RedType},
		{RedType, BlueType, BlueType, RedType, RedType, BlueType, RedType, RedType,RedType,RedType},
		{RedType, RedType, RedType, RedType, RedType, RedType, RedType, RedType,RedType,RedType},
		{BlueType, GreenType, BlueType, GreenType, BlueType, GreenType, BlueType, GreenType,BlueType,GreenType},
		{BlueType, GreenType, BlueType, GreenType, BlueType, GreenType, BlueType, GreenType,BlueType,GreenType}
	};
	const EEnemyTypes Level5[Level::skMaxEnemyGridHeight][Level::skMaxEnemyGridWidth] = {
		{BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType,BlueType,BlueType},
		{BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType,BlueType,BlueType},
		{BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType,BlueType,BlueType},
		{RedType, RedType, RedType, RedType, RedType, RedType, RedType, RedType,RedType,RedType},
		{RedType, RedType, RedType, RedType, RedType, RedType, RedType, RedType,RedType,RedType},
		{GreenType, GreenType, GreenType, GreenType, GreenType, GreenType, GreenType, GreenType,GreenType,GreenType}
	};
	const EEnemyTypes Level6[Level::skMaxEnemyGridHeight][Level::skMaxEnemyGridWidth] = {
		{BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType,BlueType,BlueType},
		{BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType,BlueType,BlueType},
		{BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType, BlueType,BlueType,BlueType},
		{RedType, RedType, BlueType, RedType, RedType, RedType, RedType, BlueType,RedType,RedType},
		{RedType, RedType, BlueType, RedType, RedType, RedType, RedType, BlueType,RedType,RedType},
		{GreenType, GreenType, RedType, GreenType, GreenType, GreenType, RedType, GreenType,GreenType,GreenType}
	};

};

