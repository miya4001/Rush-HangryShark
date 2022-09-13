/*****************************************************************//**
 * @file   EnemyBase.h
 * @brief  GĖîęNX
 * 
 * @author {āVsķ
 * @date   September 2022
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"
#include "../Collision/CollisionSphere.h"

/**
 * @brief  Q[
 */
namespace Game{
  /**
   * @brief  G
   */
  namespace Enemy {
    namespace AppMath = AppFrame::Math;
    /**
     * @class EnemyBase
     * @brief GĖîęNX
     */
    class EnemyBase : public Object::ObjectBase {
    public:
      /**
       * @brief RXgN^
       * @param app AvP[VĖQÆ
       */
      EnemyBase(Application::ApplicationMain& app);
      /**
       * @brief  úŧ
       * @return true:úŧŽũ
       *         false:úŧļs
       */
      virtual bool Init();
      /**
       * @brief  XV
       */
      virtual void Process();
      /**
       * @brief  `æ
       */
      void Draw() const override;

    protected:
      /**
       * @brief  p[^ĖÝč
       */
      virtual void SetParameters();
      /**
       * @brief  CÍÍOŧč
       * @return true:CÍÍO
       *         false:CÍÍā
       */
      virtual bool IsOverSea();
      /**
       * @brief  ÚŪ
       */
      virtual void Move();
      /**
       * @brief  ÕË
       */
      virtual void Hit();

      //!< ĖÕËŧč
      std::unique_ptr<Collision::CollisionSphere> _sphere;
    };
  } // namespace Enemy
} // namespace Game