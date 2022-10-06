/*****************************************************************//**
 * @file   UIBase.h
 * @brief  UIの基底クラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#pragma once

/**
 * @brief  ゲーム
 */
namespace Game{
  /**
   * @brief  アプリケーション
   */
  namespace Application {
    class ApplicationMain;
  } // namespace Application
  /**
   * @brief  UI
   */
  namespace UI {
    /**
     * @class UIBase
     * @brief UIの基底クラス
     */
    class UIBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      UIBase(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      virtual ~UIBase();
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

    protected:
      int _graphicHandle{ -1 };  //!< 画像ハンドル
      //!< アプリケーションの参照
      Application::ApplicationMain& _app;

    };
  } // namespace UI
} // namespace Game