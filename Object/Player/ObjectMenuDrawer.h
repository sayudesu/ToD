#pragma once
class ObjectMenuDrawer
{
public:
	ObjectMenuDrawer();
	~ObjectMenuDrawer();
	
	void Init();
	void End();
	void Update();
	void Draw();

	// メニューを開いているかどうか
	bool IsSetMenu();
	// 選択し決定した番号を返す
	int SelectNo();
	// 選択した番号をリセットする
	void ResetSelectNo();
private:
	// オブジェクトメニュー画像ハンドル
	int m_hObjMenuFrame;
	// オブジェクト画像
	int m_hObject[3];
	// オブジェクトサイズ
	float m_hObjectSize[3];
	// メニューを開いているかどうか
	bool m_isMenu;
	// メニュー選択用
	int m_select;
	int m_checkSelect;
	// スライドの値
	int m_slierY;
};

