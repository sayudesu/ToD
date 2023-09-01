#pragma once
#include <DxLib.h>
// 一時停止用ベースクラス
class PauseBase
{
public:
	PauseBase() {};
	virtual~PauseBase() {};

	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void UpdateStart() = 0;
	virtual void UpdateMain() = 0;
	virtual void UpdateEnd() = 0;
protected:
	// メンバ関数ポインタ
	void (PauseBase::* m_updateFunc)();
};

