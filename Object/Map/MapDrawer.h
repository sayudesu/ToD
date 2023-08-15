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
	// ���f���n���h��
	int m_hBlock;
	int m_hBlock2;
	// �f�[�^�ۊ�
	std::vector<int>m_loadData;
	// �f�[�^���J�E���g
	int m_dataNum;

	std::vector<int> m_objPosX;
	std::vector<int> m_objPosY;
};

