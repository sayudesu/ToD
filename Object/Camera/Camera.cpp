#include "Camera.h"
#include "../../Util/Pad.h"

namespace
{
	// カメラ初期位置
//	const VECTOR kCameraPos = VGet(0.0f, 300.0f, -100.0f);
	const VECTOR kCameraPos = VGet(600.0f, 700.0f, -300.0f);
//	const VECTOR kCameraPos = VGet(0.0f, 500.0f, 0.0f);
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

	if (trackingData.tracking)
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
	trackingData.tracking = data.tracking;

	static int handle = LoadGraph("Data/Image/HpBg.png");
	//static int handle2 = LoadGraph("Data/Image/Hp.png");
	//static int handle3 = LoadGraph("Data/Image/Icon2.png");
	//static int hp2 = 0;
	//static float sizeX1;
	//static float sizeY1;

	//hp2--;

	//GetGraphSizeF(handle3, &sizeX1, &sizeY1);

	//sizeX1 += sizeX1;

	//DrawModiBillboard3D(
	//	VGet(m_pos.x, m_pos.y, m_pos.z),
	//	0.0f, 0.0f, sizeX1, 0.0f,
	//	sizeX1, -sizeY1, 0.0f, -sizeY1,
	//	handle, true);

	//DrawModiBillboard3D(
	//	VGet(100.0f, 100.0f, 100.0f),
	//	0.0f, 0.0f, sizeX1, 0.0f,
	//	sizeX1, -sizeY1, 0.0f, -sizeY1,
	//	handle, true);
	VERTEX3D Vertex[6]{};
	// ２ポリゴン分の頂点のデータをセット
	Vertex[0].pos = VGet(100.0f, 100.0f, 0.0f);
	Vertex[0].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[0].dif = GetColorU8(255, 255, 255, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;

	Vertex[1].pos = VGet(250.0f, 100.0f, 0.0f);
	Vertex[1].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[1].dif = GetColorU8(255, 0, 255, 255);
	Vertex[1].spc = GetColorU8(0, 0, 0, 0);
	Vertex[1].u = 0.0f;
	Vertex[1].v = 0.0f;
	Vertex[1].su = 0.0f;
	Vertex[1].sv = 0.0f;

	Vertex[2].pos = VGet(100.0f, 300.0f, 0.0f);
	Vertex[2].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[2].dif = GetColorU8(0, 255, 255, 255);
	Vertex[2].spc = GetColorU8(0, 0, 0, 0);
	Vertex[2].u = 0.0f;
	Vertex[2].v = 0.0f;
	Vertex[2].su = 0.0f;
	Vertex[2].sv = 0.0f;


	Vertex[3].pos = VGet(400.0f, 200.0f, 0.0f);
	Vertex[3].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[3].dif = GetColorU8(0, 255, 255, 255);
	Vertex[3].spc = GetColorU8(0, 0, 0, 0);
	Vertex[3].u = 0.0f;
	Vertex[3].v = 0.0f;
	Vertex[3].su = 0.0f;
	Vertex[3].sv = 0.0f;

	Vertex[4].pos = VGet(600.0f, 400.0f, 0.0f);
	Vertex[4].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[4].dif = GetColorU8(0, 0, 255, 255);
	Vertex[4].spc = GetColorU8(0, 0, 0, 0);
	Vertex[4].u = 0.0f;
	Vertex[4].v = 0.0f;
	Vertex[4].su = 0.0f;
	Vertex[4].sv = 0.0f;

	Vertex[5].pos = VGet(500.0f, 50.0f, 0.0f);
	Vertex[5].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[5].dif = GetColorU8(255, 0, 255, 255);
	Vertex[5].spc = GetColorU8(0, 0, 0, 0);
	Vertex[5].u = 0.0f;
	Vertex[5].v = 0.0f;
	Vertex[5].su = 0.0f;
	Vertex[5].sv = 0.0f;

	// ２ポリゴンの描画
	DrawPolygon3D(Vertex, 2, handle, false);

}
