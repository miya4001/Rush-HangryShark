/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  モードゲームクラス
 * 
 * @author 宮澤耀生
 * @date   April 2022
 *********************************************************************/
#include "ModeGame.h"
#include "../Application/ApplicationMain.h"

namespace Game {
  namespace Mode {
    ModeGame::ModeGame(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    ModeGame::~ModeGame() {

    }

    bool ModeGame::Init() {
      return true;
    }

    void ModeGame::Enter() {

    }

    void ModeGame::Exit() {

    }

    void ModeGame::Input(AppFrame::Input::InputManager& input) {
      // XInputジョイパッドの入力処理の取得
      auto joypad = input.GetXJoypad();
      namespace AppInput = AppFrame::Input;
      // STARTボタンが入力された場合
      if (joypad.GetButton(XINPUT_BUTTON_START, AppInput::InputTrigger)) {
        // アプリケーションの終了要請
        _app.RequestTerminate();
      }
    }

    void ModeGame::Process() {
      // 入力
      Input(_app.GetInputManager());
    }

    void ModeGame::Draw() const {

    }
  } // namespace Mode
} // namespace Game