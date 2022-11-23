/*****************************************************************//**
 * @file   EffectBase.h
 * @brief  エフェクトの基底クラス
 * 
 * @author 宮澤耀生
 * @date   November 2022
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
   * @brief  エフェクト
   */
  namespace Effect {
    namespace AppMath = AppFrame::Math;
    /**
     * @class  EffectBase
     * @brief  エフェクトの基底クラス
     */
    class EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectBase(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      virtual ~EffectBase();
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
       * @brief  エフェクト停止
       */
      virtual void DeadEffect();
      /**
       * @brief  エフェクト再生情報の設定
       * @param  position エフェクト再生位置
       * @param  rotation エフェクト再生向き
       */
      virtual void SetTransform(const AppMath::Vector4 position, const AppMath::Vector4 rotation);
      /**
       * @brief  死亡状態かの判定
       * @return true:死亡状態
       *         false:死んでいない
       */
      virtual bool IsDead() {
        return _effectState == EffectState::Dead;
      }

    protected:
      /**
       * @brief  エフェクトの状態の列挙型クラス
       */
      enum class EffectState {
        Active,  //!< 活動状態
        Paused,  //!< 停止状態
        Dead     //!< 死亡状態
      };
      /**
       * @brief  パラメータの設定
       */
      virtual void SetParameters();
      /**
       * @brief  エフェクト再生
       */
      virtual void PlayEffect();
      /**
       * @brief  エフェクト読み込みハンドルの取得
       * @param  key エフェクトハンドルキー
       * @return エフェクト読み込みハンドル
       */
      virtual int GetEffectLoadHandle(const std::string_view key);

      int _loadHandle{ -1 };  //!< エフェクト読み込みハンドル
      int _playHandle{ -1 };  //!< エフェクト再生ハンドル
      //!< アプリケーションの参照
      Application::ApplicationMain& _app;
      //!< エフェクトの状態
      EffectState _effectState{ EffectState::Paused };
      //!< 位置
      AppMath::Vector4 _position;
      //!< 向き
      AppMath::Vector4 _rotation;
    };
  } // namespace Effect
} // namespace Game