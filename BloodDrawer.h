#pragma once
#include <DxLib.h>
#include <array>

class BloodDrawer
{
public:
	BloodDrawer(VECTOR pos);
	virtual ~BloodDrawer();
	// ������
	virtual void Init(int no);
	// �X�V����
	virtual void Update();
	// �`��
	virtual void Draw();
	// �������ǂ���
	virtual bool IsGetErase();
private:
	// �n�߂̓���
	void FirstMove();
private:
	// �ʒu
	VECTOR m_pos;
	// �ړ���
	VECTOR m_vec;
	// �������ǂ���
	bool m_isErase;
	// �����o�֐��|�C���^
	void(BloodDrawer::* m_pFunc)();
};

