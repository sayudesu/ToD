#pragma once
#include <vector>

class WorldSprite;
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

	// 2D画像用
	std::vector<WorldSprite*> m_pSprite;
};

