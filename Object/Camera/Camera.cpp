#include "Camera.h"
#include "Util/Pad.h"

namespace
{
	// �J���������ʒu
//	const VECTOR kCameraPos = VGet(0.0f, 300.0f, -100.0f);
	const VECTOR kCameraPos = VGet(0.0f, 500.0f, -0.00001f);
//	const VECTOR kCameraPos = VGet(0.0f, 500.0f, 0.0f);
	// �J���������^�[�Q�b�g�ʒu
	const VECTOR kCameraTargetPos = VGet(0.0f, 0.0f, 0.0f);
	// ����p
	constexpr float kFov = 60.0f;
	// ����p�v�Z
	constexpr float kFovCalculation = kFov * DX_PI_F / 180.0f;
}

Camera::Camera():
	m_pos(kCameraPos)
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	// �ǂ�����A�ǂ��܂Ō����邩
	SetCameraNearFar(100.0f, 2000.0f);
	// �ǂ������Ăǂ����݂邩
	SetCameraPositionAndTarget_UpVecY(m_pos, kCameraTargetPos);
	// ���ߖ@�̃Z�b�g�A�b�v( ���W�A���l�ɕϊ����Ă��܂� )
	SetupCamera_Perspective(kFovCalculation);
}

void Camera::End()
{
}

void Camera::Update()
{
	// �ǂ������Ăǂ����݂邩
	SetCameraPositionAndTarget_UpVecY(m_pos, kCameraTargetPos);

	//m_mouseScreenPos.y = 300.0f;
	////m_mouseWorldPos.y = 0.0f;
	//SetCameraPositionAndTarget_UpVecY(m_mouseScreenPos, m_mouseWorldPos);

	//const float cameraSpeed = 10.0f;
	//if (Pad::isPress(PAD_INPUT_UP))
	//{
	//	m_pos.y += cameraSpeed;
	//}
	//else if (Pad::isPress(PAD_INPUT_DOWN))
	//{
	//	m_pos.y -= cameraSpeed;
	//}
}
