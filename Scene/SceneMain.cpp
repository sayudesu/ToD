#include <DxLib.h>
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneGameClear.h"
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
#include "../Util/ObstructSelectNo.h"
#include "../ParticleDrawer.h"
#include "../BloodDrawer.h"

// あとで消す
#include "../Util/Pad.h"

SceneMain::SceneMain():
	m_pCamera  (nullptr),
	m_pEnemy   (nullptr),
	m_pObstacle(nullptr),
	m_pPlayer  (nullptr),
	m_pMap     (nullptr),
	m_pColl    (nullptr),
	m_catIn    (nullptr),
	m_pUI      (nullptr)
{	
	m_pCamera   = new Camera();
	m_pEnemy    = new EnemyManager();
	m_pObstacle = new ObstacleManager();
	m_pPlayer   = new Player();
	m_pMap      = new MapDrawer();
	m_pColl     = new Collision3D();
	m_catIn     = new CutInDrawer();
	m_pUI       = new UIDrawer();
}

SceneMain::~SceneMain()
{

}

void SceneMain::Init()
{
	m_pCamera  ->Init();
	m_pObstacle->Init();
	m_pMap     ->Init();
	m_pPlayer  ->Init(m_pMap->GetChip());
	m_catIn    ->Init();
	m_pUI      ->Init();

	//SaveDataFunctions::Load();
	// BGM再生
	SoundFunctions::StartBgm(SoundFunctions::SoundIdBattle);
	SoundFunctions::SetVolume(SoundFunctions::SoundIdBattle, SaveDataFunctions::GetSoundData().Bgm);
	// マップチップをエネミーに渡す
	// コードの処理の流れのせいでこうなっています治します
	m_pEnemy->SetMapChip(m_pMap->GetChip());
}

// 解放処理
void SceneMain::End()
{
	// BGM停止
	SoundFunctions::StopBgm(SoundFunctions::SoundIdBattle);

	m_pCamera  ->End();
	m_pEnemy   ->End();
	m_pObstacle->End();
	m_pPlayer  ->End();
	m_pMap     ->End();
	m_catIn	   ->End();
	m_pUI      ->End();

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

	for (int i = 0; i < m_pParticle.size(); i++)
	{
		m_pParticle[i]->End();
		delete m_pParticle[i];
		m_pParticle[i] = nullptr;
	}
	for (int i = 0; i < m_pBlood.size(); i++)
	{
		m_pBlood[i]->End();
		delete m_pBlood[i];
		m_pBlood[i] = nullptr;
	}
}

SceneBase* SceneMain::Update()
{
	for (int enemyNum = 0; enemyNum < m_pEnemy->GetNormalNum(); enemyNum++)
	{
		if (m_pEnemy->GetCollData()[enemyNum].isHit)
		{
			for (int i = 0; i < 10; i++)
			{
				m_pParticle.push_back(new ParticleDrawer(m_pEnemy->GetCollData()[enemyNum].pos));
				m_pParticle.back()->Init(i);
			}
		}
	}
	for (int i = 0; i < m_pParticle.size(); i++)
	{
		if (m_pParticle[i]->IsGetErase())
		{
			// メモリ解放
			m_pParticle[i]->End();
			// デリート処理
			delete m_pParticle[i];
			m_pParticle[i] = nullptr;
			// 要素の削除
			m_pParticle.erase(m_pParticle.begin() + i);
		}
	}
	for (int i = 0; i < m_pBlood.size(); i++)
	{
		if (m_pBlood[i]->IsGetErase())
		{
			// メモリ解放
			m_pBlood[i]->End();
			// デリート処理
			delete m_pBlood[i];
			m_pBlood[i] = nullptr;
			// 要素の削除
			m_pBlood.erase(m_pBlood.begin() + i);
		}
	}

	// プレイヤー操作
	m_pPlayer->Update();
	// プレイヤーの設置するオブジェクト
	m_pObstacle->Update();
	// カメラ
	m_pCamera->Update();
	m_pCamera->SetPosPlayer(m_pPlayer->SetPos());
	// 敵
	m_pEnemy->Update();
#if _DEBUG
	// 敵を生成(デバッグ用)
	if (Pad::isPress(PAD_INPUT_2))
	{
		m_pEnemy->Create();
		m_pEnemy->SetMapChip(m_pMap->GetChip());
	}
#else
	m_pEnemy->Create();
	m_pEnemy->SetMapChip(m_pMap->GetChip());
#endif
	bool isOn = m_pPlayer->GetObjCreate();

	// オブジェクトを生成
	ObstructSelect data = m_pPlayer->GetObstructData();
	m_pUI->SetObstructData(data);
	m_pObstacle->Create(m_pPlayer->SetPos(), data.no, 0);
	m_pUI->SetObstructSelect(isOn);

	// 判定情報	
	m_pObstacle->SetCollEnemyDatas(m_pEnemy->GetCollData());
	CheckColl();


	for (int i = 0; i < m_pEnemy->GetCollData().size(); i++)
	{
		if (m_pEnemy->GetCollData()[i].isAttack)
		{
			m_pUI->SetDamage(m_pEnemy->GetCollData()[i].datage);
		}
	}

	for (auto& par : m_pParticle)
	{
		par->Update();
	}

	for (auto& blood : m_pBlood)
	{
		blood->Update();
	}

	// 軽量化処理
	m_pObstacle->SetEraseShotData(m_eraseCollShotData);
	

	// UI関係
	m_pUI->Update();
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
		//m_isChangeScene = true;
		m_isSliderOpen = true;
		isTitle = true;
	}
	if (isTitle)
	{
		if (SceneBase::UpdateSliderClose())
		{
			return new SceneTitle;
		}
	}

