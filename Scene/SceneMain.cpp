#include <DxLib.h>
#include "SceneMain.h"
#include "SceneTitle.h"
#include "Object/Camera/Camera.h"
#include "Object/Enemy/EnemyManager.h"
#include "Object/Obstacle/ObstacleManager.h"
#include "Object/Player/Player.h"
#include "Object/Map/Map.h"
#include "Util/game.h"
// あとで消す
#include "Util/Pad.h"

SceneMain::SceneMain():
	m_pCamera(nullptr),
	m_pEnemy(nullptr),
	m_pObstacle(nullptr),
	m_pPlayer(nullptr),
	m_pMap(nullptr)
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
	m_pCamera = nullptr;
	delete m_pEnemy;
	m_pEnemy = nullptr;
	delete m_pObstacle;
	m_pObstacle = nullptr;
	delete m_pPlayer;
	m_pPlayer = nullptr;
	delete m_pMap;
	m_pMap = nullptr;
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
#if true
	static VECTOR pos = VGet(0,0,0);
	static float speed = 10.0f;
	if (Pad::isPress(PAD_INPUT_LEFT))	pos.x -= speed;
	if (Pad::isPress(PAD_INPUT_RIGHT))pos.x += speed;
	if (Pad::isPress(PAD_INPUT_UP))	pos.z += speed;
	if (Pad::isPress(PAD_INPUT_DOWN))	pos.z -= speed;
	m_pObstacle->GetTarGetPos(pos);
#endif
	// プレイヤー操作
	m_pPlayer->Update();
	// プレイヤーの設置するオブジェクト
	m_pObstacle->Update();
	// カメラ
	m_pCamera->Update();
	m_pCamera->GetMouseScreenPos(m_pPlayer->SetMouseScreenPos());
	m_pCamera->GetMouseWorldPos(m_pPlayer->SetMouseWorldPos());
	// 敵
	m_pEnemy->Update();
	// マップ
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
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xaaaaaa, true);
	m_pMap->Draw();
	m_pEnemy->Draw();
	m_pObstacle->Draw();
	m_pPlayer->Draw();

	constexpr float lineScale = 300.0f;
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

