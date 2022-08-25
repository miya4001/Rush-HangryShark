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
      auto xJoypad = input.GetXJoypad();
      // START�{�^�������͂��ꂽ�ꍇ
      if (xJoypad.GetButton(XINPUT_BUTTON_A, AppFrame::Input::InputTrigger)) {
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
    }
  } // namespace Mode
} // namespace Game