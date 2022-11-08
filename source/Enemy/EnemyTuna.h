/*****************************************************************//**
 * @file   EnemyTuna.h
 * @brief  敵(マグロ)クラス
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
     * @class  EnemyTuna
     * @brief  敵(マグロ)クラス
     */
    class EnemyTuna : public EnemyBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EnemyTuna(Application::ApplicationMain& app);
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
      /**
       * @brief  探索
       */
      void Search();
      /**
       * @brief  逃走
       */
      void Escape();

      //!< 探索球の衝突判定
      std::unique_ptr<Collision::CollisionSphere> _search{ nullptr };
    };
  } // namespace Enemy
} // namespace Game