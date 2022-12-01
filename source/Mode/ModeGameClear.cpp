/*****************************************************************//**
 * @file   ModeGameClear.cpp
 * @brief  モードゲームクリアクラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#include "ModeGameClear.h"
#include "../Application/ApplicationMain.h"
#include "ModeTitle.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // 各種定数
  constexpr int BackX = 960;    //!< バックx座標
  constexpr int BackY = 750;    //!< バックy座標
  constexpr int BubbleX = 860;  //!< 泡x座標
  constexpr int BubbleY = 750;  //!< 泡y座標
} // namespace

namespace Game {
  namespace Mode {
    ModeGameClear::ModeGameClear(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    bool ModeGameClear::Init() {
      return true;
    }

    void ModeGameClear::Enter() {
      // リソースの読み取り処理
      LoadResource();
      // 画像ハンドルの設定
      _gameClear = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::GameClear);
      _back = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Back);
      _bubble = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Bubble);
    }

    void ModeGameClear::Exit() {
      // 変数初期化
      _decision = false;
      // ゲームクリアフラグ初期化
      _appMain.SetGameClear(false);
    }

    void ModeGameClear::Input(AppFrame::Input::InputManager& input) {
      // XInputジョイパッドの入力処理の取得
      auto&& xJoypad = input.GetXJoypad();
      // Aボタンが入力された場合
      if (xJoypad.GetButton(XINPUT_BUTTON_A, AppFrame::Input::InputTrigger)) {
        // 選択決定
        _decision = true;
      }
    }

    void ModeGameClear::Process() {
      // 入力
      Input(_app.GetInputManager());
      // モード切り替え
      ChangeMode();
    }

    void ModeGameClear::Draw() const {
      // 画像の描画
      DrawGraph(0, 0, _gameClear, true);
      DrawRotaGraph(BackX, BackY, 1.0, 0.0, _back, true);
      DrawRotaGraph(BubbleX, BubbleY, 1.0, 0.0, _bubble, true);
    }

    void ModeGameClear::LoadResource() {
      // 読み込み済みの場合中断
      if (_isLoad) {
        return;
      }
      // 各種画像ハンドルの読み込み
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap{
        {GraphicKey::GameClear, "resource/Graphic/GameClear/GameClear.png"}
      };
      // 画像読み込みサーバに一括読み込み
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      // 読み込み完了
      _isLoad = true;
    }

    void ModeGameClear::ChangeMode() {
      // 選択未決定の場合中断
      if (!_decision) {
        return;
      }
      // モードタイトル遷移
      _app.GetModeServer().TransionToMode(Title);
    }
  } // namespae Mode
} // namespace Game