#pragma once
#include <vector>

class MapDrawer
{
public:
	MapDrawer();
	virtual ~MapDrawer();

	void Init();
	void End();
	void Update();
	void Draw();

	// マップチップ要素数
	std::vector<int> GetMapChip();
	// マップチップ座標
	std::vector<int> GetMapChipX();
	std::vector<int> GetMapChipZ();
private:
	// モデルハンドル
	int m_hBlock;
	int m_hEnemyRoad;
	int m_hEnemySpawner;
	int m_hEnemyStop;

	// データ保管
	std::vector<int>m_loadData;
	// データ数カウント
	int m_dataNum;

	std::vector<int> m_objPosX;
	std::vector<int> m_objPosZ;
};

