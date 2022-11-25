/*****************************************************************//**
 * @file   EffectBlood.h
 * @brief  エフェクト(血)クラス
 * 
 * @author 宮澤耀生
 * @date   November 2022
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
     * @class  EffectBase
     * @brief  エフェクト(血)クラス
     */
    class EffectBlood : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectBlood(Application::ApplicationMain& app);

    private:
      /**
       * @brief  パラメータの設定
       */
      void SetParameters() override;
    };
  } // namespace Effect
} // namespace Game