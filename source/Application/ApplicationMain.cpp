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
#include "../Spawn/SpawnServer.h"
#include "../Effect/EffectServer.h"
#include "../Mode/ModeAMG.h"

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
      // 生成サーバの生成
      _spawnServer = std::make_unique<Spawn::SpawnServer>(*this);
      // エフェクトサーバの生成
      _effectServer = std::make_unique<Effect::EffectServer>(*this);
      // モードAMGの登録
      _modeServer->AddMode(Mode::AMG, std::make_unique<Mode::ModeAMG>(*this));
      // モードAMGの追加
      _modeServer->PushBack(Mode::AMG);
      return true;  // 初期化成功
    }

    Object::ObjectServer& ApplicationMain::GetObjectServer() {
      return *_objectServer;
    }

    Camera::Camera& ApplicationMain::GetCamera() {
      return *_camera;
    }

    Spawn::SpawnServer& ApplicationMain::GetSpawnServer() {
      return *_spawnServer;
    }

    Effect::EffectServer& ApplicationMain::GetEffectServer() {
      return *_effectServer;
    }
  } // namespace Application
} // namespace Game