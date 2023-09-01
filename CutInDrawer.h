#pragma once
#include "Util/Vec2.h"

class CutInDrawer
{
public:
	CutInDrawer();
	~CutInDrawer();
	void Init();
	void End();
	void Update();
	// �X���C�h����
	void UpdateSlide();
	// ���Z�b�g
	void Reset();
	void Draw();
private:
	int m_hNewChallenger;
	int m_hSpacialAttack;

	// ��~���Ԃ��J�E���g
	int m_countFrameSleep;
	// �ǂ��܂ŃX���C�h�����邩
	int m_slidePos;

	Vec2 m_pos;
	
};

