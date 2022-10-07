/*****************************************************************//**
 * @file   UIHungryGauge.h
 * @brief  UI空腹ゲージクラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#pragma once
#include "UIBase.h"

 /**
  * @brief  ゲーム
  */
namespace Game {
  /**
   * @brief  UI
   */
  namespace UI {
    /**
     * @class  UIHungryGauge
     * @brief  UI空腹ゲージクラス
     */
    class UIHungryGauge : public UIBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      UIHungryGauge(Application::ApplicationMain& app);
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
      int _gauge{ -1 };          //!< 空腹ゲージ画像
      int _gaugeBar{ -1 };       //!< 空腹ゲージバー画像
      int _gaugeBarRightX{ 0 };  //!< ゲージバー右下x座標
    };
  } // namespace UI
} // namespace Game