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
#include "../Effect/EffectServer.h"
#include "../Mode/ModeAMG.h"

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
      // �G�t�F�N�g�T�[�o�̐���
      _effectServer = std::make_unique<Effect::EffectServer>(*this);
      // ���[�hAMG�̓o�^
      _modeServer->AddMode(Mode::AMG, std::make_unique<Mode::ModeAMG>(*this));
      // ���[�hAMG�̒ǉ�
      _modeServer->PushBack(Mode::AMG);
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

    Effect::EffectServer& ApplicationMain::GetEffectServer() {
      return *_effectServer;
    }
  } // namespace Application
} // namespace Game