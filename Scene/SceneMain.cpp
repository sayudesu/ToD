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

// ���Ƃŏ���
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
	// BGM�Đ�
	SoundFunctions::StartBgm(SoundFunctions::SoundIdBattle);
	SoundFunctions::SetVolume(SoundFunctions::SoundIdBattle, SaveDataFunctions::GetSoundData().Bgm);
	// �}�b�v�`�b�v���G�l�~�[�ɓn��
	// �R�[�h�̏����̗���̂����ł����Ȃ��Ă��܂������܂�
	m_pEnemy->SetMapChip(m_pMap->GetChip());
}

// �������
void SceneMain::End()
{
	// BGM��~
	SoundFunctions::StopBgm(SoundFunctions::SoundIdBattle);

	m_pCamera  ->End();
	m_pEnemy   ->End();
	m_pObstacle->End();
	m_pPlayer  ->End();
	m_pMap     ->End();
	m_catIn	   ->End();
	m_pUI      ->End();

	// �������̉��
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
			// ���������
			m_pParticle[i]->End();
			// �f���[�g����
			delete m_pParticle[i];
			m_pParticle[i] = nullptr;
			// �v�f�̍폜
			m_pParticle.erase(m_pParticle.begin() + i);
		}
	}
	for (int i = 0; i < m_pBlood.size(); i++)
	{
		if (m_pBlood[i]->IsGetErase())
		{
			// ���������
			m_pBlood[i]->End();
			// �f���[�g����
			delete m_pBlood[i];
			m_pBlood[i] = nullptr;
			// �v�f�̍폜
			m_pBlood.erase(m_pBlood.begin() + i);
		}
	}

	// �v���C���[����
	m_pPlayer->Update();
	// �v���C���[�̐ݒu����I�u�W�F�N�g
	m_pObstacle->Update();
	// �J����
	m_pCamera->Update();
	m_pCamera->SetPosPlayer(m_pPlayer->SetPos());
	// �G
	m_pEnemy->Update();
#if _DEBUG
	// �G�𐶐�(�f�o�b�O�p)
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

	// �I�u�W�F�N�g�𐶐�
	ObstructSelect data = m_pPlayer->GetObstructData();
	m_pUI->SetObstructData(data);
	m_pObstacle->Create(m_pPlayer->SetPos(), data.no, 0);
	m_pUI->SetObstructSelect(isOn);

	// ������	
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

	// �y�ʉ�����
	m_pObstacle->SetEraseShotData(m_eraseCollShotData);
	

	// UI�֌W
	m_pUI->Update();
	// �I�u�W�F�N�g�ݒu�R�X�g�̐����󂯎��
	m_pUI->SetCostSetObject(m_pPlayer->GetObjectCostNum());
	// �v���C���[�̈ʒu���󂯎��
	m_pUI->SetPlayerPos(m_pPlayer->SetPos());

	// ���o�֌W
	// ���o�ׂ̈ɃJ�����̃^�[�Q�b�g�ʒu�ύX
	m_pCamera->SeTrackingData(m_pPlayer->GetTracingData());
	// �J�b�g�C�����I����Ă��邩�ǂ����̔����n��
	m_pPlayer->IsSetShot(m_catIn->IsGetEnd());
	// �J�b�g�C���𑱂Ă����Ȃ��ׂ�
	m_catIn->IsSetEndReset();
	// ����U�������邩�ǂ���
	if (m_pPlayer->isSpecialAttack())
	{
		// ���o�J�n
		m_catIn->Update();
		if (m_catIn->IsGetEnd())
		{
			// �V���b�g�����Ă邩�ǂ���
			m_pPlayer->SpecialAttackReset();
			// ���o���Z�b�g
			m_catIn->Reset();
		}
	}


	// �V�[����؂�ւ��܂�
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

	// BGM���~�܂����������x�Đ�
	SoundFunctions::ReStartBgm(SoundFunctions::SoundIdBattle);

	// �X���C�h���J����
	SceneBase::UpdateSlider(m_isSliderOpen);

	return this;
}

void SceneMain::Draw()
{
	// �w�i�p
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xaaaa888, true);
	// �}�b�v�̕`��
	m_pMap->Draw();
	// ���̕`��
	for (auto& blood : m_pBlood)
	{
		blood->Draw();
	}
	// �G�̕`��
	m_pEnemy->Draw();
	// ��Q���̕`��
	m_pObstacle->Draw();
	// �v���C���[�p
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
	m_pPlayer->Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,255);

	// �I�u�W�F�N�g��UI
	m_pEnemy->DrawUI();
	m_pPlayer->DrawUI();
	// UI
	m_pUI->Draw();
	// ���oUI
	m_catIn->Draw();

	// ���̕`��
	for (auto& par : m_pParticle)
	{
		par->Draw();
	}

#if _DEBUG
	// �g��
	float y = 30.0f;
	// ����
	DrawLine3D(VGet(-100, y, -100),   VGet(1300.0f, y, -100),   0xff0000);
	DrawLine3D(VGet(-100, y,  700),    VGet(1300.0f, y, 700),   0xffff00);
	// �c��
	DrawLine3D(VGet(-100,    y, 0), VGet(-100,    y, 600), 0xff0000);
	DrawLine3D(VGet(1300.0f, y, 0), VGet(1300.0f, y, 600), 0xffff00);
#endif
	SceneBase::DrawSliderDoor();
}

// ����`�F�b�N
void SceneMain::CheckColl()
{
	// �G���V���b�g�ɓ����������𔻕�
	// �G�̐���
	for (int enemyNum = 0; enemyNum < m_pEnemy->GetNormalNum(); enemyNum++)
	{
		// �v���C���[�ݒu�I�u�W�F�N�g�̐���
		for (int objNum = 0; objNum < m_pObstacle->GetNum(); objNum++)
		{
			// �I�u�W�F�N�g���o���e�̐���
			for (int shotNum = 0; shotNum < m_pObstacle->GetShotNum(objNum); shotNum++)
			{
				// �����蔻�菈��
				if (m_pColl->UpdateCheck(
					m_pEnemy   ->GetCollData     ()[enemyNum]     .pos,
					m_pObstacle->GetCollShotDatas(objNum, shotNum).pos,
					m_pEnemy   ->GetCollData     ()[enemyNum]     .radius,
					m_pObstacle->GetCollShotDatas(objNum, shotNum).radius))
				{
					// �V���b�g���폜
					m_pObstacle->SetShotErase(objNum, shotNum, false);
					// �G�l�~�[�Ƀ_���[�W��^����
					m_pEnemy->SetHitDamage(enemyNum, m_pObstacle->GetCollShotDatas(objNum, shotNum).datage);

					// ���Ƃŕς���
					// �����o�鉉�o
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
