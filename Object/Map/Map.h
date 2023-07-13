#pragma once
#include <vector>

class Map
{
public:
	Map();
	virtual ~Map();

	void Init();
	void End();
	void Update();
	void Draw();
private:
	std::vector<int>m_mapX;
	std::vector<int>m_mapY;
};

