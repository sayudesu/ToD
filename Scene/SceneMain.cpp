#include <DxLib.h>
#include "SceneMain.h"
#include "SceneTitle.h"
#include "Object/Camera/Camera.h"
#include "Object/Enemy/EnemyManager.h"
#include "Object/ObstacleManager.h"
#include "Object/Player/Player.h"
#include "Object/Map/Map.h"

// あとで消す
#include "Util/Pad.h"

SceneMain::SceneMain():
	m_pCamera(nullptr),
	m_pEnemy(nullptr),
	m_pObstacle(nullptr)
{
	// カメラクラスのインスタンス作成
	m_pCamera = new Camera;
	// 敵クラスのインスタンス作成
	m_pEnemy = new EnemyManager;
	// 障害物クラスのインスタンス作成
	m_pObstacle = new ObstacleManager;
	// プレイヤークラスのインスタンス作成
	m_pPlayer = new Player;
	// マップクラスのインスタンス作成
	m_pMap = new Map;
}

SceneMain::~SceneMain()
{
	// メモリの解放
	delete m_pCamera;
	delete m_pEnemy;
	delete m_pObstacle;
	delete m_pPlayer;
	delete m_pMap;
}

void SceneMain::Init()
{
	// 3D関連の設定
	// Zバッファを使用する
	SetUseZBuffer3D(true);
	// Zバッファへの書き込みを行う
	SetWriteZBuffer3D(true);
	// ポリゴンの裏面を描画しない
	SetUseBackCulling(true);
	m_pCamera->Init();
	m_pEnemy->Init();
	m_pObstacle->Init();
	m_pPlayer->Init();
	m_pMap->Init();
}

void SceneMain::End()
{
	m_pCamera->End();
	m_pEnemy->End();
	m_pObstacle->End();
	m_pPlayer->End();
	m_pMap->End();
}

SceneBase* SceneMain::Update()
{
	m_pCamera->GetMouseScreenPos(m_pPlayer->SetMouseScreenPos());
	m_pCamera->GetMouseWorldPos(m_pPlayer->SetMouseWorldPos());


	m_pCamera->Update();
	m_pEnemy->Update();
	m_pObstacle->Update();
	m_pPlayer->Update();
	m_pMap->Update();
	
	// 敵を生成(デバッグ用)
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_pEnemy->Create(1);
	}
	// オブジェクトを生成
	if (m_pPlayer->SetMouseLeft())
	{
		m_pObstacle->Create(m_pPlayer->SetMouseScreenPos());
	}

	if (Pad::isTrigger(PAD_INPUT_8))
	{
		m_isChangeScene = true;
		m_isSliderOpen = true;
	}

	if (m_isChangeScene)
	{
		if (SceneBase::UpdateSliderClose())
		{
			return new SceneTitle;
		}
	}
	// スライドを開ける
	SceneBase::UpdateSlider(m_isSliderOpen);
	return this;
}

void SceneMain::Draw()
{
	m_pMap->Draw();
	m_pEnemy->Draw();
	m_pObstacle->Draw();
	m_pPlayer->Draw();

	float lineScale = 300.0f;
	for (int X = -150; X < 1000; X += 30)
	{
		const VECTOR a = VGet(-lineScale, 0, X);
		const VECTOR b = VGet(lineScale, 0, X);

		DrawLine3D(a, b, 0xffffff);
	}
	for (int X = -150; X < 1000; X += 30)
	{
		const VECTOR a = VGet(X, 0, -lineScale);
		const VECTOR b = VGet(X, 0, lineScale);

		DrawLine3D(a, b, 0xffffff);
	}

	SceneBase::DrawSliderDoor();
}

