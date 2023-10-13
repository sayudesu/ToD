#pragma once
#include <DxLib.h>
#include <array>

class ParticleDrawer
{
public:
	ParticleDrawer(VECTOR pos);
	virtual ~ParticleDrawer();

	virtual void Init(int no);
	virtual void End();
	virtual void Update();
	virtual void Draw();
	// �摜���������ǂ���
	virtual bool IsGetErase();
private:
	// �n�߂ɂǂ�������
	void FirstMove();
	// �ǂ��Ɉړ����邩
	void Suction();
private:
	// �摜�n���h��
	int m_hGraph;
	// �ʒu
	VECTOR m_pos;
	// �ړ���
	VECTOR m_vec;
	// ���x
	float m_speed;
	// �����o�֐��|�C���^
	void(ParticleDrawer::* m_pFunc)();
	// �摜���������ǂ���
	bool m_isErase;

};

