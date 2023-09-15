#include "Camera.h"
#include "../../Util/Pad.h"

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
	SetCameraNearFar(100.0f, 2000.0f);
	// どこを居てどこをみるか
	SetCameraPositionAndTarget_UpVecY(m_pos, m_targetPos);
	// 遠近法のセットアップ( ラジアン値に変換しています )
	SetupCamera_Perspective(kFovCalculation);

	//// カメラを正射影に変更
//	SetupCamera_Ortho(2000.0f);
}

void Camera::End()
{
}

void Camera::Update()
{
	DINPUT_JOYSTATE input;

	// 入力状態を取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);
	
	// スティックの位置からカメラ位置に変換
	int x = (input.Rx - 0) * (500  - 0) / (1000 - 0);
	int z = (input.Ry - 0) * (500 - 0) / (1000 - 0);
	m_pos.x = x + kCameraPos.x;
	m_pos.z = z + kCameraPos.z;

	VECTOR targetPos{};

	if (trackingData.isTracking)
	{
		targetPos = trackingData.pos;
	}
	else
	{
		targetPos = m_targetPos;
	}

	// どこを居てどこをみるか
	SetCameraPositionAndTarget_UpVecY(m_pos, targetPos);
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
