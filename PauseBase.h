#pragma once
#include <DxLib.h>
// �ꎞ��~�p�x�[�X�N���X
class PauseBase
{
public:
	PauseBase() {};
	virtual~PauseBase() {};

	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void UpdateStart() = 0;
	virtual void UpdateMain() = 0;
	virtual void UpdateEnd() = 0;
protected:
	// �����o�֐��|�C���^
	void (PauseBase::* m_updateFunc)();
};

