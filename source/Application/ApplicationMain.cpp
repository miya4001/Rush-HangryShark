/*****************************************************************//**
 * @file   ApplicationMain.cpp
 * @brief  �A�v���P�[�V�������C���N���X
 * 
 * @author �{�V�s��
 * @date   April 2022
 *********************************************************************/
#include "ApplicationMain.h"
#include "../Mode/ModeTitle.h"

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
      // ���[�h�^�C�g���̓o�^
      _modeServer->AddMode(Mode::MTitle, std::make_unique<Mode::ModeTitle>(*this));
      // ���[�h�^�C�g���̒ǉ�
      _modeServer->PushBack(Mode::MTitle);
      return true;  // ����������
    }
  } // namespace Application
} // namespace Game