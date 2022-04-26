/*****************************************************************//**
 * @file   ApplicationMain.h
 * @brief  アプリケーションメインクラス
 * 
 * @author 宮澤耀生
 * @date   April 2022
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
    /**
     * @class  ApplicationMain
     * @brief  アプリケーションメインクラス
     */
    class ApplicationMain :public AppFrame::Application::ApplicationBase {
    public:
      /**
       * @brief  コンストラクタ
       */
      ApplicationMain();
      /**
       * @brief  アプリケーションの初期化
       * @return true:初期化成功
       *         false:初期化失敗
       */
      bool Init() override;

    private:

    };
  } // namespace Application
} // namespace Game