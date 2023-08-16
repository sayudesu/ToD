#include "MapDrawer.h"
#include <DxLib.h>
#include <cassert>

namespace
{

    const char* kDataPath = "Data/Save/MapData.csv";
}

MapDrawer::MapDrawer():
    m_hBlock(-1),
    m_dataNum(-1)
{

}

MapDrawer::~MapDrawer()
{
}

void MapDrawer::Init()
{
    // csvファイルを読み込んで数字の配列にしたい
    FILE* fp;
    // ファイルがあるかどうか
    bool isFileCheck = true;

    if (fopen_s(&fp, kDataPath, "rt") != 0)
    {
        if (fopen_s(&fp, kDataPath, "rt"))return;
    }

    int chr;
    // 未確定
    int wNum = -1;
    // 横の要素数数える用
    int tempW = 0;

    int tempNum = 0;

    while (true)
    {
        chr = fgetc(fp);    // 1文字読み込み

        // 区切り文字が見つかった
        if (chr == ',' || chr == '\n' || chr == EOF)
        {

            // m_loadDataにデータを入れる
            m_loadData.push_back(tempNum);

            m_dataNum++;
            tempNum = 0;

            // ファイルの終端に来たら終了
            if (chr == EOF)
            {
                break;
            }
            else if (chr == ',')
            {
                tempW++;    // 要素数数える
            }
            else   // chr == '\n'
            {
                tempW++;    // 要素数数える
                if (wNum < 0)
                {
                    wNum = tempW;    // 要素数確定
                }
                /*else
                {
                    assert(wNum == tempW);
                }*/
                tempW = 0;
            }
            // まだ終わってないので続けて読み込み
            continue;
        }

        // データは数字のみのはず
        assert(chr >= '0' && chr <= '9');

        // 数字なのは確定
        // 文字列を数値に変換したい
        // 268を読み込む
        // 1文字目は'2'    これを数値に変換していれる
        // 2文字目は'6'    tempNumは2 20 + 6  tempNum = 26
        // 3文字目は'8' tempNumは26 260+ 8 tempNum = 268
        tempNum = (tempNum * 10) + chr - '0';

        // データの区切りが見つかった時点でそこまでがデータのひとまとまり

    }
    // ファイルを閉じる
    fclose(fp);

    for (int i = 0; i < m_loadData.size(); i++)
    {
        int x = -300;
        int y = 0;
        x += i * 50;
        if (m_loadData[i] == 1)
        {
            m_objPosX.push_back(x);

        }
    }

    // モデルロード
    m_hBlock = MV1LoadModel("Data/Model/NormalBlock2.mv1");
    m_hBlock2 = MV1LoadModel("Data/Model/NormalBlock3.mv1");
}

void MapDrawer::End()
{
}

void MapDrawer::Update()
{
}

void MapDrawer::Draw()
{
    int z = 250;
    int puls = -1;

    for (int i = 0; i < m_loadData.size(); i++)
    {
        // カウント
        puls++;
        // 右に押し詰める
        int x = -600;
        x += (puls * 50);

        // Z軸変更
        if (m_loadData[i] == 0)
        {
            puls = -1;
            z -= 50;
        }
        // 地面ブロック
        if (m_loadData[i] == 1)
        {
            VECTOR pos = VGet(x, -25.0f, z);
            MV1SetPosition(m_hBlock, pos);
            // オブジェクト描画
            MV1DrawModel(m_hBlock);
            continue;
        }
        if (m_loadData[i] == 2)
        {
            VECTOR pos = VGet(x, -25.0f, z);
            MV1SetPosition(m_hBlock2, pos);
            // オブジェクト描画
            MV1DrawModel(m_hBlock2);
            continue;
        }

    }
}

std::vector<int> MapDrawer::GetMapChip()
{
    return m_loadData;
}
