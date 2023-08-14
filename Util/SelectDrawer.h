#pragma once
#include "Vec2.h"
#include <vector>
#include <memory>


namespace
{
	// 猫の手
	constexpr int kCatHandNum = 2;
}


class StringDrawer;

/// 文字を描画させるクラス
class SelectDrawer
{
public:
	SelectDrawer();
	virtual ~SelectDrawer();

	/// <summary>
	/// テキストの数分のTextクラスをインスタンスを作成する
	/// </summary>
	/// <param name="frameX">    枠の位置X  </param>
	/// <param name="frameY">    枠の位置Y  </param>
	/// <param name="stringX">   枠の位置Xからの文字位置  </param>
	/// <param name="stringY">   枠の位置Yからの文字位置  </param>
	/// <param name="text">		 文字  </param>
	/// <param name="color">	 色	   </param>
	/// <param name="size">		 サイズ</param>
	void Add(int frameX, int frameY, int stringX, int stringY, const char* text, int color, int size);

	// メモリ解放
	void End();

	/// パッド入力の更新処理
	void Update();

	// 座標を変更します
	void UpdatePos(int x, int y);

	// 猫の手の位置を変更します
	void UpdateCatHandPos();

	/// テキストを描画する
	void Draw();

	// セレクトナンバーをリセットする
	void ResetSelectNo();

	/// <summary>
	/// 選択した番号
	/// </summary>
	/// <returns>何番目を選択しかたを返す</returns>
	int GetSelectNo();

	/// <summary>
	/// 現在選択中の番号
	/// </summary>
	/// <returns>現在選択中の番号を返す</returns>
	int GetSelectNowNo();

private:
	// テキスト描画用クラス
	std::vector<std::shared_ptr<StringDrawer>> m_pText;
	// 選択したかどうか
	bool m_isSelect;
	// 選択肢の数
	int selectNum;
	int selectNow;
	int m_selectNo;
	// 円の半径
	int selectRad;

	// 猫の手の位置
	int m_catHandPosX[kCatHandNum];
	int m_catHandPosY;
};

class StringDrawer
{
public:
	/// <summary>
	/// テキスト作成
	/// </summary>
	/// <param name="frameX">    枠の位置X  </param>
	/// <param name="frameY">    枠の位置Y  </param>
	/// <param name="stringX">   枠の位置Xからの文字位置  </param>
	/// <param name="stringY">   枠の位置Yからの文字位置  </param>
	/// <param name="text">		 文字  </param>
	/// <param name="color">	 色	   </param>
	/// <param name="size">		 サイズ</param>
	/// <param name="frameHnadle">		 文字枠の画像ハンドル</param>
	StringDrawer(int frameX, int frameY, int stringX, int stringY, const char* text, int color, int size,int frameHnadle,int selectHandle);
	virtual ~StringDrawer();
	void UpdatePos(int x, int y);
	void Draw();

	void SetSelectRadius(int rad);
	void SetBlendMode(int blendLevel);

	int GetFramePosX();
	int GetFramePosY();
private:
	// 位置
	int m_frameX;
	int m_frameY;
	// 位置
	int m_stringX;
	int m_stringY;
	// 元の位置からずらす用
	int m_changePosX;
	int m_changePosY;
	// スライド用変数
	int m_slideY;
	// 文字
	const char* m_text;
	// 色
	int m_color;
	// 枠を表示するかどうか
	bool m_isFrame;
	// 文字データ
	int m_fontHandle;
	// 選択してるかどうか
	bool m_isSelect;
	// 選択後のエフェクト円の大きさ
	int m_rad;
	// ブレンド率
	int m_blend;
	// 選択画像用ハンドル
	int m_hSelectFrame;
};

