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
     * @class  EnemyBase
     * @brief  GĖîęNX
     */
    class EnemyBase : public Object::ObjectBase {
    public:
      /**
       * @brief  GĖŊĘĖņ^NX
       */
      enum class EnemyID {
        None,      //!< YČĩ
        Shrimp,    //!< Gr
        Tuna,      //!< }O
        Jerryfish  //!< NQ
      };
      /**
       * @brief  GĖóÔĖņ^NX
       */
      enum class EnemyState {
        Idle,    //!< Ō@
        Swim,    //!< Vj
        Escape,  //!< Ķ
        Attack,  //!< U
        Dead     //!< S
      };
      /**
       * @brief  RXgN^
       * @param  app AvP[VĖQÆ
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
      /**
       * @brief  ķŽîņĖÝč
       * @param  position ķŽĀW
       * @param  rotation ķŽüŦ
       */
      virtual void Spawn(const AppMath::Vector4 position, const AppMath::Vector4 rotation);
      /**
       * @brief  GĖSóÔĖÝč
       */
      virtual void SetEnemyDead() {
        _enemyState = EnemyState::Dead;
      }
      /**
       * @brief  HŋlĖæū
       * @return Hŋl
       */
      virtual int GetFoodValue() const {
        return _foodValue;
      }
      /**
       * @brief  GĖŊĘĖæū
       * @return GĖŊĘ
       */
      virtual EnemyID GetEnemyID() const {
        return _enemyID;
      }
      /**
       * @brief  GĖóÔĖæū
       * @return GĖóÔ
       */
      virtual EnemyState GetEnemyState() const {
        return _enemyState;
      }
      /**
       * @brief  ĖÕËŧčĖæū
       * @return ĖÕËŧčĖQÆ
       */
      virtual Collision::CollisionSphere& GetSphere() {
        return *_sphere;
      }

    protected:
      /**
       * @brief  p[^ĖÝč
       */
      virtual void SetParameters();
      /**
       * @brief  ÕËŧčĖÝč
       */
      virtual void SetCollision();
      /**
       * @brief  CÍÍāŧč
       * @return true:CÍÍā
       *         false:CÍÍO
       */
      virtual bool InTheSea();
      /**
       * @brief  ÚŪ
       */
      virtual void Move();
      /**
       * @brief  ÕË
       */
      virtual void Hit();
      /**
       * @brief  S
       */
      virtual void Dead();

      int _foodValue{ 0 };  //!< Hŋl
      //!< GĖŊĘ
      EnemyID _enemyID{ EnemyID::None };
      //!< GĖóÔ
      EnemyState _enemyState{ EnemyState::Idle };
      //!< ĖÕËŧč
      std::unique_ptr<Collision::CollisionSphere> _sphere{ nullptr };
    };
  } // namespace Enemy
} // namespace Game