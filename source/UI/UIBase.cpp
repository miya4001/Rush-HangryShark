/*****************************************************************//**
 * @file   UIBase.cpp
 * @brief  UI�̊��N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#include "UIBase.h"

namespace Game {
  namespace UI {
    UIBase::UIBase(Application::ApplicationMain& app) : _app(app) {

    }

    UIBase::~UIBase() {

    }

    bool UIBase::Init() {
      return true;
    }

    void UIBase::Process() {

    }

    void UIBase::Draw() const {

    }
  } // namespace UI
} // namespace Game