#include "ObstacleNormalShot.h"
#include "../../Object/Shot/ShotBase.h"
#include "../../Effeck/EffekseerDrawer.h"

namespace
{
	// ショット最初打ち出すまでのフレームむカウント
	constexpr int kShotFirstFrameMax = 60;
	// ショット再放出するまでのフレーム
	constexpr int kShootFrameMax = 10;
	// オブジェクトカラー(緑)
	constexpr int kObjColor1 = 0x00ff00;
	// オブジェクトカラー(黄色)
	constexpr int kObjColor2 = 0xffff00;
}

ObstacleNormalShot::ObstacleNormalShot(VECTOR pos):
	m_shotFirstDelayFrameCount(0),
	m_shootFrameCount(0),
	m_objColor(kObjColor1)
{
	m_pos = pos;
	// 設置用関数に移動
	m_updateFunc = &ObstacleNormalShot::UpdateSetting;
	m_pEffect = new EffekseerDrawer;
}

ObstacleNormalShot::~ObstacleNormalShot()
{
}

void ObstacleNormalShot::Init()
{
	m_pEffect->Init();
}

void ObstacleNormalShot::End()
{

}

void ObstacleNormalShot::Update()
{
	(this->*m_updateFunc)();
}

void ObstacleNormalShot::UpdateSetting()
{
	m_pEffect->Update();
	m_pEffect->GetPos(m_pos);

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

		// エフェクトクラスのメモリ解放
		m_pEffect->End();
		delete m_pEffect;
		m_pEffect = nullptr;
	}
}

void ObstacleNormalShot::UpdateShot()
{
	m_shootFrameCount++;
	// ショットを出すスピート
	if (m_shootFrameCount > kShootFrameMax)
	{
		m_pShot.push_back(std::make_shared<ShotBase>(m_pos));
		m_shootFrameCount = 0;
	}

	for (auto& shot : m_pShot)
	{
		shot->Update();
	}

	static int a = 0;
	a++;
	if (a > 60 * 5)
	{
		test = true;
	//	a = 0;
	}
	
}

void ObstacleNormalShot::Draw()
{
	// オブジェクト描画
	DrawSphere3D(m_pos, 16, 16, m_objColor, m_objColor, true);

	for (auto& shot : m_pShot)
	{
		shot->Draw();
	}

	if (m_updateFunc == &ObstacleNormalShot::UpdateSetting)
	{
		m_pEffect->Draw();
	}
}

void ObstacleNormalShot::GetTarGetPos(VECTOR pos)
{
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i]->GetTargetPos(pos);
	}
}
