/*****************************************************************//**
 * @file   EnemyTuna.h
 * @brief  G(}O)NX
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
     * @class  EnemyTuna
     * @brief  G(}O)NX
     */
    class EnemyTuna : public EnemyBase {
    public:
      /**
       * @brief  RXgN^
       * @param  app AvP[VĖQÆ
       */
      EnemyTuna(Application::ApplicationMain& app);
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
       * @brief  Tõ
       */
      void Search();
      /**
       * @brief  Ķ
       */
      void Escape();

      //!< TõĖÕËŧč
      std::unique_ptr<Collision::CollisionSphere> _search{ nullptr };
    };
  } // namespace Enemy
} // namespace Game