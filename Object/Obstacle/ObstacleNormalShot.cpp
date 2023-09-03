#include "ObstacleNormalShot.h"
#include "../../Object/Shot/ShotBase.h"
#include "../../Object/Shot/NormalShot.h"
#include "../../Effeck/EffekseerDrawer.h"
#include "../../Util/SoundFunctions.h"
#include <math.h>

const bool ef = false;

namespace
{
	// ショット最初打ち出すまでのフレームむカウント
	constexpr int kShotFirstFrameMax = 30;
	// ショット再放出するまでのフレーム
	constexpr int kShootFrameMax = 30;
	// オブジェクトカラー(緑)
	constexpr int kObjColor1 = 0x00ff00;
	// オブジェクトカラー(黄色)
	constexpr int kObjColor2 = 0xffff00;

	// 大砲モデルのパスの位置
	const char* kCannonBasePathName = "Data/Model/CannonBase.mv1";
	const char* kCannonPathName = "Data/Model/Cannon.mv1";

	//const VECTOR kConnonScale = VGet(0.1f, 0.1f, 0.1f);
	const VECTOR kConnonScale = VGet(1.0f, 1.0f, 1.0f);
}

ObstacleNormalShot::ObstacleNormalShot(VECTOR pos):
	m_hCannon(-1),
	m_hCannonBaes(-1),
	m_shotFirstDelayFrameCount(0),
	m_countShotNum(-1),
	m_shootFrameCount(0),
	m_objColor(kObjColor1)
{
	m_pos = pos;
	// 設置用関数に移動
	m_updateFunc = &ObstacleNormalShot::UpdateSetting;

	if(ef)m_pEffect = new EffekseerDrawer;
}

ObstacleNormalShot::~ObstacleNormalShot()
{
}

void ObstacleNormalShot::Init()
{
	if (ef)m_pEffect->Init();
	// 設置音
	SoundFunctions::Play(SoundFunctions::SoundIdSet);

	// 大砲モデルのロード
	m_hCannonBaes = MV1LoadModel(kCannonBasePathName);
	m_hCannon = MV1LoadModel(kCannonPathName);
	// 大砲モデルの位置
	MV1SetPosition(m_hCannonBaes, VGet(m_pos.x, m_pos.y + 12.0f, m_pos.z));
	MV1SetPosition(m_hCannon, VGet(m_pos.x, m_pos.y + 20.0f, m_pos.z));
	// 大砲モデルのサイズ変更
	MV1SetScale(m_hCannonBaes, kConnonScale);
	MV1SetScale(m_hCannon, kConnonScale);
}

void ObstacleNormalShot::End()
{
	if (ef)
	{
		m_pEffect->End();
		delete m_pEffect;
		m_pEffect = nullptr;
	}

	// モデルのデリート
	MV1DeleteModel(m_hCannonBaes);
	MV1DeleteModel(m_hCannon);
}

void ObstacleNormalShot::Update()
{
	(this->*m_updateFunc)();
}

void ObstacleNormalShot::UpdateSetting()
{

	if (ef)
	{
		m_pEffect->Update();
		m_pEffect->GetPos(m_pos);
	}

	// ショットの打ち出しまでのフレームをカウントする
	m_shotFirstDelayFrameCount++;
	if (m_shotFirstDelayFrameCount > kShotFirstFrameMax)
	{
		// ショット用関数に移動
		m_updateFunc = &ObstacleNormalShot::UpdateShot;
		// オブジェクトの色変更
		m_objColor = kObjColor2;
		// カウントリセット
		m_shotFirstDelayFrameCount = 0;

		if (ef)
		{
			// エフェクトクラスのメモリ解放
			m_pEffect->End();
			delete m_pEffect;
			m_pEffect = nullptr;
		}
	}
}

void ObstacleNormalShot::UpdateShot()
{
	m_shootFrameCount++;
	// ショットを出すスピート
	if (m_shootFrameCount > kShootFrameMax)
	{
		m_countShotNum++;
		m_pShot.push_back(std::make_shared<NormalShot>(m_countShotNum,m_pos));
		m_pShot[m_countShotNum]->Init(m_targetPos,VGet(1.0f, 1.0f, 1.0f), VGet(0.0f, 180.0f, 0.0f),10.0f);
		m_shootFrameCount = 0;
	}

	for (auto& shot : m_pShot)
	{
		shot->Update();
	}	

	// モデルの回転行列を計算して設定
	VECTOR dir2 = VSub(m_targetPos, m_pos);
	const float angle2 = atan2f(dir2.x, dir2.z) + -90.0f * DX_PI_F / 180.0f;
	MV1SetRotationXYZ(m_hCannon, VGet(0.0f, angle2, 0.0f));
}

void ObstacleNormalShot::Draw()
{
	// オブジェクト描画
	DrawSphere3D(m_pos, 16, 16, m_objColor, m_objColor, true);

	for (auto& shot : m_pShot)
	{
		shot->Draw();
	}
	if (ef)
	{
		// エフェクト描画
		if (m_updateFunc == &ObstacleNormalShot::UpdateSetting)
		{
			m_pEffect->Draw();
		}
	}

	// 3D描画モデル
	MV1DrawModel(m_hCannonBaes);
	MV1DrawModel(m_hCannon);
}

// 判定データを渡す
std::vector<CollData> ObstacleNormalShot::GetCollDatas()
{
	std::vector<CollData> collData;

	if (m_countShotNum != -1)
	{
		for(auto& shotData : m_pShot)
		{
			collData.push_back(shotData->GetCollData());
		}
	}

	return collData;
}

int ObstacleNormalShot::SetShotNum()
{
	return static_cast<int>(m_pShot.size());
}

void ObstacleNormalShot::SetTarGetPos(VECTOR pos)
{
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i]->SetTargetPos(pos);
	}
}
