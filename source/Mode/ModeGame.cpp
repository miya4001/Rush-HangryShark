/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  モードゲームクラス
 * 
 * @author 宮澤耀生
 * @date   April 2022
 *********************************************************************/
#include "ModeGame.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"

namespace Game {
  namespace Mode {
    ModeGame::ModeGame(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    bool ModeGame::Init() {
      return true;
    }

    void ModeGame::Enter() {

    }

    void ModeGame::Exit() {
      // 生成したオブジェクトを削除
      _appMain.GetObjectServer().Release();
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
      // オブジェクトサーバの更新
      _appMain.GetObjectServer().Process();
    }

    void ModeGame::Draw() const {
      // モードゲーム確認四角形描画
      DrawBox(100, 100, 200, 200, GetColor(255, 0, 0), true);
      // オブジェクトサーバの描画
      _appMain.GetObjectServer().Draw();
    }
  } // namespace Mode
} // namespace Game