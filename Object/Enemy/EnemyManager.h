#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/CollDatas.h"

class EnemyBase;
class EnemyManager
{
public:
	EnemyManager();
	virtual ~EnemyManager();

	virtual void Init();
	virtual void End();
	virtual void Create();
	virtual void Update();
	virtual void Draw();
	virtual void DrawUI();

	// �m�[�}���G�l�~�[�̈ʒu
	virtual VECTOR SetNormalPos(int num);
	// �m�[�}���G�l�~�[�̐���Ԃ��܂�
	virtual int GetNormalNum();
	// �}�b�v�`�b�v�Ńf�[�^���󂯎��܂�
	virtual void SetMapChip(std::vector<int>mapChip);
	// ����p�f�[�^���󂯎��
 	virtual void SetObjCollData(std::vector<CollData> collData);
	// ���g�̔���p�f�[�^
 	virtual std::vector<CollData> GetCollData();
	// �󂯂�_���[�W���󂯎��
	virtual void SetHitDamage(int enemyNo,int damage);
private:
	// �K�v�̂Ȃ��I�u�W�F�N�g���폜����
	virtual void EraseObject();
private:
	// �m�[�}���G�l�~�[
	std::vector<EnemyBase*>m_pEnemyNormal;
	// �}�b�v�`�b�v�̃f�[�^
	std::vector<int>m_mapChip;
};

