#pragma once
#include <DxLib.h>
#include "../../Util/Vec2.h"
#include <vector>

// �v���C���[�N���X
class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void End();
	void Update();
	void Draw();

	// �}�E�X�̈ʒu��Ԃ�
	VECTOR SetMouseWorldPos() { return m_screenToWorldPos; }
	VECTOR SetMouseScreenPos() { return m_pos; }
	// �}�E�X��������Ă��邩�ǂ���
	bool SetMouseLeft() { return m_isResultObject; }
private:
	// ����𐧌�
	void UpdateControl();
	// �I�u�W�F�N�g�̃R�X�g�֘A
	void ObjectCost();
private:
	// �}�E�X�̈ʒu
	VECTOR m_pos;
	// ��ʂ���3D��Ԃɕϊ��p
	VECTOR m_screenToWorldPos;
	VECTOR m_screenPos;
	VECTOR m_start3DPos;
	VECTOR m_end3DPos;

	// �ʒu���L�^���܂�
	std::vector<VECTOR>m_posHistory;

	// �}�E�X�̍��N���b�N��������Ă��邩�ǂ���
	// false : �����Ă��Ȃ� true : �����Ă���
	bool m_isResultObject;
	// �ݒu�o���邩�̍ŏI�m�F
	bool m_isSetObject;

	// �I�u�W�F�N�g�R�X�g�֘A
	int m_objectCostNum;
};

