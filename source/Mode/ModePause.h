/*****************************************************************//**
 * @file   ModePause.h
 * @brief  モードポーズクラス
 * 
 * @author 宮澤耀生
 * @date   December 2022
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
    constexpr auto Pause = "ModePause";  //!< モードポーズ登録用キー
    /**
     * @class  ModePause
     * @brief  モードポーズクラス
     */
    class ModePause : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      ModePause(Application::ApplicationMain& app);
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
       * @param  leftX 左スティック左右入力値
       */
      void CursorInput(const int leftX);

      int _pause{ -1 };         //!< ポーズ画像
      int _continue{ -1 };      //!< 続行画像
      int _retire{ -1 };        //!< リタイア画像
      int _bubble{ -1 };        //!< 泡画像
      int _switch{ -1 };        //!< 切り替え画像
      int _bubbleX{ 0 };        //!< 泡x座標
      bool _isStick{ false };   //!< 左スティック入力
      bool _decision{ false };  //!< 選択決定
      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;
    };
  } // namespace Mode
} // namespace Game