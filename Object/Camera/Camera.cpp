#include "Camera.h"
#include "../../Util/Pad.h"

namespace
{
	// �J���������ʒu
//	const VECTOR kCameraPos = VGet(0.0f, 300.0f, -100.0f);
	const VECTOR kCameraPos = VGet(0.0f, 700.0f, -400.0f);
//	const VECTOR kCameraPos = VGet(0.0f, 500.0f, 0.0f);
	// �J���������^�[�Q�b�g�ʒu
	const VECTOR kCameraTargetPos = VGet(0.0f, 0.0f, 0.0f);
	// ����p
	constexpr float kFov = 60.0f;
	// ����p�v�Z
	constexpr float kFovCalculation = kFov * DX_PI_F / 180.0f;
}

Camera::Camera():
	m_pos(kCameraPos),
	m_targetPos(kCameraTargetPos)
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
	SetCameraPositionAndTarget_UpVecY(m_pos, m_targetPos);
	// ���ߖ@�̃Z�b�g�A�b�v( ���W�A���l�ɕϊ����Ă��܂� )
	SetupCamera_Perspective(kFovCalculation);
}

void Camera::End()
{
}

void Camera::Update()
{
	DINPUT_JOYSTATE input;

	// ���͏�Ԃ��擾
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	// �X�e�B�b�N�̈ʒu����J�����ʒu�ɕϊ�
	int x = (input.Rx - 0) * (500 - 0) / (1000 - 0);
	int z = (input.Ry - 0) * (1000 - 0) / (1000 - 0);
	m_pos.x = x;
	m_pos.z = z + kCameraPos.z;

	// �ǂ������Ăǂ����݂邩
	SetCameraPositionAndTarget_UpVecY(m_pos, m_targetPos);
}

VECTOR Camera::SetPos() const
{
	return m_pos;
}

void Camera::GetTargetPos(VECTOR targetPos)
{
	VECTOR tempPos = targetPos;

	if (targetPos.z > m_targetPos.z)m_targetPos.z += 10;
	if (targetPos.z < m_targetPos.z)m_targetPos.z -= 10;
}
