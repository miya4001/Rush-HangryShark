/*****************************************************************//**
 * @file   EnemyJerryfish.h
 * @brief  G(NQ)NX
 * 
 * @author {āVsķ
 * @date   September 2022
 *********************************************************************/
#pragma once
#include "EnemyBase.h"

/**
 * @brief  Q[
 */
namespace Game {
  /**
   * @brief  G
   */
  namespace Enemy {
    /**
     * @class  EnemyJerryfish
     * @brief  G(NQ)NX
     */
    class EnemyJerryfish : public EnemyBase {
    public:
      /**
       * @brief  RXgN^
       * @param  app AvP[VĖQÆ
       */
      EnemyJerryfish(Application::ApplicationMain& app);
      /**
       * @brief  XV
       */
      void Process() override;
      /**
       * @brief  `æ
       */
      void Draw() const override;

    private:
      /**
       * @brief  p[^ĖÝč
       */
      void SetParameters() override;
      /**
       * @brief  ÕËŧčĖÝč
       */
      void SetCollision() override;
      /**
       * @brief  ÚŪ
       */
      void Move() override;
      /**
       * @brief  [d
       */
      void Charge();
      /**
       * @brief  U
       */
      void Attack();

      int _chargeCount{ 0 };    //!< [dJEg
      int _attackCount{ 0 };    //!< UJEg
      bool _isAttack{ false };  //!< UŽũ
      //!< UĖÕËŧč
      std::unique_ptr<Collision::CollisionSphere> _attack{ nullptr };
    };
  } // namespace Enemy
} // namespace Game