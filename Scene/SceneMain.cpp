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

// ���Ƃŏ���
#include "../Util/Pad.h"

SceneMain::SceneMain():
	m_pCamera(nullptr),
	m_pEnemy(nullptr),
	m_pObstacle(nullptr),
	m_pPlayer(nullptr),
	m_pMap(nullptr),
	m_pColl(nullptr)
{
	// �J�����N���X�̃C���X�^���X�쐬
	m_pCamera = new Camera;
	// �G�N���X�̃C���X�^���X�쐬
	m_pEnemy = new EnemyManager;
	// ��Q���N���X�̃C���X�^���X�쐬
	m_pObstacle = new ObstacleManager;
	// �v���C���[�N���X�̃C���X�^���X�쐬
	m_pPlayer = new Player;
	// �}�b�v�N���X�̃C���X�^���X�쐬
	m_pMap = new MapDrawer;
	// 3D�����蔻��p�̃C���X�^���X
	m_pColl = new Collision3D;
}

SceneMain::~SceneMain()
{

	// BGM��~
	SoundFunctions::StopBgm(SoundFunctions::SoundIdBattle);

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
}

void SceneMain::Init()
{
	//SaveDataFunctions::Load();
	// BGM�Đ�
	SoundFunctions::StartBgm(SoundFunctions::SoundIdBattle);
	SoundFunctions::SetVolume(SoundFunctions::SoundIdBattle, SaveDataFunctions::GetSoundData().Bgm);


	m_pCamera->Init();
	m_pObstacle->Init();
	m_pPlayer->Init();
	m_pMap->Init();

	// �}�b�v�`�b�v���G�l�~�[�ɓn��
	// �R�[�h�̏����̗���̂����ł����Ȃ��Ă��܂������܂�
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

	// �v���C���[����
	m_pPlayer->Update();
	// �v���C���[�̐ݒu����I�u�W�F�N�g
	m_pObstacle->Update();
	// �J����
	m_pCamera->Update();
	//m_pCamera->GetMouseScreenPos(m_pPlayer->SetPos());
	//m_pCamera->GetMouseWorldPos(m_pPlayer->SetMouseWorldPos());
	// �G
	m_pEnemy->Update();
	// �}�b�v
	m_pMap->Update();
	
	// 
	m_pCamera->GetTargetPos(m_pPlayer->SetPos());

	// �G�𐶐�(�f�o�b�O�p)
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_pEnemy->Create();
		m_pEnemy->SetMapChip(m_pMap->GetMapChip());
	}
	// �I�u�W�F�N�g�𐶐�
	if (m_pPlayer->SetMouseLeft())
	{
		m_pObstacle->Create(m_pPlayer->SetPos());
	}

	// ���菈��
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


	// �V�[����؂�ւ��܂�
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

	// BGM���~�܂����������x�Đ�
	SoundFunctions::ReStartBgm(SoundFunctions::SoundIdBattle);

	// �X���C�h���J����
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
