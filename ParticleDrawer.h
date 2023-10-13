#pragma once
#include <DxLib.h>
#include <array>

class ParticleDrawer
{
public:
	ParticleDrawer(VECTOR pos);
	virtual ~ParticleDrawer();

	virtual void Init(int no);
	virtual void End();
	virtual void Update();
	virtual void Draw();
	// 画像を消すかどうか
	virtual bool IsGetErase();
private:
	// 始めにどう動くか
	void FirstMove();
	// どこに移動するか
	void Suction();
private:
	// 画像ハンドル
	int m_hGraph;
	// 位置
	VECTOR m_pos;
	// 移動量
	VECTOR m_vec;
	// 速度
	float m_speed;
	// メンバ関数ポインタ
	void(ParticleDrawer::* m_pFunc)();
	// 画像を消すかどうか
	bool m_isErase;

};

