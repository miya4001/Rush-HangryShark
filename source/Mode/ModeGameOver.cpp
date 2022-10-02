/*****************************************************************//**
 * @file   ModeGameOver.cpp
 * @brief  モードゲームオーバークラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#include "ModeGameOver.h"
#include "../Application/ApplicationMain.h"
#include "ModeGame.h"

namespace Game {
  namespace Mode {
    ModeGameOver::ModeGameOver(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    bool ModeGameOver::Init() {
      return true;
    }

    void ModeGameOver::Enter() {
      // リソースの読み取り処理
      LoadResource();
    }

    void ModeGameOver::Exit() {
      // 変数初期化
      _decision = false;
    }

    void ModeGameOver::Input(AppFrame::Input::InputManager& input) {
      // XInputジョイパッドの入力処理の取得
      auto xJoypad = input.GetXJoypad();
      // Aボタンが入力された場合
      if (xJoypad.GetButton(XINPUT_BUTTON_A, AppFrame::Input::InputTrigger)) {
        // 選択決定
        _decision = true;
      }
    }

    void ModeGameOver::Process() {
      // 入力
      Input(_app.GetInputManager());
      // モード切り替え
      ChangeMode();
    }

    void ModeGameOver::Draw() const {

    }

    void ModeGameOver::LoadResource() {
      // 読み込み済みの場合中断
      if (_isLoad) {
        return;
      }
      // 読み込み完了
      _isLoad = true;
    }

    void ModeGameOver::ChangeMode() {
      // 選択未決定の場合中断
      if (!_decision) {
        return;
      }
      // モードゲーム遷移
      _app.GetModeServer().TransionToMode(Game);
      // ゲームオーバーフラグ初期化
      _appMain.SetGameOver(false);
    }
  } // namespae Mode
} // namespace Game