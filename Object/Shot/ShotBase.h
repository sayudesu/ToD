#pragma once
#include <DxLib.h>

// �V���b�g�N���X
class ShotBase
{
public:
	ShotBase(VECTOR pos);
	virtual~ShotBase();

	void Update();
	void Draw();

	// �V���b�g�̈ʒu
	VECTOR SetPos()const{ return m_pos; }
	// �^�[�Q�b�g�ʒu
	void GetTargetPos(VECTOR pos) { m_targetPos = pos; }
private:
	// �ړ��̌v�Z�����Ă��܂�
	void VecCalculation();
private:
	// 3D���f���n���h��
	int m_hShot;
	// �ʒu
	VECTOR m_pos;
	// ����
	VECTOR m_dir;
	// �^�[�Q�b�g�ʒu
	VECTOR m_targetPos;
	// ��ʊO����
	bool m_isScreenOut;
};

