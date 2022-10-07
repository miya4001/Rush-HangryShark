/*****************************************************************//**
 * @file   EnemyJerryfish.h
 * @brief  敵(クラゲ)クラス
 * 
 * @author 宮澤耀生
 * @date   September 2022
 *********************************************************************/
#pragma once
#include "EnemyBase.h"

/**
 * @brief  ゲーム
 */
namespace Game {
  /**
   * @brief  敵
   */
  namespace Enemy {
    /**
     * @class  EnemyJerryfish
     * @brief  敵(クラゲ)クラス
     */
    class EnemyJerryfish :public EnemyBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EnemyJerryfish(Application::ApplicationMain& app);
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
       * @brief  移動
       */
      void Move() override;
    };
  } // namespace Enemy
} // namespace Game