#pragma once
#include <DxLib.h>

// �G�t�F�N�V�A�Ǘ�
class EffekseerDrawer
{
public:
	EffekseerDrawer();
	virtual~EffekseerDrawer();

	void Init();
	void End();
	void Update();
	void Draw();
	// �ʒu���󂯎��܂�
	void GetPos(VECTOR pos);
	// ���݃G�t�F�N�g���Đ�����Ă��邩�ǂ���
	int SetPlayingNow();
private:
	VECTOR  m_pos;
	int m_hEff;
	int m_hPlayEff;
	int m_time;
};

