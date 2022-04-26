/*****************************************************************//**
 * @file   ApplicationMain.cpp
 * @brief  �A�v���P�[�V�������C���N���X
 * 
 * @author �{�V�s��
 * @date   April 2022
 *********************************************************************/
#include "ApplicationMain.h"
#include "../Mode/ModeGame.h"

namespace Game {
  namespace Application {
    // �A�v���P�[�V�����̎���
    ApplicationMain application;

    ApplicationMain::ApplicationMain() : ApplicationBase() {
      if (IsSetApplication()) {
        // ���Ԑ���
        _application = std::make_shared<ApplicationMain>();
      }
    }

    bool ApplicationMain::Init() {
      if (!ApplicationBase::Init()) {
        return false;  // ���������s
      }
      // ���[�h�Q�[���̓o�^
      _modeServer->AddMode("Game", std::make_unique<Mode::ModeGame>(*this));
      // ���[�h�Q�[���̒ǉ�
      _modeServer->PushBack("Game");
      return true;  // ����������
    }
  } // namespace Application
} // namespace Game