/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  ���[�h�Q�[���N���X
 * 
 * @author �{�V�s��
 * @date   April 2022
 *********************************************************************/
#include "ModeGame.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Camera/Camera.h"
#include "../Sea/SeaSphere.h"
#include "../Player/PlayerShark.h"
#include "ModeGameOver.h"

namespace {
  namespace AppMath = AppFrame::Math;
  const AppMath::Vector4 CameraPosition{ 0.0f, 100.0f, 250.0f };  //!< �����J�����ʒu
  const AppMath::Vector4 CameraTarget{ 0.0f, 50.0f, 0.0f };       //!< �����J���������_
}

namespace Game {
  namespace Mode {
    ModeGame::ModeGame(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    bool ModeGame::Init() {
      // �����R���|�[�l���g�̐���
      _spawn = std::make_unique<Spawn::SpawnComponent>(_appMain);
      return true;
    }

    void ModeGame::Enter() {
      // ���\�[�X�̓ǂݎ�菈��
      LoadResource();
      // �J����������
      _appMain.GetCamera().FixedPoint(CameraPosition, CameraTarget);
      // �������̐ݒ�
      SetSpawn();
    }

    void ModeGame::Exit() {
      // ���������I�u�W�F�N�g���폜
      _appMain.GetObjectServer().Release();
      // �����������f���̉��
      _appMain.GetModelLoadServer().DeleteDuplicateModels();
      // �����R���|�[�l���g�̉��
      _spawn->Release();
    }

    void ModeGame::Input(AppFrame::Input::InputManager& input) {
      // XInput�W���C�p�b�h�̓��͏����̎擾
      auto xJoypad = input.GetXJoypad();
      // START�{�^�������͂��ꂽ�ꍇ
      if (xJoypad.GetButton(XINPUT_BUTTON_START, AppFrame::Input::InputTrigger)) {
        // �A�v���P�[�V�����̏I���v��
        _app.RequestTerminate();
      }
    }

    void ModeGame::Process() {
      // ����
      Input(_app.GetInputManager());
      // �I�u�W�F�N�g�T�[�o�̍X�V
      _appMain.GetObjectServer().Process();
      // �����R���|�[�l���g�̍X�V
      _spawn->Process();
      // ���[�h�؂�ւ�
      ChangeMode();
    }

    void ModeGame::Draw() const {
      // �I�u�W�F�N�g�T�[�o�̕`��
      _appMain.GetObjectServer().Draw();
    }

    void ModeGame::LoadResource() {
      // �ǂݍ��ݍς݂̏ꍇ���f
      if (_isLoad) {
        return;
      }
      // �e�탂�f���n���h���̓ǂݍ���
      using ModelLoadServer = AppFrame::Model::ModelLoadServer;
      const ModelLoadServer::LoadModelMap loadModelMap {
        {"sea", "resource/Model/Sea/skysphere.mv1"},
        {"shark", "resource/Model/Shark/megalodon.mv1"},
        {"tuna", "resource/Model/Tuna/Tuna.mv1"},
        {"jerryfish", "resource/Model/Jerryfish/jerryfish.mv1"}
      };
      // ���f���ǂݍ��݃T�[�o�Ɉꊇ�ǂݍ���
      _app.GetModelLoadServer().LoadModels(loadModelMap);
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModeGame::ChangeMode() {
      // �Q�[���I�[�o�[�łȂ��ꍇ���f
      if (!_appMain.GetGameOver()) {
        return;
      }
      // �L�[�̓o�^����
      bool key = _app.GetModeServer().ContainsMode(GameOver);
      // �L�[�����o�^�̏ꍇ
      if (!key) {
        // ���[�h�Q�[���I�[�o�[�̓o�^
        _app.GetModeServer().AddMode(GameOver, std::make_shared<Mode::ModeGameOver>(_appMain));
      }
      // ���[�h�Q�[���I�[�o�[�J��
      _app.GetModeServer().TransionToMode(GameOver);
    }

    void ModeGame::SetSpawn() {
      // �C���w�i�̐���
      auto sea = std::make_shared<Sea::SeaSphere>(_appMain);
      _appMain.GetObjectServer().RegisterObject(sea, true);
      // �v���C���[(�T��)�̐���
      auto player = std::make_shared<Player::PlayerShark>(_appMain);
      _appMain.GetObjectServer().RegisterObject(player, true);
      // �������̐ݒ�
      _spawn->SetSpawn();
    }
  } // namespace Mode
} // namespace Game