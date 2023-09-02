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

	// �X���C�h���Ō�܂ŏI��������ǂ���
	bool IsGetEnd();
	void IsSetEndReset();
private:
	int m_hNewChallenger;
	int m_hSpacialAttack;
	int m_hSpShot;

	// ��~���Ԃ��J�E���g
	int m_countFrameSleep;
	// �ǂ��܂ŃX���C�h�����邩
	int m_slidePos;
	// ���o���I��������ǂ���
	bool m_isEnd;
	Vec2 m_pos;
	
};

