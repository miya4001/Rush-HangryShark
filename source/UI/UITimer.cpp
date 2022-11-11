/*****************************************************************//**
 * @file   UITimer.cpp
 * @brief  UIタイマークラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#include "UITimer.h"
#include "../Application/ApplicationMain.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // タイマー各種定数
  constexpr int TimerSecondsInit = 180;   //!< 初期タイマー秒
  constexpr int FrameCountMax = 60;       //!< フレームカウント上限
  constexpr int SecondsMax = 60;          //!< 秒上限
  constexpr int TenPlace = 10;            //!< 十の位
  constexpr int ColonX = 1700;            //!< コロンx座標
  constexpr int OnePlaceMinutesX = 1630;  //!< 分(一の位)x座標
  constexpr int TenPlaceSecondsX = 1730;  //!< 秒(十の位)x座標
  constexpr int OnePlaceSecondsX = 1800;  //!< 秒(一の位)x座標
  constexpr int DrawY = 25;               //!< 描画y座標
}

namespace Game {
  namespace UI {
    UITimer::UITimer(Application::ApplicationMain& app) : UIBase(app) {
      Init();
    }

    bool UITimer::Init() {
      // 画像ハンドルの設定
      _timerNumber = _app.GetGraphicLoadServer().GetDivGraphicHandles(GraphicKey::TimerNumber);
      _colon = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::TimerColon);
      // 変数初期化
      _timerSeconds = TimerSecondsInit;
      // タイマー秒変換
      TimerConversion();
      return true;
    }

    void UITimer::Process() {
      // タイマー秒が尽きた場合
      if (_timerSeconds <= 0) {
        // ゲームクリア
        _app.SetGameClear(true);
        // ホイッスルSEの再生
        _app.GetSoundComponent().PlayBackGround(SoundKey::Whistle);
        return;
      }
      // フレームカウント増加
      _frameCount = AppFrame::Math::Utility::IncrementCount(_frameCount, FrameCountMax);
      // フレームカウントが上限の場合
      if (_frameCount == 0) {
        // 一秒経過
        OneSecondPass();
        // タイマー秒変換
        TimerConversion();
      }
    }

    void UITimer::Draw() const {
      // コロン描画
      DrawGraph(ColonX, DrawY, _colon, true);
      // タイマー数字描画
      DrawGraph(OnePlaceMinutesX, DrawY, _timerNumber.at(_onePlaceMinutes), true);
      DrawGraph(TenPlaceSecondsX, DrawY, _timerNumber.at(_tenPlaceSeconds), true);
      DrawGraph(OnePlaceSecondsX, DrawY, _timerNumber.at(_onePlaceSeconds), true);
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