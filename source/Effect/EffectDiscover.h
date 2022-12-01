/*****************************************************************//**
 * @file   EffectDiscover.h
 * @brief  エフェクト(発見)クラス
 * 
 * @author 宮澤耀生
 * @date   December 2022
 *********************************************************************/
#pragma once
#include "EffectBase.h"

/**
 * @brief  ゲーム
 */
namespace Game {
  /**
   * @brief  エフェクト
   */
  namespace Effect {
    /**
     * @class  EffectDiscover
     * @brief  エフェクト(発見)クラス
     */
    class EffectDiscover : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectDiscover(Application::ApplicationMain& app);

    private:
      /**
       * @brief  パラメータの設定
       */
      void SetParameters() override;
    };
  } // namespace Effect
} // namespace Game