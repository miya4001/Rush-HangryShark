/*****************************************************************//**
 * @file   ModeTitle.cpp
 * @brief  ���[�h�^�C�g���N���X
 * 
 * @author �{�V�s��
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
      // XInput�W���C�p�b�h�̓��͏����̎擾
      auto joypad = input.GetXJoypad();
      namespace AppInput = AppFrame::Input;
      // START�{�^�������͂��ꂽ�ꍇ
      if (joypad.GetButton(XINPUT_BUTTON_A, AppInput::InputTrigger)) {
        // ���[�h�Q�[���̓o�^
        _app.GetModeServer().AddMode(MGame, std::make_shared<Mode::ModeGame>(_appMain));
        // ���[�h�Q�[���J��
        _app.GetModeServer().TransionToMode(MGame);
      }
    }

    void ModeTitle::Process() {
      // ����
      Input(_app.GetInputManager());
    }

    void ModeTitle::Draw() const {
      // ���[�h�^�C�g���m�F�l�p�`�`��
      DrawBox(100, 100, 200, 200, GetColor(0, 255, 0), true);
    }
  } // namespace Mode
} // namespace Game