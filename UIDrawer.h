#pragma once
#include <DxLib.h>

class UIDrawer
{
public:
	UIDrawer();
	~UIDrawer();

	void Init();
	void End();
	void Update();
	void Draw();

	// �I�u�W�F�N�g��ݒu���邽�߂̃R�X�g���󂯎��
	void SetCostSetObject(int cost);
	// �v���C���[�̈ʒu���󂯎��3D���W����2D���W�ɕϊ�
	void SetPlayerPos(VECTOR pos);

private:
	// �摜�n���h��
	// ���g�̗̑͂�ݒu�R�X�g���̔w�i
	int m_hBgUtil;
	// �I�u�W�F�N�g�ݒu�R�X�g�̔w�i
	int m_hObjectCost;
	// ���̉摜
	int m_hMeat;
	// �K�E�Z�{�^���̐���
	int m_hTopicSpecialAttack;
	int m_hBarTopicSpecialAttack;
	// HP�o�[�̔w�i
	int m_hBgHp;
	// HP�o�[
	int m_hHp;
	// �I�u�W�F�N�g�ݒu�p
	int m_hSelectObject;
	int m_hSelectObjectState[3];


	// ���݂̃R�X�g��
	int m_costNum;

	// �v���C���[�̈ʒu���󂯎��
	VECTOR m_playerPos;

	// �I���摜�p�ʒu
	VECTOR m_selectPos[3];
};

