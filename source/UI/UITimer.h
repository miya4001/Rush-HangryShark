/*****************************************************************//**
 * @file   UITimer.h
 * @brief  UIタイマークラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#pragma once
#include "UIBase.h"
#include <vector>

/**
 * @brief  ゲーム
 */
namespace Game {
  /**
   * @brief  UI
   */
  namespace UI {
    /**
     * @class  UITimer
     * @brief  UIタイマークラス
     */
    class UITimer : public UIBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      UITimer(Application::ApplicationMain& app);
      /**
       * @brief  初期化
       * @return true:初期化成功
       *         false:初期化失敗
       */
      bool Init() override;
      /**
       * @brief  更新
       */
      void Process() override;
      /**
       * @brief  描画
       */
      void Draw() const override;

    private:
      /**
       * @brief  一秒経過
       */
      void OneSecondPass();
      /**
       * @brief  タイマー秒変換
       */
      void TimerConversion();

      int _colon{ -1 };           //!< コロン画像
      int _frameCount{ 0 };       //!< フレームカウント
      int _timerSeconds{ 0 };     //!< タイマー秒
      int _onePlaceSeconds{ 0 };  //!< 秒(一の位)
      int _tenPlaceSeconds{ 0 };  //!< 秒(十の位)
      int _onePlaceMinutes{ 0 };  //!< 分(一の位)
      // タイマー数字画像
      std::vector<int> _timerNumber;
    };
  } // namespace UI
} // namespace Game