#if _DEBUG
#else
	if (m_pUI->GetDead())
	{
		// m_isChangeScene = true;
		m_isSliderOpen = true;
		isEnd = true;
	}
	if (isEnd)
	{
		if (SceneBase::UpdateSliderClose())
		{
			return new  SceneGameClear(1);
		}
	}

	if (m_pUI->GetClear())
	{
		// m_isChangeScene = true;
		m_isSliderOpen = true;
		isC = true;
	}
	if (isC)
	{
		if (SceneBase::UpdateSliderClose())
		{
			return new SceneGameClear(0);
		}
	}
#endif

	// BGMが止まったらもう一度再生
	SoundFunctions::ReStartBgm(SoundFunctions::SoundIdBattle);

	// スライドを開ける
	SceneBase::UpdateSlider(m_isSliderOpen);

	return this;
}

void SceneMain::Draw()
{
	// 背景用
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xaaaa888, true);
	// マップの描画
	m_pMap->Draw();
	// 血の描画
	for (auto& blood : m_pBlood)
	{
		blood->Draw();
	}
	// 敵の描画
	m_pEnemy->Draw();
	// 障害物の描画
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

	// 肉の描画
	for (auto& par : m_pParticle)
	{
		par->Draw();
	}

#if _DEBUG
	// 枠線
	float y = 30.0f;
	// 横線
	DrawLine3D(VGet(-100, y, -100),   VGet(1300.0f, y, -100),   0xff0000);
	DrawLine3D(VGet(-100, y,  700),    VGet(1300.0f, y, 700),   0xffff00);
	// 縦線
	DrawLine3D(VGet(-100,    y, 0), VGet(-100,    y, 600), 0xff0000);
	DrawLine3D(VGet(1300.0f, y, 0), VGet(1300.0f, y, 600), 0xffff00);
#endif
	SceneBase::DrawSliderDoor();
}

// 判定チェック
void SceneMain::CheckColl()
{
	// 敵がショットに当たったかを判別
	// 敵の数分
	for (int enemyNum = 0; enemyNum < m_pEnemy->GetNormalNum(); enemyNum++)
	{
		// プレイヤー設置オブジェクトの数分
		for (int objNum = 0; objNum < m_pObstacle->GetNum(); objNum++)
		{
			// オブジェクトが出す弾の数分
			for (int shotNum = 0; shotNum < m_pObstacle->GetShotNum(objNum); shotNum++)
			{
				// 当たり判定処理
				if (m_pColl->UpdateCheck(
					m_pEnemy   ->GetCollData     ()[enemyNum]     .pos,
					m_pObstacle->GetCollShotDatas(objNum, shotNum).pos,
					m_pEnemy   ->GetCollData     ()[enemyNum]     .radius,
					m_pObstacle->GetCollShotDatas(objNum, shotNum).radius))
				{
					// ショットを削除
					m_pObstacle->SetShotErase(objNum, shotNum, false);
					// エネミーにダメージを与える
					m_pEnemy->SetHitDamage(enemyNum, m_pObstacle->GetCollShotDatas(objNum, shotNum).datage);

					// あとで変える
					// 血が出る演出
					for (int i = 0; i < 10; i++)
					{
						m_pBlood.push_back(new BloodDrawer(m_pEnemy->GetCollData()[enemyNum].pos));
						m_pBlood.back()->Init(i);
					}
				}

				if (m_pColl->UpdateCheck(
					m_pEnemy->GetCollData()[enemyNum].pos,
					m_pPlayer->GetCollShotDatas().pos,
					m_pEnemy->GetCollData()[enemyNum].radius,
					m_pPlayer->GetCollShotDatas().radius))
				{
					printfDx("aaa");
				}
			}
		}
	}
}
