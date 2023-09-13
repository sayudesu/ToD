#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/ObjectData.h"

// ��Q���N���X�x�[�X
class ObstacleBase
{
public:
	ObstacleBase() {};
	virtual ~ObstacleBase() {};

	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// ��Q���̈ʒu
	virtual VECTOR GetPos() const { return m_pos; }
	// �����蔻��f�[�^
	virtual ObjectData GetCollShotDatas(int shotNum) { return ObjectData(); }
	// �G�l�~�[�̔���p�f�[�^
	virtual void SetCollEnemyDatas(std::vector<ObjectData> collEnemyData) { m_collEnemyData = collEnemyData; }
	// �V���b�g�̐�
	virtual int GetShotNum() { return 0; }
	// ����Ȃ��V���b�g�̔ԍ����󂯎��
	virtual void SetEraseShotData(std::vector<ObjectData> eraseShotData) {};
	// �K�v�̂Ȃ��V���b�g�ԍ����󂯎��
	virtual void SetShotErase(int shotNum, bool erase) {};

protected:
	// �ʒu
	VECTOR m_pos       = VGet(0.0f, 0.0f, 0.0f);
	// �^�[�Q�b�g�ʒu
	VECTOR m_targetPos = VGet(0.0f, 0.0f, 0.0f);
	// �����蔻��f�[�^
	std::vector<ObjectData> m_collShotData {};
	std::vector<ObjectData> m_collEnemyData{};
};