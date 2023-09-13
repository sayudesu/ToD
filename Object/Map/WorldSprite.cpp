#include "WorldSprite.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="textureGraph">テクスチャの画像ハンドル</param>
/// <param name="chipPixelSize">スプライトの１チップのピクセルサイズ</param>
/// <param name="spriteNo">スプライト番号</param>
void WorldSprite::Init(int textureGraph, int chipPixelSize, int spriteNo)
{
	this->m_hGraph = textureGraph;

    // NOTE:初期化時に固定しているが、変更したければ自分で関数を追加する必要がある
    // ４頂点分のuvデータを設定
    int texW, texH;
    GetGraphTextureSize(textureGraph, &texW, &texH);
    const int chipNum = texW / chipPixelSize;
    const int chipNoX = spriteNo % chipNum;
    const int chipNoY = spriteNo / chipNum;
    // テクスチャ全部を1.0とした時のcihp一個に対するuvのサイズ
    const float oneChipUVRate = 1.0f / static_cast<float>(chipNum);   
    m_vertex[0].u = (chipNoX + 0.0f) * oneChipUVRate;
    m_vertex[0].v = (chipNoY + 0.0f) * oneChipUVRate;
    m_vertex[1].u = (chipNoX + 1.0f) * oneChipUVRate;
    m_vertex[1].v = (chipNoY + 0.0f) * oneChipUVRate;
    m_vertex[2].u = (chipNoX + 0.0f) * oneChipUVRate;
    m_vertex[2].v = (chipNoY + 1.0f) * oneChipUVRate;
    m_vertex[3].u = (chipNoX + 1.0f) * oneChipUVRate;
    m_vertex[3].v = (chipNoY + 1.0f) * oneChipUVRate;

    // ディフューズ、スペキュラは初期化時に固定
    for (int i = 0; i < 4; i++)
    {
        m_vertex[i].dif = GetColorU8(255, 255, 255, 255);
        m_vertex[i].spc = GetColorU8(0, 0, 0, 0);
        // 回転をサポートしないのでノーマルも固定
        m_vertex[i].norm = VGet(0.0f, 0.0f, -1.0f);   

        // 補助テクスチャをサポートしないのでuv固定
        m_vertex[i].su = 0.0f;
        m_vertex[i].sv = 0.0f;
    }

    // ２ポリゴン分のインデックスデータをセット
    m_index[0] = 0;
    m_index[1] = 1;
    m_index[2] = 2;
    m_index[3] = 3;
    m_index[4] = 2;
    m_index[5] = 1;
}

/// <summary>
/// サイズとポジションに応じて４頂点分の頂点位置を調整
/// </summary>
/// <param name="pos">ポジション</param>
/// <param name="chipSize">配置するワールドスプライトのサイズ</param>
void WorldSprite::SetTransform(const VECTOR& pos, float spriteSize)
{
    // ピボット中心で設定
    // 左上
    m_vertex[0].pos = VScale(VGet(-1.0f, 0.0f, 1.0f), spriteSize * 0.5f);
    // 右上
    m_vertex[1].pos = VScale(VGet(1.0f,  0.0f, 1.0f), spriteSize * 0.5f);
    // 左下
    m_vertex[2].pos = VScale(VGet(-1.0,  0.0f, -1.0f), spriteSize * 0.5f);
    // 右下
    m_vertex[3].pos = VScale(VGet(1.0f,  0.0f, -1.0f), spriteSize * 0.5f);

    // 座標を中心にする
    for (int i = 0; i < 4; i++)
    {
        m_vertex[i].pos = VAdd(m_vertex[i].pos, pos);
    }
}

// 描画
void WorldSprite::Draw()
{
    // ２ポリゴンの描画
    DrawPolygonIndexed3D(m_vertex, 4, m_index, 2, m_hGraph, true);
}