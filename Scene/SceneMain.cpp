#include <DxLib.h>
#include "SceneMain.h"
#include "SceneTitle.h"
#include "../Object/Camera/Camera.h"
#include "../Object/Enemy/EnemyManager.h"
#include "../Object/Obstacle/ObstacleManager.h"
#include "../Object/Player/Player.h"
#include "../Object/Map/MapDrawer.h"
#include "../Util/game.h"
#include "../Util/SoundFunctions.h"
#include "../SaveDataFunctions.h"
#include "../Util/Collision3D.h"

// あとで消す
#include "../Util/Pad.h"

SceneMain::SceneMain():
	m_pCamera(nullptr),
	m_pEnemy(nullptr),
	m_pObstacle(nullptr),
	m_pPlayer(nullptr),
	m_pMap(nullptr),
	m_pColl(nullptr)
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
	m_pMap = new MapDrawer;
	// 3D当たり判定用のインスタンス
	m_pColl = new Collision3D;
}

SceneMain::~SceneMain()
{

	// BGM停止
	SoundFunctions::StopBgm(SoundFunctions::SoundIdBattle);

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
	delete m_pColl;
	m_pColl = nullptr;
}

void SceneMain::Init()
{
	//SaveDataFunctions::Load();
	// BGM再生
	SoundFunctions::StartBgm(SoundFunctions::SoundIdBattle);
	SoundFunctions::SetVolume(SoundFunctions::SoundIdBattle, SaveDataFunctions::GetSoundData().Bgm);


	m_pCamera->Init();
	m_pObstacle->Init();
	m_pPlayer->Init();
	m_pMap->Init();

	// マップチップをエネミーに渡す
	// コードの処理の流れのせいでこうなっています治します
	m_pEnemy->SetMapChip(m_pMap->GetMapChip());
	m_pEnemy->Create();
	m_pEnemy->SetMapChip(m_pMap->GetMapChip());

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

	m_pObstacle->SetTarGetPos(m_pEnemy->SetNormalPos(m_pEnemy->SetNormalNum()));

	// プレイヤー操作
	m_pPlayer->Update();
	// プレイヤーの設置するオブジェクト
	m_pObstacle->Update();
	// カメラ
	m_pCamera->Update();
	//m_pCamera->GetMouseScreenPos(m_pPlayer->SetPos());
	//m_pCamera->GetMouseWorldPos(m_pPlayer->SetMouseWorldPos());
	// 敵
	m_pEnemy->Update();
	// マップ
	m_pMap->Update();
	
	// 
	m_pCamera->GetTargetPos(m_pPlayer->SetPos());

	// 敵を生成(デバッグ用)
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_pEnemy->Create();
		m_pEnemy->SetMapChip(m_pMap->GetMapChip());
	}
	// オブジェクトを生成
	if (m_pPlayer->SetMouseLeft())
	{
		m_pObstacle->Create(m_pPlayer->SetPos());
	}

	// 判定処理
	std::vector<VECTOR> pos1;
	std::vector<VECTOR> pos2;
	for (int i = 0; i < m_pObstacle->GetNormalNum(); i++)
	{
		pos1.push_back(m_pObstacle->GetPos(i));
	}
	for (int i = 0; i < m_pEnemy->GetNormalNum(); i++)
	{
		pos2.push_back(m_pEnemy->SetNormalPos2(i));
	}
	m_pColl->UpdateCheck(pos1, pos2);


	// シーンを切り替えます
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

	// BGMが止まったらもう一度再生
	SoundFunctions::ReStartBgm(SoundFunctions::SoundIdBattle);

	// スライドを開ける
	SceneBase::UpdateSlider(m_isSliderOpen);

	return this;
}

void SceneMain::Draw()
{

	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xdddd888, true);
	m_pMap->Draw();
	m_pEnemy->Draw();
	m_pObstacle->Draw();
	m_pPlayer->DrawUI();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
	m_pPlayer->Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,255);

	SceneBase::DrawSliderDoor();
}
