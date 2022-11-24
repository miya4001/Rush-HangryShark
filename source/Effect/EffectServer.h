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
   * @brief  エフェクト
   */
  namespace Effect {
    namespace AppMath = AppFrame::Math;
    class EffectBase;
    /**
     * @class  EffectServer
     * @brief  エフェクトの基底クラス
     */
    class EffectServer {
    public:
      /**
       * @brief  コンストラクタ
       */
      EffectServer();
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

      //!< エフェクトレジストリ
      std::vector<std::shared_ptr<EffectBase>> _effectRegistry;
    };
  } // namespace Effect
  /**
   * @brief  エフェクト番号
   */
  namespace EffectNumber {

  } // namespace EffectNumber
} // namespace Game