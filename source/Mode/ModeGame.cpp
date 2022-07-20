/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  ���[�h�Q�[���N���X
 * 
 * @author �{�V�s��
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
      // ���������I�u�W�F�N�g���폜
      _appMain.GetObjectServer().Release();
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
      // �I�u�W�F�N�g�T�[�o�̍X�V
      _appMain.GetObjectServer().Process();
    }

    void ModeGame::Draw() const {
      // ���[�h�Q�[���m�F�l�p�`�`��
      DrawBox(100, 100, 200, 200, GetColor(255, 0, 0), true);
      // �I�u�W�F�N�g�T�[�o�̕`��
      _appMain.GetObjectServer().Draw();
    }
  } // namespace Mode
} // namespace Game