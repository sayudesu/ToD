#pragma once

// 起動時の基本設定
namespace Game
{
	// ウインドウモード設定
	constexpr bool kWindowMode = false;
	// ウインドウ名
	const char* const kTitleText = "タワーオブディフェンス";
	// ウインドウサイズ
	constexpr int kScreenWidth = 1920;
	constexpr int kScreenHeight = 1080;
	// カラーモード
	constexpr int kColorDepth = 32;		// 32 or 16
	// ウィンドウのサイズ変更をできるかどうか
	constexpr bool kWindowSizeChange = true;
	// Logを残すかどうか
	constexpr bool kLogText = false;
};