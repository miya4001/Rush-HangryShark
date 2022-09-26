/*****************************************************************//**
 * @file   ModeGame.h
 * @brief  モードゲームクラス
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
    constexpr auto MGame = "ModeGame";  //!< モードゲーム登録用キー
    /**
     * @class  ModeGame
     * @brief  モードゲームクラス
     */
    class ModeGame : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
       */
      ModeGame(Application::ApplicationMain& app);
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
       * @brief  生成情報の設定
       */
      void SetSpawn();

      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;
    };
  } // namespace Mode
} // namespace Game