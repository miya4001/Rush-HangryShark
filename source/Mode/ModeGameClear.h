/*****************************************************************//**
 * @file   ModeGameClear.h
 * @brief  モードゲームクリアクラス
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
    constexpr auto GameClear = "ModeGameClear";  //!< モードゲームクリア登録用キー
    /**
     * @class  ModeGameClear
     * @brief  モードゲームクリアクラス
     */
    class ModeGameClear : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      ModeGameClear(Application::ApplicationMain& app);
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

      int _gameClear{ -1 };     //!< ゲームクリア画像
      int _back{ -1 };          //!< バック画像
      int _bubble{ -1 };        //!< 泡画像
      bool _decision{ false };  //!< 選択決定
      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;
    };
  } // namespae Mode
} // namespace Game