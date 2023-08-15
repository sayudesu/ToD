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
private:
	// モデルハンドル
	int m_hBlock;
	int m_hBlock2;
	// データ保管
	std::vector<int>m_loadData;
	// データ数カウント
	int m_dataNum;

	std::vector<int> m_objPosX;
	std::vector<int> m_objPosY;
};

