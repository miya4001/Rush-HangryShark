/*****************************************************************//**
 * @file   EffectServer.h
 * @brief  エフェクトを管理するサーバクラス
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
    class EffectBase;
    class EffectBlood;
    class EffectParalysis;
    /**
     * @class  EffectServer
     * @brief  エフェクトの基底クラス
     */
    class EffectServer {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectServer(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectServer();
      /**
       * @brief  解放
       */
      void Release();
      /**
       * @brief  更新
       */
      void Process();
      /**
       * @brief  描画
       */
      void Draw() const;
      /**
       * @brief  エフェクトの生成
       * @param  number エフェクト番号
       * @param  position エフェクト再生位置
       * @param  rotation エフェクト再生向き
       */
      void MakeEffect(const int number, const AppMath::Vector4 position, const AppMath::Vector4 rotation);

    private:
      /**
       * @brief  エフェクトの登録
       * @param  effect エフェクトのシェアードポインタ
       */
      void RegisterEffect(std::shared_ptr<EffectBase> effect);
      /**
       * @brief  血の生成
       * @param  position エフェクト再生位置
       * @param  rotation エフェクト再生向き
       * @return 血のシェアードポインタ
       */
      std::shared_ptr<EffectBlood> Blood(const AppMath::Vector4 position, const AppMath::Vector4 rotation);
      /**
       * @brief  麻痺の生成
       * @param  position エフェクト再生位置
       * @param  rotation エフェクト再生向き
       * @return 麻痺のシェアードポインタ
       */
      std::shared_ptr<EffectParalysis> Paralysis(const AppMath::Vector4 position, const AppMath::Vector4 rotation);

      //!< アプリケーションの参照
      Application::ApplicationMain& _app;
      //!< エフェクトレジストリ
      std::vector<std::shared_ptr<EffectBase>> _effectRegistry;
    };
  } // namespace Effect
  /**
   * @brief  エフェクト番号
   */
  namespace EffectNumber {
    constexpr int Blood = 1;      //!< 血
    constexpr int Paralysis = 2;  //!< 麻痺
  } // namespace EffectNumber
} // namespace Game