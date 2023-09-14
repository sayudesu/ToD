#pragma once
#include <DxLib.h>
#include "Util/ObstructSelectNo.h"

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

	// �f�o�b�O�p
	bool GetDead() { return m_isDead; }
	bool GetClear() { return m_isClear; }
	void SetDamage(int damage) { hp -= damage; }

	void SetObstructSelect(bool select);
	void SetObstructData(ObstructSelect data);

private:
	// �f�o�b�O�p
	void Time();
	void meat();

private:
	// �摜�n���h��
	// ���g�̗̑͂�ݒu�R�X�g���̔w�i
	int m_hBgUtil;
	// �I�u�W�F�N�g�ݒu�R�X�g�̔w�i
	int m_hObjectCost;
	// ���̉摜
	int m_hCatFood;
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
	int m_hSelectObjectState[5];


	// ���݂̃R�X�g��
	int m_costNum;

	// �v���C���[�̈ʒu���󂯎��
	VECTOR m_playerPos;

	// �I���摜�p�ʒu
	VECTOR m_selectPos[5];


	ObstructSelect m_obstructData;
	bool m_isSelect;
	bool m_isSelectNo[5];

	// �f�o�b�O�p
	int m_hpBarX;
	int m_hpBarY;

	int hp = 0;

	bool m_isDead = false;
	bool m_isClear = false;


	int time = 01;
	int time2 = 30;
	int time3 = 59;
	int timeSecond = 9;

	int timeCount1 = 0;
	int timeCount2 = 0;
	int timeCountS2 = 0;

	bool notloop = true;
	bool notloop2 = false;
	bool notloopS2 = false;

	int timerPosChange = 0;


	int costPos = 0;
	bool is1 = true;
	bool is2 = true;
	bool is3 = true;
	bool is4 = true;
	bool is5 = true;
	bool is6 = true;

	bool is1_ = true;
	bool is2_ = true;
	bool is3_ = true;
	bool is4_ = true;
	bool is5_ = true;
	bool is6_ = true;
};

