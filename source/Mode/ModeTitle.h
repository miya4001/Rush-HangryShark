/*****************************************************************//**
 * @file   ModeTitle.h
 * @brief  モードタイトルクラス
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
    class ApplicationMain;
  } // namespace Application
  /**
   * @brief  モード
   */
  namespace Mode {
    constexpr auto Title = "ModeTitle";  //!< モードタイトル登録用キー
    /**
     * @class  ModeTitle
     * @brief  モードタイトルクラス
     */
    class ModeTitle : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      ModeTitle(Application::ApplicationMain& app);
      /**
       * @brief  初期化
       * @return true:初期化成功
       *         false:初期化失敗
       */
      bool Init() override;
      /**
       * @brief  モード開始
       */
      void Enter() override;
      /**
       * @brief  モード終了
       */
      void Exit() override;
      /**
       * @brief  入力
       * @param  input インプットマネージャーの参照
       */
      void Input(AppFrame::Input::InputManager& input) override;
      /**
       * @brief  更新
       */
      void Process() override;
      /**
       * @brief  描画
       */
      void Draw() const override;

    private:
      /**
       * @brief  リソース読み込み
       */
      void LoadResource() override;
      /**
       * @brief  モード切り替え
       */
      void ChangeMode() override;
      /**
       * @brief  カーソル入力
       * @param  leftY 左スティック上下入力値
       */
      void CursorInput(const int leftY);
      /**
       * @brief  モードゲーム遷移
       */
      void ToModeGame();

      int _sea{ -1 };           //!< 海中画像
      int _title{ -1 };         //!< タイトル画像
      int _start{ -1 };         //!< 開始画像
      int _explain{ -1 };       //!< 説明画像
      int _quit{ -1 };          //!< 終了画像
      int _bubble{ -1 };        //!< 泡画像
      int _cursor{ 0 };         //!< カーソル
      int _switch{ -1 };        //!< 切り替え画像
      int _bubbleY{ 0 };        //!< 泡y座標
      bool _isStick{ false };   //!< 左スティック入力
      bool _decision{ false };  //!< 選択決定
      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;
    };
  } // namespace Mode
} // namespace Game