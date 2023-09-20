#pragma once
#include <vector>
#include "../../MapDatas.h"

class WorldSprite;
class MapDrawer
{
public:
	MapDrawer();
	virtual ~MapDrawer();

	void Init();
	void End();
	void Draw();
	// マップチップ要素数
	MapDatas GetChip();
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

	// 別のクラスにマップの情報を渡す為に使う
	MapDatas m_data;
};

