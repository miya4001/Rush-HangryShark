/*****************************************************************//**
 * @file   ObjectBase.h
 * @brief  オブジェクトの基底クラス
 * 
 * @author 宮澤耀生
 * @date   July 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

/**
 * @brief  ゲーム
 */
namespace Game {
  /**
   * @brief  アプリケーション
   */
  namespace Application {
    class ApplicationMain;
  } // namespace Application
  /**
   * @brief  オブジェクト
   */
  namespace Object {
    namespace AppMath = AppFrame::Math;
    /**
     * @class ObjectBase
     * @brief オブジェクトの基底クラス
     */
    class ObjectBase {
    public:
      /**
       * @brief  オブジェクトの識別の列挙型クラス
       */
      enum class ObjectId {
        Object,  //!< オブジェクト
        Player,  //!< プレイヤー
        Enemy,   //!< 敵
        Sea      //!< 海
      };
      /**
       * @brief  オブジェクトの状態の列挙型クラス
       */
      enum class ObjectState {
        Active,  //!< 活動状態
        Pause,   //!< 一時停止状態
        Dead     //!< 死亡状態
      };
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
       */
      ObjectBase(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      virtual ~ObjectBase();
      /**
       * @brief  初期化
       * @return true:初期化成功
       *         false:初期化失敗
       */
      virtual bool Init();
      /**
       * @brief  更新
       */
      virtual void Process();
      /**
       * @brief  描画
       */
      virtual void Draw() const;
      /**
       * @brief  死亡
       */
      virtual void Dead();
      /**
       * @brief  死亡状態かの判定
       * @return true:死亡状態
       *         false:死んでいない
       */
      virtual bool IsDead() const;
      /**
       * @brief  識別の取得
       * @return 識別
       */
      ObjectId GetId() const {
        return _objectId;
      }
      /**
       * @brief  状態の取得
       * @return 状態
       */
      ObjectState GetState() const {
        return _objectState;
      }
      /**
       * @brief  ワールド座標行列の取得
       * @return ワールド座標行列
       */
      AppMath::Matrix44 GetMatrix() const {
        return _world;
      }
      /**
       * @brief  ローカル座標の取得
       * @return ローカル座標
       */
      AppMath::Vector4 GetPosition() const {
        return _position;
      }
      /**
       * @brief  向きの取得
       * @return 向き
       */
      AppMath::Vector4 GetRotation() const {
        return _rotation;
      }

    protected:
      /**
       * @brief  パラメータの設定
       */
      virtual void SetParameters();
      /**
       * @brief  ワールド座標の更新
       */
      void WorldMatrix();

      int _modelHandle{ 0 };  //!< モデルハンドル
      //!< アプリケーションの参照
      Application::ApplicationMain& _app;
      //!< オブジェクトの識別
      ObjectId _objectId{ ObjectId::Object };
      //!< オブジェクトの状態
      ObjectState _objectState{ ObjectState::Active };
      //!< ワールド座標
      AppMath::Matrix44 _world;
      //!< ローカル座標
      AppMath::Vector4 _position;
      //!< 向き
      AppMath::Vector4 _rotation;
      //!< 拡大率
      AppMath::Vector4 _scale;
    };
  } // namespace Object
} // namespace Game