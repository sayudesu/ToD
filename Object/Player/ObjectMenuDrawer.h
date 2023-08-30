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
	int m_CheckSelect;
	// スライドの値
	int m_slierY;
};

