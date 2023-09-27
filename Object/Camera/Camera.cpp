#include "Camera.h"
#include "../../Util/Pad.h"
#include <corecrt_math.h>

namespace
{
	// �J���������ʒu
	const VECTOR kCameraPos = VGet(600.0f, 700.0f, -300.0f);
	// �J���������^�[�Q�b�g�ʒu
	const VECTOR kCameraTargetPos = VGet(kCameraPos.x, 0.0f, 300.0f);
	// ����p
	constexpr float kFov = 60.0f;
	// ����p�v�Z
	constexpr float kFovCalculation = kFov * DX_PI_F / 180.0f;
}

Camera::Camera():
	m_pos(kCameraPos),
	m_mouseScreenPos(VGet(0,0,0)),
	m_mouseWorldPos(VGet(0, 0, 0)),
	m_targetPos(kCameraTargetPos)
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	// �ǂ�����A�ǂ��܂Ō����邩
	SetCameraNearFar(100.0f, 4000.0f);
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
	
	//// �X�e�B�b�N�̈ʒu����J�����ʒu�ɕϊ�
	//int x = (input.Rx - 0) * (500  - 0) / (1000 - 0);
	//int z = (input.Ry - 0) * (500 - 0) / (1000 - 0);
	//m_pos.z = z + kCameraPos.z;
	//m_pos.x = x + kCameraPos.x;

	m_pos.y = m_tempPos.y + 500.0f;
	//m_pos.x = m_tempPos.x;

	VECTOR tempPos{};
	tempPos.x = m_tempPos.x;

	constexpr float speed = 15.0f;
	constexpr float speedTargetCamera = 15.0f;

	if (static_cast<int>(m_pos.x) > static_cast<int>(tempPos.x))
	{
		m_pos.x -= speed;
		if (static_cast<int>(m_pos.x) > static_cast<int>(tempPos.x) + 300.0f)
		{
			m_pos.x -= speedTargetCamera * 10;
		}
	}
	if(static_cast<int>(m_pos.x) < static_cast<int>(tempPos.x))
	{
		m_pos.x += speed;
		if (static_cast<int>(m_pos.x) < static_cast<int>(tempPos.x) - 300.0f)
		{
			m_pos.x += speedTargetCamera * 10;
		}
	}

	if (static_cast<int>(m_targetPos.x) > static_cast<int>(tempPos.x))
	{
		m_targetPos.x -= speedTargetCamera;
		if (static_cast<int>(m_targetPos.x) > static_cast<int>(tempPos.x) + 300.0f)
		{
			m_targetPos.x -= speedTargetCamera * 10;
		}
	}
	if (static_cast<int>(m_targetPos.x) < static_cast<int>(tempPos.x))
	{
		m_targetPos.x += speedTargetCamera;
		if (static_cast<int>(m_targetPos.x) < static_cast<int>(tempPos.x) - 300.0f)
		{
			m_targetPos.x += speedTargetCamera * 10;
		}
	}


//	m_targetPos.x = m_tempPos.x;
	m_targetPos.y = m_tempPos.y;

	if (trackingData.isTracking)
	{
		m_targetNowPos = trackingData.pos;
	}
	else
	{
		m_targetNowPos = m_targetPos;
	}

	// �ǂ������Ăǂ����݂邩
	SetCameraPositionAndTarget_UpVecY(m_pos, m_targetNowPos);
}

VECTOR Camera::SetPos() const
{
	return m_pos;
}

void Camera::SeTrackingData(Tracking data)
{
	trackingData.pos = data.pos;
	trackingData.isTracking = data.isTracking;
}

void Camera::SetPosPlayer(VECTOR pos)
{
	m_tempPos = pos;
}
