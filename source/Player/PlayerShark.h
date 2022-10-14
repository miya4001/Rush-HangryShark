/*****************************************************************//**
 * @file   PlayerShark.h
 * @brief  vC[(T)NX
 * 
 * @author {āVsķ
 * @date   July 2022
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"
#include "../Collision/CollisionSphere.h"

/**
 * @brief  Q[
 */
namespace Game {
  /**
   * @brief  vC[
   */
  namespace Player {
    namespace AppMath = AppFrame::Math;
    /**
     * @class  PlayerShark
     * @brief  vC[(T)NX
     */
    class PlayerShark : public Object::ObjectBase {
    public:
      /**
       * @brief  vC[ĖóÔĖņ^NX
       */
      enum class PlayerState {
        Idle,    //!< Ō@
        Swim,    //!< Vj
        Rush,    //!< Ë
        Attack,  //!< U
        Eat,     //!< ßH
        Dead     //!< S
      };
      /**
       * @brief  RXgN^
       * @param  app AvP[VĖQÆ
       */
      PlayerShark(Application::ApplicationMain& app);
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
       * @brief  `æ
       */
      void Draw() const override;
      /**
       * @brief  vC[óÔĖæū
       * @return vC[óÔ
       */
      PlayerState GetPlayerState() {
        return _playerState;
      }
      /**
       * @brief  {ĖĖÕËŧčĖæū
       * @return {ĖĖÕËŧčĖQÆ
       */
      Collision::CollisionSphere& GetSphere() {
        return *_sphere;
      }
      /**
       * @brief  UĖÕËŧčĖæū
       * @return UĖÕËŧčĖQÆ
       */
      Collision::CollisionSphere& GetAttack() {
        return *_attack;
      }
      /**
       * @brief  ó lĖæū
       * @return ó l
       */
      int GetHungry() {
        return _hungry;
      }

    private:
      /**
       * @brief  p[^ĖÝč
       */
      void SetParameters() override;
      /**
       * @brief  ó 
       */
      void Hungry();
      /**
       * @brief  Vj
       */
      void Swim();
      /**
       * @brief  U
       */
      void Attack();
      /**
       * @brief  ßH
       */
      void Eat();
      /**
       * @brief  S
       */
      void Dead();
      /**
       * @brief  ņ]
       */
      void Rotate();
      /**
       * @brief  ÚŪ
       */
      void Move();
      /**
       * @brief  Uõ
       */
      void AttackReady();

      int _hungry{ 0 };       //!< ó l
      int _hungryCount{ 0 };  //!< ó JEg
      int _eatTime{ 0 };      //!< ßHÔ
      float _speed{ 0.0f };   //!< ÚŪŽx
      //!< vC[ĖóÔ
      PlayerState _playerState{ PlayerState::Idle };
      //!< OûüŦ
      AppMath::Vector4 _forward{ 0.0f, 0.0f, -1.0f };
      //!< {ĖĖÕËŧč
      std::unique_ptr<Collision::CollisionSphere> _sphere{ nullptr };
      //!< UĖÕËŧč
      std::unique_ptr<Collision::CollisionSphere> _attack{ nullptr };
    };
  } // namespace Player
} // namespace Game