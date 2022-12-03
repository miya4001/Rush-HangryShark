/*****************************************************************//**
 * @file   ModeGame.h
 * @brief  モードゲームクラス
 * 
 * @author 宮澤耀生
 * @date   April 2022
 *********************************************************************/
#pragma once
#include <appframe.h>
#include "../Spawn/SpawnComponent.h"
#include "../UI/UIServer.h"

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
    constexpr auto Game = "ModeGame";  //!< モードゲーム登録用キー
    /**
     * @class  ModeGame
     * @brief  モードゲームクラス
     */
    class ModeGame : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
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
       * @brief  モード切り替え
       */
      void ChangeMode() override;
      /**
       * @brief  UIの設定
       */
      void SetUI();
      /**
       * @brief  モードポーズ遷移
       */
      void ToModePause();
      /**
       * @brief  モードゲームオーバー遷移
       */
      void ToModeGameOver();
      /**
       * @brief  モードゲームクリア遷移
       */
      void ToModeGameClear();

      bool _isPause{ false };  //!< ポーズフラグ
      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;
      //!< 生成コンポーネント
      std::unique_ptr<Spawn::SpawnComponent> _spawn{ nullptr };
      //!< UIサーバ
      std::unique_ptr<UI::UIServer> _uiServer{ nullptr };
    };
  } // namespace Mode
} // namespace Game