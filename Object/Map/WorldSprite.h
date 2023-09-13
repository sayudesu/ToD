// 2023 Takeru Yui All Rights Reserved.
#pragma once
#include <DxLib.h>

/// <summary>
/// 3D座標空間にスプライトを表示する仕組み（ピボットは中心固定、画像のgraphは外で管理）
/// </summary>
class WorldSprite
{
public:
	void Init(int textureGraph, int chipPixelSize, int spriteNo);
	void SetTransform(const VECTOR& pos, float spriteSize);
	void Draw();
	
private:
	int			m_hGraph;	 // スプライトを作成する元テクスチャのグラフィックハンドル
	VECTOR		m_pos;		 // 描画ポジション
	VERTEX3D	m_vertex[4]; // 頂点バッファS
	WORD		m_index [6]; // インデックスバッファ
};

