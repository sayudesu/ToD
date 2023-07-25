#include <DxLib.h>
#include "SceneMain.h"
#include "SceneTitle.h"
#include "Object/Camera/Camera.h"
#include "Object/Enemy/EnemyManager.h"
#include "Object/Obstacle/ObstacleManager.h"
#include "Object/Player/Player.h"
#include "Object/Map/Map.h"
#include "Util/game.h"
// ���Ƃŏ���
#include "Util/Pad.h"

SceneMain::SceneMain():
	m_pCamera(nullptr),
	m_pEnemy(nullptr),
	m_pObstacle(nullptr),
	m_pPlayer(nullptr),
	m_pMap(nullptr)
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
	m_pMap = new Map;
}

SceneMain::~SceneMain()
{
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
}

void SceneMain::Init()
{
	// 3D�֘A�̐ݒ�
	// Z�o�b�t�@���g�p����
	SetUseZBuffer3D(true);
	// Z�o�b�t�@�ւ̏������݂��s��
	SetWriteZBuffer3D(true);
	// �|���S���̗��ʂ�`�悵�Ȃ�
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
	// �v���C���[����
	m_pPlayer->Update();
	// �v���C���[�̐ݒu����I�u�W�F�N�g
	m_pObstacle->Update();
	// �J����
	m_pCamera->Update();
	m_pCamera->GetMouseScreenPos(m_pPlayer->SetMouseScreenPos());
	m_pCamera->GetMouseWorldPos(m_pPlayer->SetMouseWorldPos());
	// �G
	m_pEnemy->Update();
	// �}�b�v
	m_pMap->Update();
	
	// �G�𐶐�(�f�o�b�O�p)
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_pEnemy->Create(1);
	}
	// �I�u�W�F�N�g�𐶐�
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

	// �X���C�h���J����
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

