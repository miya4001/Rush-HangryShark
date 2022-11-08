/*****************************************************************//**
 * @file   EnemyShrimp.h
 * @brief  敵(エビ)クラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#pragma once
#include "EnemyBase.h"

/**
 * @brief  ゲーム
 */
namespace Game{
  /**
   * @brief  敵
   */
  namespace Enemy {
    /**
     * @class  EnemyShrimp
     * @brief  敵(エビ)クラス
     */
    class EnemyShrimp : public EnemyBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EnemyShrimp(Application::ApplicationMain& app);
      /**
       * @brief  更新
       */
      void Process() override;

    private:
      /**
       * @brief  パラメータの設定
       */
      void SetParameters() override;
      /**
       * @brief  衝突判定の設定
       */
      void SetCollision() override;
      /**
       * @brief  移動
       */
      void Move() override;
    };
  } // namespace Enemy
} // namespace Game