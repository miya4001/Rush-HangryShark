/*****************************************************************//**
 * @file   UITimer.cpp
 * @brief  UIタイマークラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#include "UITimer.h"
#include "../Application/ApplicationMain.h"

namespace {
  // タイマー各種定数
  constexpr int TimerSecondsInit = 180;  //!< 初期タイマー秒
  constexpr int FrameCountMax = 60;      //!< フレームカウント上限
  constexpr int SecondsMax = 60;         //!< 秒上限
  constexpr int TenPlace = 10;           //!< 十の位
}

namespace Game {
  namespace UI {
    UITimer::UITimer(Application::ApplicationMain& app) : UIBase(app) {
      Init();
    }

    bool UITimer::Init() {
      // 変数初期化
      _timerSeconds = TimerSecondsInit;
      // タイマー秒変換
      TimerConversion();
      return true;
    }

    void UITimer::Process() {
      // フレームカウントが上限の場合
      if (FrameCountMax <= _frameCount) {
        // フレームカウント初期化
        _frameCount = 0;
        // 一秒経過
        OneSecondPass();
        // タイマー秒変換
        TimerConversion();
        return;
      }
      // フレームカウントを増やす
      ++_frameCount;
    }

    void UITimer::Draw() const {
      // デバッグ情報描画
#ifdef _DEBUG
      // タイマー
      DrawFormatString(1500, 100, GetColor(255, 255, 255), "%d : %d %d", _onePlaceMinutes, _tenPlaceSeconds, _onePlaceSeconds);
#endif
    }

    void UITimer::OneSecondPass() {
      // タイマー秒を減らす
      --_timerSeconds;
    }

    void UITimer::TimerConversion() {
      // 分(一の位)を求める
      _onePlaceMinutes = _timerSeconds / SecondsMax;
      // 秒
      int seconds = _timerSeconds % SecondsMax;
      // 秒(十の位)を求める
      _tenPlaceSeconds = seconds / TenPlace;
      // 秒(一の位)を求める
      _onePlaceSeconds = seconds % TenPlace;
    }
  } // namespace UI
} // namespace Game