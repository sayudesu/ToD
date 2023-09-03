#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include "../../Util/CollDatas.h"

class EnemyBase;
class EnemyManager
{
public:
	EnemyManager();
	virtual ~EnemyManager();

	void Init();
	void End();
	void Create();
	void Update();
	void Draw();
	// �m�[�}���G�l�~�[�̈ʒu
	VECTOR SetNormalPos(int num);
	VECTOR SetNormalPos2(int num);
	int SetNormalNum();

	void SetMapChip(std::vector<int>mapChip);

	// ����p�f�[�^���󂯎��
 	virtual void SetObjCollData(std::vector<CollData> collData);

	// �z��̐�
	int GetNormalNum();

private:
	// �m�[�}���G�l�~�[
	std::vector<std::shared_ptr<EnemyBase>>m_pEnemyNormal;
	std::vector<int>m_mapChip;
	// �o�������J�E���g���܂�
	int m_count;
	// �I�u�W�F�N�g�̐�
	int m_objNum;
};

