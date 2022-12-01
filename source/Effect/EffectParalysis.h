/*****************************************************************//**
 * @file   EffectParalysis.h
 * @brief  エフェクト(麻痺)クラス
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
     * @class  EffectParalysis
     * @brief  エフェクト(麻痺)クラス
     */
    class EffectParalysis : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectParalysis(Application::ApplicationMain& app);

    private:
      /**
       * @brief  パラメータの設定
       */
      void SetParameters() override;
    };
  } // namespace Effect
} // namespace Game