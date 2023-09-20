#include "MapDrawer.h"
#include <DxLib.h>
#include <cassert>
#include "WorldSprite.h"

namespace
{
#if false
    const char* kDataPath = "Data/Save/T_MapData.csv";
#else
    const char* kDataPath = "Data/Save/MapData.csv";
#endif
    // マップチップサイズ
    constexpr int kMapChipMaxZ = 50;// 行
    constexpr int kMapChipMaxX = 25;// 列
    // マップチップナンバー(敵の道)
    constexpr int kEnemyRoad = 2;
    // ブロック1つの大きさ
    constexpr float kBlockSize = 50.0f;
    // マップチップ画像サイズ
    constexpr float kMapCihpSize = 32.0f;
}

MapDrawer::MapDrawer():
    m_hBlock(-1),
    m_hEnemyRoad(-1),
    m_hEnemySpawner(-1),
    m_hEnemyStop(-1),
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

    //// モデルロード
    //m_hBlock        = MV1LoadModel("Data/Model/NormalBlock2.mv1");
    //m_hEnemyRoad    = MV1LoadModel("Data/Model/EnemyRoad.mv1");
    //m_hEnemySpawner = MV1LoadModel("Data/Model/EnemySpawner.mv1");
    //m_hEnemyStop    = MV1LoadModel("Data/Model/EnemyStop.mv1");


    int gprah = LoadGraph("mapData.png");
    m_dataNum = -1;
    // WorldSprite実体設定と位置初期化
    // マップの描画開始位置（左上）
    // 行
    VECTOR chipLeftTopPos = VGet(0, 0, kMapChipMaxZ * 50.0f);

    for (int z = 0; z < kMapChipMaxZ; ++z)
    {
        // 列
        for (int x = 0; x < kMapChipMaxX; ++x)
        {
            m_dataNum++;
            // インスタンス生成
            m_pSprite.push_back(new WorldSprite());
            m_pSprite[m_dataNum]->Init(gprah, kMapCihpSize, m_loadData[m_dataNum]);
            // マップチップの半分サイズ左下にずらすオフセット
           // VECTOR chipHalfOffset = VGet(-kBlockSize * 0.5f, 0, -kBlockSize * 0.5f);
            // 真ん中ピボットなのでマップチップ半分サイズずらす+地面なので一つ下に
            VECTOR chipPos = VAdd(VGet(x * kBlockSize, 0, (-z - 1) * kBlockSize), VGet(0,0,0));
            chipPos = VAdd(chipPos, chipLeftTopPos);
            // 位置を設定
            m_pSprite[m_dataNum]->SetTransform(chipPos, kBlockSize);
        }
    }
    m_data.chipMaxX = kMapChipMaxX;
    m_data.chipMaxZ = kMapChipMaxZ;
    m_data.chipSizeX = kMapCihpSize;
    m_data.chipSizeZ = kMapCihpSize;
    m_data.road         = 1;
    m_data.enemyRoad    = 2;
    m_data.enemySpawner = 3;
    m_data.enemyStop    = 4;
    m_data.blockSizeY = kBlockSize;
    m_data.blockSizeZ = kBlockSize;
    m_data.data = m_loadData;
}

void MapDrawer::End()
{
    for (int i = 0; i < m_pSprite.size(); i++)
    {
        delete m_pSprite[i];
        m_pSprite[i] = nullptr;
    }
    m_pSprite.clear();
}

void MapDrawer::Draw()
{
    for(auto& sprite : m_pSprite)
    {
       sprite->Draw();
    }
}

// データ保管
MapDatas MapDrawer::GetChip()
{
    return m_data;
}