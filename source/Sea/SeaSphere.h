/*****************************************************************//**
 * @file   SeaSphere.h
 * @brief  海中背景クラス
 * 
 * @author 宮澤耀生
 * @date   August 2022
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"

/**
 * @brief  ゲーム
 */
namespace Game{
  /**
   * @brief  海
   */
  namespace Sea {
    namespace AppMath = AppFrame::Math;
    /**
     * @class SeaSphere
     * @brief 海中背景クラス
     */
    class SeaSphere : public Object::ObjectBase {
    public:
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
       */
      SeaSphere(Application::ApplicationMain& app);
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

    private:
      /**
       * @brief  パラメータの設定
       */
      void SetParameters() override;
    };
  } // namespace Sea
} // namespace Game