/*****************************************************************//**
 * @file   ModeTitle.cpp
 * @brief  モードタイトルクラス
 * 
 * @author 宮澤耀生
 * @date   April 2022
 *********************************************************************/
#include "ModeTitle.h"
#include "../Application/ApplicationMain.h"
#include "ModeGame.h"

namespace Game {
  namespace Mode {
    ModeTitle::ModeTitle(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    bool ModeTitle::Init() {
      return true;
    }

    void ModeTitle::Enter() {
      // リソースの読み取り処理
      LoadResource();
    }

    void ModeTitle::Exit() {
      // 変数初期化
      _decision = false;
    }

    void ModeTitle::Input(AppFrame::Input::InputManager& input) {
      // XInputジョイパッドの入力処理の取得
      auto xJoypad = input.GetXJoypad();
      // Aボタンが入力された場合
      if (xJoypad.GetButton(XINPUT_BUTTON_A, AppFrame::Input::InputTrigger)) {
        // 選択決定
        _decision = true;
      }
    }

    void ModeTitle::Process() {
      // 入力
      Input(_app.GetInputManager());
      // モード切り替え
      ChangeMode();
    }

    void ModeTitle::Draw() const {

    }

    void ModeTitle::LoadResource() {
      // 読み込み済みの場合中断
      if (_isLoad) {
        return;
      }
      // 読み込み完了
      _isLoad = true;
    }

    void ModeTitle::ChangeMode() {
      // 選択未決定の場合中断
      if (!_decision) {
        return;
      }
      // モードゲームの登録
      _app.GetModeServer().AddMode(Game, std::make_shared<Mode::ModeGame>(_appMain));
      // モードゲーム遷移
      _app.GetModeServer().TransionToMode(Game);
    }
  } // namespace Mode
} // namespace Game