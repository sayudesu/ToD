#pragma once
#include "SceneBase.h"
#include <vector>
#include "../Util/ObjectData.h"

class Camera;
class EnemyManager;
class ObstacleManager;
class Player;
class MapDrawer;
class Collision3D;
class CutInDrawer;
class UIDrawer;
class ParticleDrawer;
class BloodDrawer;

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void End();

	SceneBase* Update();
	void Draw();
private:
	// 判定をチェックします
	void CheckColl();
private:
	Camera*          m_pCamera;
	EnemyManager*    m_pEnemy;
	ObstacleManager* m_pObstacle;
	Player*          m_pPlayer;
	MapDrawer*		 m_pMap;
	Collision3D*	 m_pColl;
	CutInDrawer*     m_catIn;
	UIDrawer*		 m_pUI;


	std::vector<ParticleDrawer*>  m_pParticle;
	std::vector<BloodDrawer*>     m_pBlood;

	// 削除用の判定データ
	std::vector<ObjectData>m_eraseCollShotData;


	// デバッグ
	bool isTitle = false;
	bool isEnd = false;
	bool isC = false;
};