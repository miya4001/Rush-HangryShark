/*****************************************************************//**
 * @file   ApplicationMain.cpp
 * @brief  �A�v���P�[�V�������C���N���X
 * 
 * @author �{�V�s��
 * @date   April 2022
 *********************************************************************/
#include "ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Camera/Camera.h"
#include "../Spawn/SpawnServer.h"
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
      // �I�u�W�F�N�g�T�[�o�̐���
      _objectServer = std::make_unique<Object::ObjectServer>();
      // �J�����̐���
      _camera = std::make_unique<Camera::Camera>();
      // �����T�[�o�̐���
      _spawnServer = std::make_unique<Spawn::SpawnServer>(*this);
      // ���[�h�^�C�g���̓o�^
      _modeServer->AddMode(Mode::MTitle, std::make_unique<Mode::ModeTitle>(*this));
      // ���[�h�^�C�g���̒ǉ�
      _modeServer->PushBack(Mode::MTitle);
      return true;  // ����������
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
  } // namespace Application
} // namespace Game