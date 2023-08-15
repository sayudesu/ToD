#include "LoadGraphfunction.h"
#include <vector>
#include <DxLib.h>
#include <cassert>

namespace
{
    // 画像ハンドル
    std::vector<int> graphHandle{};

    // 画像ファイル名
    const char* const kFileName[LoadGraphFunction::GraphIdMaxNum] =
    {
        "Data/Image/SelectVol_B.png",// 猫の画像パス
        "Data/Image/SelectVol_S.png",// すこし特別
        "Data/Image/Wood.png",// 背景画像パス
        "Data/Image/GBar.png",// メーター画像パス   
        "Data/Image/OutSideBar.png",// 外側のメーター画像パス   
        "Data/Image/OutSideBarBg.png",// 外側のメーター画像パス   
        "Data/Image/SelectFrame.png",// 選択用枠
        "Data/Image/nikukyu_S.png",// 選択用肉球
        "Data/Image/Icon0.png",// アイコン
        "Data/Image/Icon1.png",
        "Data/Image/Icon2.png",
        "Data/Image/Icon3.png",
        "Data/Image/Icon4.png",
        "Data/Image/Icon5.png",
        "Data/Image/Icon6.png",
        "Data/Image/Icon7.png",
        "Data/Image/GamePad.png",// ゲームパッド
    };
}

namespace LoadGraphFunction
{
    // 画像をロードします
    void LoadGraphFunction::Load()
    {
        // サウンドデータの読み込み
        for (auto& fileName : kFileName)
        {
            int handle = LoadGraph(fileName);
            assert(handle != -1);
            graphHandle.push_back(handle);
        }
    }

    // メモリ解放
    void LoadGraphFunction::UnLoad()
    {
        // サウンドデータの読み込み
        for (auto& graphData : graphHandle)
        {
            DeleteGraph(graphData);
        }
    }

    // 画像データを渡す
    int LoadGraphFunction::GraphData(GraphId name)
    {
        return graphHandle[name];
    }
}
