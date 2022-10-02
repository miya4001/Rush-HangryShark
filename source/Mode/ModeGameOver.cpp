/*****************************************************************//**
 * @file   ModeGameOver.cpp
 * @brief  ���[�h�Q�[���I�[�o�[�N���X
 * 
 * @author �{�V�s��
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
      // ���\�[�X�̓ǂݎ�菈��
      LoadResource();
    }

    void ModeGameOver::Exit() {
      // �ϐ�������
      _decision = false;
    }

    void ModeGameOver::Input(AppFrame::Input::InputManager& input) {
      // XInput�W���C�p�b�h�̓��͏����̎擾
      auto xJoypad = input.GetXJoypad();
      // A�{�^�������͂��ꂽ�ꍇ
      if (xJoypad.GetButton(XINPUT_BUTTON_A, AppFrame::Input::InputTrigger)) {
        // �I������
        _decision = true;
      }
    }

    void ModeGameOver::Process() {
      // ����
      Input(_app.GetInputManager());
      // ���[�h�؂�ւ�
      ChangeMode();
    }

    void ModeGameOver::Draw() const {

    }

    void ModeGameOver::LoadResource() {
      // �ǂݍ��ݍς݂̏ꍇ���f
      if (_isLoad) {
        return;
      }
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModeGameOver::ChangeMode() {
      // �I�𖢌���̏ꍇ���f
      if (!_decision) {
        return;
      }
      // ���[�h�Q�[���J��
      _app.GetModeServer().TransionToMode(Game);
      // �Q�[���I�[�o�[�t���O������
      _appMain.SetGameOver(false);
    }
  } // namespae Mode
} // namespace Game