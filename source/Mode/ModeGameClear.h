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
      /**
       * @brief  敵数の設定
       */
      void SetEnemyNumbers();

      int _gameClear{ -1 };     //!< ゲームクリア画像
      int _shrimp{ -1 };        //!< エビ数画像
      int _tuna{ -1 };          //!< マグロ数画像
      int _jerryfish{ -1 };     //!< クラゲ数画像
      int _back{ -1 };          //!< バック画像
      int _bubble{ -1 };        //!< 泡画像
      int _shrimpTen{ 0 };      //!< エビ数(十の位)
      int _shrimpOne{ 0 };      //!< エビ数(一の位)
      int _tunaTen{ 0 };        //!< マグロ数(十の位)
      int _tunaOne{ 0 };        //!< マグロ数(一の位)
      int _jerryfishTen{ 0 };   //!< クラゲ数(十の位)
      int _jerryfishOne{ 0 };   //!< クラゲ数(一の位)
      bool _decision{ false };  //!< 選択決定
      // 数字画像
      std::vector<int> _number;
      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;
    };
  } // namespae Mode
} // namespace Game