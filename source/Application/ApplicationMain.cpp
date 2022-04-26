/*****************************************************************//**
 * @file   ApplicationMain.cpp
 * @brief  アプリケーションメインクラス
 * 
 * @author 宮澤耀生
 * @date   April 2022
 *********************************************************************/
#include "ApplicationMain.h"

namespace Game {
  namespace Application {
    // アプリケーションの実態
    ApplicationMain application;

    ApplicationMain::ApplicationMain() : ApplicationBase() {
      if (IsSetApplication()) {
        // 実態生成
        _application = std::make_shared<ApplicationMain>();
      }
    }

    bool ApplicationMain::Init() {
      if (!ApplicationBase::Init()) {
        return false;  // 初期化失敗
      }
      return true;  // 初期化成功
    }
  } // namespace Application
} // namespace Game