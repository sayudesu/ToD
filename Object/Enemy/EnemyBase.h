#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/CollDatas.h"

class EnemyBase
{
public:
	EnemyBase() {};
	virtual ~EnemyBase() {};

	virtual void Init(VECTOR firstPos,int x,int y) = 0;
	virtual void End()    = 0;
	virtual void Update() = 0;
	virtual void Draw()   = 0;
	virtual void DrawUI() = 0;

	// �G�l�~�[�̈ʒu
	virtual VECTOR GetPos() const   { return m_pos; }
	virtual void SetPos(VECTOR pos) { m_pos = pos;  }
	// ����f�[�^���󂯎��
	virtual void SetCollData(std::vector<CollData>collData) { m_collObstacleShotData = collData; }
	// �����蔻��f�[�^
	virtual CollData GetCollDatas() { return m_collData; }
	// �ʂ铹
	virtual void SetRoadPos(std::vector<int> mapChip) { m_mapChip = mapChip; }

protected:
	VECTOR m_pos = VGet(0.0f, 0.0f, 0.0f);
	std::vector<int> m_mapChip{};
	// ����f�[�^
	// ���g�̃f�[�^
	CollData m_collData{};
	// �v���C���[�ݒu�I�u�W�F�N�g�̃f�[�^
	std::vector<CollData> m_collObstacleShotData{};
};

