/*****************************************************************//**
 * @file   SeaSphere.h
 * @brief  CwiNX
 * 
 * @author {āVsķ
 * @date   August 2022
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"
#include "../Collision/CollisionSphere.h"

/**
 * @brief  Q[
 */
namespace Game{
  /**
   * @brief  C
   */
  namespace Sea {
    namespace AppMath = AppFrame::Math;
    /**
     * @class  SeaSphere
     * @brief  CwiNX
     */
    class SeaSphere : public Object::ObjectBase {
    public:
      /**
       * @brief RXgN^
       * @param app AvP[VĖQÆ
       */
      SeaSphere(Application::ApplicationMain& app);
      /**
       * @brief  úŧ
       * @return true:úŧŽũ
       *         false:úŧļs
       */
      bool Init() override;
      /**
       * @brief  XV
       */
      void Process() override;
      /**
       * @brief  ĖÕËŧčĖæū
       * @return ĖÕËŧčĖQÆ
       */
      Collision::CollisionSphere& GetSphere() {
        return *_sphere;
      }

    private:
      /**
       * @brief  p[^ĖÝč
       */
      void SetParameters() override;

      //!< ĖÕËŧč
      std::unique_ptr<Collision::CollisionSphere> _sphere{ nullptr };
    };
  } // namespace Sea
} // namespace Game