/*****************************************************************//**
 * @file   ApplicationMain.cpp
 * @brief  �A�v���P�[�V�������C���N���X
 * 
 * @author �{�V�s��
 * @date   April 2022
 *********************************************************************/
#include "ApplicationMain.h"

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
      return true;  // ����������
    }
  } // namespace Application
} // namespace Game