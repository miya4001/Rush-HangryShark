/*****************************************************************//**
 * @file   ModeExplanation.cpp
 * @brief  モード説明クラス
 * 
 * @author 宮澤耀生
 * @date   December 2022
 *********************************************************************/
#include "ModeExplanation.h"
#include "../Application/ApplicationMain.h"
#include "ModeTitle.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // 各種定数
  constexpr int BackX = 1700;    //!< バックx座標
  constexpr int BackY = 1000;    //!< バックy座標
  constexpr int BubbleX = 1600;  //!< 泡x座標
  constexpr int BubbleY = 1000;  //!< 泡y座標
} // namespace

namespace Game {
  namespace Mode {
    ModeExplanation::ModeExplanation(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    void ModeExplanation::Enter() {
      // リソースの読み取り処理
      LoadResource();
      // 画像ハンドルの設定
      _explanation = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Explanation);
      _back = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Back);
      _bubble = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Bubble);
    }

    void ModeExplanation::Exit() {
      // 変数初期化
      _decision = false;
    }

    void ModeExplanation::Input(AppFrame::Input::InputManager& input) {
      // XInputジョイパッドの入力処理の取得
      auto&& xJoypad = input.GetXJoypad();
      // Aボタンが入力された場合
      if (xJoypad.GetButton(XINPUT_BUTTON_A, AppFrame::Input::InputTrigger)) {
        // 選択決定
        _decision = true;
      }
    }

    void ModeExplanation::Process() {
      // 入力
      Input(_app.GetInputManager());
      // モード切り替え
      ChangeMode();
    }

    void ModeExplanation::Draw() const {
      // 画像の描画
      DrawGraph(0, 0, _explanation, true);
      DrawRotaGraph(BackX, BackY, 1.0, 0.0, _back, true);
      DrawRotaGraph(BubbleX, BubbleY, 1.0, 0.0, _bubble, true);
    }

    void ModeExplanation::LoadResource() {
      // 読み込み済みの場合中断
      if (_isLoad) {
        return;
      }
      // 各種画像ハンドルの読み込み
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap{
        {GraphicKey::Explanation, "resource/Graphic/Explanation/Explanation.png"}
      };
      // 画像読み込みサーバに一括読み込み
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      // 読み込み完了
      _isLoad = true;
    }

    void ModeExplanation::ChangeMode() {
      // 選択未決定の場合中断
      if (!_decision) {
        return;
      }
      // モードタイトル遷移
      _app.GetModeServer().TransionToMode(Title);
    }
  } // namespace Mode
} // namespace Game