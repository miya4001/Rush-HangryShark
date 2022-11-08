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
    class EnemyJerryfish : public EnemyBase {
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
       * @brief  充電
       */
      void Charge();
      /**
       * @brief  攻撃
       */
      void Attack();

      int _chargeCount{ 0 };  //!< 充電カウント
      int _attackCount{ 0 };  //!< 攻撃カウント
      //!< 攻撃球の衝突判定
      std::unique_ptr<Collision::CollisionSphere> _attack{ nullptr };
    };
  } // namespace Enemy
} // namespace Game