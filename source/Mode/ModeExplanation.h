/*****************************************************************//**
 * @file   ModeExplanation.h
 * @brief  モード説明クラス
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
    constexpr auto Explanation = "ModeExplanation";  //!< モード説明登録用キー
    /**
     * @class  ModeExplanation
     * @brief  モード説明クラス
     */
    class ModeExplanation : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      ModeExplanation(Application::ApplicationMain& app);
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

      int _explanation{ -1 };   //!< 説明画像
      int _back{ -1 };          //!< バック画像
      int _bubble{ -1 };        //!< 泡画像
      bool _decision{ false };  //!< 選択決定
      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;
    };
  } // namespace Mode
} // namespace Game