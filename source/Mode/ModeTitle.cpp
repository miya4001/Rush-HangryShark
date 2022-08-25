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

    }

    void ModeTitle::Exit() {

    }

    void ModeTitle::Input(AppFrame::Input::InputManager& input) {
      // XInputジョイパッドの入力処理の取得
      auto xJoypad = input.GetXJoypad();
      // STARTボタンが入力された場合
      if (xJoypad.GetButton(XINPUT_BUTTON_A, AppFrame::Input::InputTrigger)) {
        // モードゲームの登録
        _app.GetModeServer().AddMode(MGame, std::make_shared<Mode::ModeGame>(_appMain));
        // モードゲーム遷移
        _app.GetModeServer().TransionToMode(MGame);
      }
    }

    void ModeTitle::Process() {
      // 入力
      Input(_app.GetInputManager());
    }

    void ModeTitle::Draw() const {
    }
  } // namespace Mode
} // namespace Game