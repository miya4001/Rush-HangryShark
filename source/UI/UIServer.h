/*****************************************************************//**
 * @file   UIServer.h
 * @brief  UIを管理するサーバクラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

/**
 * @brief  ゲーム
 */
namespace Game {
  /**
   * @brief  UI
   */
  namespace UI {
    class UIBase;
    /**
     * @class  UIServer
     * @brief  UIを管理するサーバクラス
     */
    class UIServer {
    public:
      /**
       * @brief  コンストラクタ
       */
      UIServer();
      /**
       * @brief  デストラクタ
       */
      ~UIServer();
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
       * @brief  UIを登録
       * @param  ui UIのスマートポインタ
       */
      void RegisterUI(std::shared_ptr<UIBase> ui);

    private:
      //!< UIレジストリ
      std::vector<std::shared_ptr<UIBase>> _uiRegistry;
    };
  } // namespace UI
} // namespace Game