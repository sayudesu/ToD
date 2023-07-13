#include "Map.h"
#include <DxLib.h>

namespace
{
	// マップチップのマス目数
	constexpr int kMapX = 50;
	constexpr int kMapY = 50;

	int kMapChip[kMapY][kMapX] = {};
}

Map::Map()
{

}

Map::~Map()
{
}

void Map::Init()
{
	int a[kMapY][kMapX];
	for (int y = 0; y < kMapY; y++)
	{
		for (int x = 0; x < kMapX; x++)
		{
			const int mapY = y * 30;
			const int mapX = x * 30;
			m_mapY.push_back(mapY);
			m_mapX.push_back(mapX);
		}
	}
}

void Map::End()
{
}

void Map::Update()
{
}

void Map::Draw()
{
	for (int y = 0; y < kMapY; y++)
	{
		for (int x = 0; x < kMapX; x++)
		{
			DrawBox(m_mapX[x], m_mapY[y], m_mapX[x] + 30, m_mapY[y] + 30, 0xfffff, true);
		}
	}
}
