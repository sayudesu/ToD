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

	// �}�b�v�`�b�v�v�f��
	std::vector<int> GetMapChip();
	// �}�b�v�`�b�v���W
	std::vector<int> GetMapChipX();
	std::vector<int> GetMapChipZ();
private:
	// ���f���n���h��
	int m_hBlock;
	int m_hEnemyRoad;
	int m_hEnemySpawner;
	int m_hEnemyStop;

	// �f�[�^�ۊ�
	std::vector<int>m_loadData;
	// �f�[�^���J�E���g
	int m_dataNum;

	std::vector<int> m_objPosX;
	std::vector<int> m_objPosZ;
};

