/*****************************************************************//**
 * @file   PlayerShark.h
 * @brief  プレイヤー(サメ)クラス
 * 
 * @author 宮澤耀生
 * @date   July 2022
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"

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
     * @class PlayerShark
     * @brief プレイヤー(サメ)クラス
     */
    class PlayerShark : public Object::ObjectBase {
    public:
      /**
       * @brief  プレイヤーの状態の列挙型クラス
       */
      enum class PlayerState {
        Idle,  //!< 待機
        Swim,  //!< 移動
        Rush,  //!< 突撃
        Eat,   //!< 捕食
      };
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
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

      void Draw() const override;

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
       * @brief  移動
       */
      void Swim();
      /**
       * @brief  接触
       */
      void Hit();
      /**
       * @brief  捕食
       */
      void Eat();
      /**
       * @brief  移動量の算出
       * @return 移動量
       */
      AppMath::Vector4 Move();

      int _hungry{ 0 };         //!< 空腹値
      int _hungryCount{ 0 };    //!< 空腹カウント
      int _eatTime{ 0 };        //!< 捕食時間
      float _speed{ 0.0f };     //!< 移動速度
      bool _isEating{ false };  //!< 捕食中
      //!< 前方向き
      AppMath::Vector4 _forward{ 0.0f, 0.0f, -1.0f };
      //!< プレイヤーの状態
      PlayerState _playerState{ PlayerState::Idle };
      //!< 前フレームのプレイヤーの状態
      PlayerState _oldPlayerState{ PlayerState::Idle };
    };
  } // namespace Player
} // namespace Game