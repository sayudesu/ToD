#pragma once
#include <DxLib.h>
#include "../../Util/Tracking.h"
class Camera
{
public:
	Camera();
	virtual ~Camera();

	void Init();
	void End();
	void Update();

	// �J�����̈ʒu
	VECTOR SetPos() const;
	// �}�E�X�̈ʒu�󂯎��
	void SetMouseScreenPos(VECTOR mousePos) { m_mouseScreenPos = mousePos; }
	void SetMouseWorldPos(VECTOR mousePos) { m_mouseWorldPos = mousePos; }

	// �g���b�L���O�f�[�^���󂯎��
	void SeTrackingData(Tracking data);

private:
	// �J�����̈ʒu
	VECTOR m_pos;
	// �}�E�X�̈ʒu
	VECTOR m_mouseScreenPos;
	VECTOR m_mouseWorldPos;
	// �^�[�Q�b�g
	VECTOR m_targetPos;
	// �g���b�L���O�������Ȃ����ǂ���
	Tracking trackingData;
};

