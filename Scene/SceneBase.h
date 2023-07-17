#pragma once
#include "Util/Vec2.h"

// �Q�[���V�[�����N���X
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {}


	virtual void Init() {}
	virtual void End()	{}

	virtual SceneBase* Update() { return this; }
	virtual void Draw() {}

	// �X���C�_�[�֘A
	void UpdateSlider(bool& open);
	bool UpdateSliderOpen();
	bool UpdateSliderClose();

	void DrawSliderDoor();

protected:
	bool m_isSliderOpen;
	bool m_isChangeScene;
private:
	// ��ʐ؂�ւ��ۂ̃X���C�h�p�ϐ�
	int m_hDoor;
	int m_sliderPos;
	Vec2 m_pos;
};