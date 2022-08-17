/*****************************************************************//**
 * @file   ApplicationMain.cpp
 * @brief  アプリケーションメインクラス
 * 
 * @author 宮澤耀生
 * @date   April 2022
 *********************************************************************/
#include "ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Camera/Camera.h"
#include "../Mode/ModeTitle.h"

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
      // オブジェクトサーバの生成
      _objectServer = std::make_unique<Object::ObjectServer>();
      // カメラの生成
      _camera = std::make_unique<Camera::Camera>();
      // モードタイトルの登録
      _modeServer->AddMode(Mode::MTitle, std::make_unique<Mode::ModeTitle>(*this));
      // モードタイトルの追加
      _modeServer->PushBack(Mode::MTitle);
      return true;  // 初期化成功
    }

    Object::ObjectServer& ApplicationMain::GetObjectServer() {
      return *_objectServer;
    }

    Camera::Camera& ApplicationMain::GetCamera() {
      return *_camera;
    }
  } // namespace Application
} // namespace Game