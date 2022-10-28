/*****************************************************************//**
 * @file   PlayerShark.h
 * @brief  プレイヤー(サメ)クラス
 * 
 * @author 宮澤耀生
 * @date   July 2022
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"
#include "../Collision/CollisionSphere.h"

/**
 * @brief  ゲーム
 */
namespace Game {
  /**
   * @brief  プレイヤー
   */
  namespace Player {
    namespace AppMath = AppFrame::Math;
    /**
     * @class  PlayerShark
     * @brief  プレイヤー(サメ)クラス
     */
    class PlayerShark : public Object::ObjectBase {
    public:
      /**
       * @brief  プレイヤーの状態の列挙型クラス
       */
      enum class PlayerState {
        Idle,    //!< 待機
        Swim,    //!< 遊泳
        Rush,    //!< 突撃
        Attack,  //!< 攻撃
        Eat,     //!< 捕食
        Dead     //!< 死亡
      };
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      PlayerShark(Application::ApplicationMain& app);
      /**
       * @brief  初期化
       * @return true:初期化成功
       *         false:初期化失敗
       */
      bool Init() override;
      /**
       * @brief  更新
       */
      void Process() override;
      /**
       * @brief  描画
       */
      void Draw() const override;
      /**
       * @brief  プレイヤー状態の取得
       * @return プレイヤー状態
       */
      PlayerState GetPlayerState() {
        return _playerState;
      }
      /**
       * @brief  本体球の衝突判定の取得
       * @return 本体球の衝突判定の参照
       */
      Collision::CollisionSphere& GetSphere() {
        return *_sphere;
      }
      /**
       * @brief  攻撃球の衝突判定の取得
       * @return 攻撃球の衝突判定の参照
       */
      Collision::CollisionSphere& GetAttack() {
        return *_attack;
      }
      /**
       * @brief  空腹値の取得
       * @return 空腹値
       */
      int GetHungry() {
        return _hungry;
      }

    private:
      /**
       * @brief  パラメータの設定
       */
      void SetParameters() override;
      /**
       * @brief  空腹
       */
      void Hungry();
      /**
       * @brief  遊泳
       */
      void Swim();
      /**
       * @brief  攻撃
       */
      void Attack();
      /**
       * @brief  捕食
       */
      void Eat();
      /**
       * @brief  死亡
       */
      void Dead();
      /**
       * @brief  回転
       */
      void Rotate();
      /**
       * @brief  移動
       */
      void Move();
      /**
       * @brief  攻撃準備
       */
      void AttackReady();
      /**
       * @brief  遊泳アニメーション
       */
      void SwimAnimation();

      int _hungry{ 0 };           //!< 空腹値
      int _hungryCount{ 0 };      //!< 空腹カウント
      int _eatFood{ 0 };          //!< 捕食値
      int _eatTime{ 0 };          //!< 捕食時間
      int _animationCount{ 0 };   //!< アニメカウント
      float _moveSpeed{ 0.0f };   //!< 移動速度
      bool _swimUp{ true };       //!< 遊泳上昇
      //!< プレイヤーの状態
      PlayerState _playerState{ PlayerState::Idle };
      //!< 前方向き
      AppMath::Vector4 _forward{ 0.0f, 0.0f, -1.0f };
      //!< 本体球の衝突判定
      std::unique_ptr<Collision::CollisionSphere> _sphere{ nullptr };
      //!< 攻撃球の衝突判定
      std::unique_ptr<Collision::CollisionSphere> _attack{ nullptr };
    };
  } // namespace Player
} // namespace Game