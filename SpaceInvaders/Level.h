#pragma once

enum EEnemyTypes
{
	BlankEnemyType,
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
	//DO this
	//This should be read in from a manafest file. This is horrible and should of been in a data file. I just do not have the time to do this the correct way.
	const EEnemyTypes Level1[Level::skMaxEnemyGridHeight][Level::skMaxEnemyGridWidth] =
	{
		{BlankEnemyType, BlankEnemyType, BlankEnemyType, RedType, RedType, BlankEnemyType, BlankEnemyType, BlankEnemyType,BlankEnemyType,BlankEnemyType},
		{BlankEnemyType, BlankEnemyType, RedType, GreenType, GreenType, RedType, BlankEnemyType, BlankEnemyType,BlankEnemyType,BlankEnemyType},
		{BlankEnemyType, RedType, GreenType, GreenType, GreenType, GreenType, RedType, BlankEnemyType,BlankEnemyType,BlankEnemyType},
		{BlankEnemyType, RedType, GreenType, GreenType, GreenType, GreenType, RedType, BlankEnemyType,BlankEnemyType,BlankEnemyType},
		{BlankEnemyType, BlankEnemyType, GreenType, GreenType, GreenType, GreenType, BlankEnemyType, BlankEnemyType,BlankEnemyType,BlankEnemyType},
		{BlankEnemyType, BlankEnemyType, BlankEnemyType, BlankEnemyType, BlankEnemyType, BlankEnemyType, BlankEnemyType, BlankEnemyType,BlankEnemyType}
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

};

