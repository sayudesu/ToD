#include "Camera.h"
#include "../../Util/Pad.h"
#include <corecrt_math.h>

namespace
{
	// カメラ初期位置
	const VECTOR kCameraPos = VGet(600.0f, 700.0f, -300.0f);
	// カメラ初期ターゲット位置
	const VECTOR kCameraTargetPos = VGet(kCameraPos.x, 0.0f, 300.0f);
	// 視野角
	constexpr float kFov = 60.0f;
	// 視野角計算
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
	// どこから、どこまで見えるか
	SetCameraNearFar(100.0f, 4000.0f);
	// どこを居てどこをみるか
	SetCameraPositionAndTarget_UpVecY(m_pos, m_targetPos);
	// 遠近法のセットアップ( ラジアン値に変換しています )
	SetupCamera_Perspective(kFovCalculation);
}

void Camera::End()
{
}

void Camera::Update()
{
	DINPUT_JOYSTATE input;

	// 入力状態を取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);
	
	//// スティックの位置からカメラ位置に変換
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

	// どこを居てどこをみるか
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
