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
private:
	VECTOR  m_pos;
	int m_hEff;
	int m_hPlayEff;
	int m_time;
};

