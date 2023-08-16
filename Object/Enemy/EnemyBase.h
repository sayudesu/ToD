#pragma once
#include <DxLib.h>
#include <vector>

class EnemyBase
{
public:
	EnemyBase() {};
	virtual ~EnemyBase() {};

	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// �G�l�~�[�̈ʒu
	VECTOR SetPos() const { return m_pos; }

	// �ʂ铹
	void SetRoadPos(std::vector<int> mapChip) { m_mapChip = mapChip; }

protected:
	VECTOR m_pos = VGet(300.0f, 0.0f, 0.0f);
	std::vector<int> m_mapChip;
};

