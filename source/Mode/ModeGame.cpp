/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  ���[�h�Q�[���N���X
 * 
 * @author �{�V�s��
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
      // XInput�W���C�p�b�h�̓��͏����̎擾
      auto joypad = input.GetXJoypad();
      namespace AppInput = AppFrame::Input;
      // START�{�^�������͂��ꂽ�ꍇ
      if (joypad.GetButton(XINPUT_BUTTON_START, AppInput::InputTrigger)) {
        // �A�v���P�[�V�����̏I���v��
        _app.RequestTerminate();
      }
    }

    void ModeGame::Process() {
      // ����
      Input(_app.GetInputManager());
    }

    void ModeGame::Draw() const {

    }
  } // namespace Mode
} // namespace Game