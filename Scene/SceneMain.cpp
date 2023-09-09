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
#include "../Save/SaveDataFunctions.h"
#include "../Util/Collision3D.h"
#include "../Util/CutInDrawer.h"
#include "../UIDrawer.h"

// あとで消す
#include "../Util/Pad.h"

SceneMain::SceneMain():
	m_pCamera(nullptr),
	m_pEnemy(nullptr),
	m_pObstacle(nullptr),
	m_pPlayer(nullptr),
	m_pMap(nullptr),
	m_pColl(nullptr),
	m_catIn(nullptr),
	m_pUI(nullptr)
{
	// カメラクラスのインスタンス作成
	m_pCamera = new Camera();
	// 敵クラスのインスタンス作成
	m_pEnemy = new EnemyManager();
	// 障害物クラスのインスタンス作成
	m_pObstacle = new ObstacleManager();
	// プレイヤークラスのインスタンス作成
	m_pPlayer = new Player();
	// マップクラスのインスタンス作成
	m_pMap = new MapDrawer();
	// 3D当たり判定用のインスタンス
	m_pColl = new Collision3D();
	// カットインのインスタンス
	m_catIn = new CutInDrawer();
	// UIを描画するクラスのインスタンス
	m_pUI = new UIDrawer();
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
	delete m_catIn;
	m_catIn = nullptr;
	delete m_pUI;
	m_pUI = nullptr;
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
	m_catIn->Init();
	m_pUI->Init();

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
	m_catIn->End();
	m_pUI->End();
}

SceneBase* SceneMain::Update()
{
	// プレイヤー操作
	m_pPlayer->Update();
	// プレイヤーの設置するオブジェクト
	m_pObstacle->Update();
	// カメラ
	m_pCamera->Update();
	// 敵
	m_pEnemy->Update();
	// マップ
	m_pMap->Update();	

	// 敵を生成(デバッグ用)
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_pEnemy->Create();
		m_pEnemy->SetMapChip(m_pMap->GetMapChip());
	}

	// オブジェクトを生成
	if (m_pPlayer->GetObjCreate())
	{
		m_pObstacle->Create(m_pPlayer->SetPos());
	}

	// 判定情報	
	m_pEnemy->SetObjCollData(m_pObstacle->GetCollDatas());
	m_pObstacle->SetCollEnemyDatas(m_pEnemy->GetCollData());

	CheckColl();
	

	// UI関係
	// オブジェクト設置コストの数を受け取る
	m_pUI->SetCostSetObject(m_pPlayer->GetObjectCostNum());
	// プレイヤーの位置を受け取る
	m_pUI->SetPlayerPos(m_pPlayer->SetPos());

	// 演出関係
	// 演出の為にカメラのターゲット位置変更
	m_pCamera->SeTrackingData(m_pPlayer->GetTracingData());
	// カットインが終わっているかどうかの判定を渡す
	m_pPlayer->IsSetShot(m_catIn->IsGetEnd());
	// カットインを続てけしない為に
	m_catIn->IsSetEndReset();
	// 特殊攻撃をするかどうか
	if (m_pPlayer->isSpecialAttack())
	{
		// 演出開始
		m_catIn->Update();
		if (m_catIn->IsGetEnd())
		{
			// ショットを撃てるかどうか
			m_pPlayer->SpecialAttackReset();
			// 演出リセット
			m_catIn->Reset();
		}
	}

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

	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xaaaa888, true);
	m_pMap->Draw();
	m_pEnemy->Draw();
	m_pObstacle->Draw();
	
	// プレイヤー用
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
	m_pPlayer->Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,255);

	// オブジェクトのUI
	m_pEnemy->DrawUI();
	m_pPlayer->DrawUI();

	// UI
	m_pUI->Draw();
	// 演出UI
	m_catIn->Draw();

	SceneBase::DrawSliderDoor();
}

// 判定チェック
std::vector<int> SceneMain::CheckColl()
{
	// 当たったショットのナンバーをみる
	std::vector<int> hitShotNo;

	// 敵がショットに当たったかを判別
	for (int enemyNum = 0; enemyNum < m_pEnemy->GetNormalNum(); enemyNum++)
	{
		for (int shotNum = 0; shotNum < m_pObstacle->GetCollDatas().size(); shotNum++)
		{
			if (m_pColl->UpdateCheck(
				m_pEnemy->GetCollData()[enemyNum].pos,
				m_pObstacle->GetCollDatas()[shotNum].pos,
				m_pEnemy->GetCollData()[enemyNum].radius,
				m_pObstacle->GetCollDatas()[enemyNum].radius))
			{
				printfDx("Hit\n");
				hitShotNo.push_back(shotNum);
			}
		}
	}

	return hitShotNo;
}
