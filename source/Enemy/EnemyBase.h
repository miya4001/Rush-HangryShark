/*****************************************************************//**
 * @file   EnemyBase.h
 * @brief  “G‚ÌŠî’êƒNƒ‰ƒX
 * 
 * @author ‹{àV—s¶
 * @date   September 2022
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"
#include "../Collision/CollisionSphere.h"

/**
 * @brief  ƒQ[ƒ€
 */
namespace Game{
  /**
   * @brief  “G
   */
  namespace Enemy {
    namespace AppMath = AppFrame::Math;
    /**
     * @class  EnemyBase
     * @brief  “G‚ÌŠî’êƒNƒ‰ƒX
     */
    class EnemyBase : public Object::ObjectBase {
    public:
      /**
       * @brief  “G‚Ìó‘Ô‚Ì—ñ‹“Œ^ƒNƒ‰ƒX
       */
      enum class EnemyState {
        Idle,    //!< ‘Ò‹@
        Swim,    //!< —V‰j
        Attack,  //!< UŒ‚
        Dead     //!< €–S
      };
      /**
       * @brief  ƒRƒ“ƒXƒgƒ‰ƒNƒ^
       * @param  app ƒAƒvƒŠƒP[ƒVƒ‡ƒ“‚ÌQÆ
       */
      EnemyBase(Application::ApplicationMain& app);
      /**
       * @brief  ‰Šú‰»
       * @return true:‰Šú‰»¬Œ÷
       *         false:‰Šú‰»¸”s
       */
      virtual bool Init();
      /**
       * @brief  XV
       */
      virtual void Process();
      /**
       * @brief  •`‰æ
       */
      void Draw() const override;
      /**
       * @brief  ¶¬î•ñ‚Ìİ’è
       * @param  position ¶¬À•W
       * @param  rotation ¶¬Œü‚«
       */
      virtual void Spawn(const AppMath::Vector4 position, const AppMath::Vector4 rotation);
      /**
       * @brief  “G‚Ìó‘Ô€–Sİ’è
       */
      virtual void SetEnemyDead() {
        _enemyState = EnemyState::Dead;
      }
      /**
       * @brief  H—¿’l‚Ìæ“¾
       * @return H—¿’l
       */
      virtual int GetFoodValue() const {
        return _foodValue;
      }
      /**
       * @brief  “G‚Ìó‘Ô‚Ìæ“¾
       * @return “G‚Ìó‘Ô
       */
      virtual EnemyState GetEnemyState() const {
        return _enemyState;
      }
      /**
       * @brief  ‹…‚ÌÕ“Ë”»’è‚Ìæ“¾
       * @return ‹…‚ÌÕ“Ë”»’è‚ÌQÆ
       */
      virtual Collision::CollisionSphere& GetSphere() {
        return *_sphere;
      }

    protected:
      /**
       * @brief  ƒpƒ‰ƒ[ƒ^‚Ìİ’è
       */
      virtual void SetParameters();
      /**
       * @brief  ŠC’†”ÍˆÍ“à”»’è
       * @return true:ŠC’†”ÍˆÍ“à
       *         false:ŠC’†”ÍˆÍŠO
       */
      virtual bool InTheSea();
      /**
       * @brief  ˆÚ“®
       */
      virtual void Move();
      /**
       * @brief  Õ“Ë
       */
      virtual void Hit();
      /**
       * @brief  €–S
       */
      virtual void Dead();

      int _foodValue{ 0 };  //!< H—¿’l
      //!< “G‚Ìó‘Ô
      EnemyState _enemyState{ EnemyState::Idle };
      //!< ‹…‚ÌÕ“Ë”»’è
      std::unique_ptr<Collision::CollisionSphere> _sphere{ nullptr };
    };
  } // namespace Enemy
} // namespace Game