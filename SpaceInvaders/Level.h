#pragma once

enum EEnemyTypes
{
	BlankEnemyType,
	GreenType = 5,
	RedType = 7,
	BlueType = 9,
	BossType = 11, 
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

