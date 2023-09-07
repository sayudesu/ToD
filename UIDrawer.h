#pragma once
class UIDrawer
{
public:
	UIDrawer();
	~UIDrawer();

	void Init();
	void End();
	void Update();
	void Draw();

	// オブジェクトを設置するためのコストを受け取る
	void SetCostSetObject(int cost);

private:
	// 画像ハンドル
	// 自身の体力や設置コスト数の背景
	int m_hBgUtil;
	// オブジェクト設置コストの背景
	int m_hObjectCost;
	// 肉の画像
	int m_hMeat;
	// 必殺技ボタンの説明
	int m_hTopicSpecialAttack;
	int m_hBarTopicSpecialAttack;
	// HPバーの背景
	int m_hBgHp;
	// HPバー
	int m_hHp;


	// 現在のコスト数
	int m_costNum;
};

