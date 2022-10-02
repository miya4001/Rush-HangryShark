/*****************************************************************//**
 * @file   ModeGameOver.h
 * @brief  モードゲームオーバークラス
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
   * @brief  アプリケーション
   */
  namespace Application {
    class ApplicationMain;
  } // namespace Application
  /**
   * @brief  モード
   */
  namespace Mode {
    constexpr auto GameOver = "ModeGameOver";  //!< モードタイトル登録用キー
    /**
     * @class  ModeGameOver
     * @brief  モードゲームオーバークラス
     */
    class ModeGameOver : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      ModeGameOver(Application::ApplicationMain& app);
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

      bool _decision{ false };  //!< 選択決定
      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;
    };
  } // namespae Mode
} // namespace Game