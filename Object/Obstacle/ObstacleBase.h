#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/CollDatas.h"

// ��Q���N���X�x�[�X
class ObstacleBase
{
public:
	ObstacleBase(){};
	virtual ~ObstacleBase() {};

	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// ��Q���̈ʒu
	virtual VECTOR GetPos() const { return m_pos; }
	// �^�[�Q�b�g�̈ʒu
	virtual void SetTarGetPos(VECTOR pos) { m_targetPos = pos; }
	// �����蔻��f�[�^
	virtual std::vector<CollData> GetCollDatas() { return m_collData; }
	// �G�l�~�[�̔���p�f�[�^
	virtual void SetCollEnemyDatas(std::vector<CollData> collEnemyData) { m_collEnemyData = collEnemyData; }
	// �V���b�g�̐�
	virtual int SetShotNum() { return 0; }

protected:
	// �ʒu
	VECTOR m_pos = VGet(0.0f, 0.0f, 0.0f);
	// �^�[�Q�b�g�ʒu
	VECTOR m_targetPos = VGet(0.0f, 0.0f, 0.0f);
	// �����蔻��f�[�^
	std::vector<CollData> m_collData;
	std::vector<CollData> m_collEnemyData;
};