/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  ���[�h�Q�[���N���X
 * 
 * @author �{�V�s��
 * @date   April 2022
 *********************************************************************/
#include "ModeGame.h"
#include "../Application/ApplicationMain.h"
#include "../Camera/Camera.h"
#include "../Object/ObjectServer.h"
#include "../Player/PlayerShark.h"
#include "../Sea/SeaSphere.h"
#include "../Enemy/EnemyTuna.h"

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
      return true;
    }

    void ModeGame::Enter() {
      // ���\�[�X�̓ǂݎ�菈��
      LoadResource();
      // �J����������
      _appMain.GetCamera().FixedPoint(CameraPosition, CameraTarget);
      // �C���w�i�̐���
      auto sea = std::make_shared<Sea::SeaSphere>(_appMain);
      _appMain.GetObjectServer().RegisterObject(sea, true);
      // �v���C���[(�T��)�̐���
      auto player = std::make_shared<Player::PlayerShark>(_appMain);
      _appMain.GetObjectServer().RegisterObject(player, true);
      // �G(�}�O��)�̐���
      auto enemy = std::make_shared<Enemy::EnemyTuna>(_appMain);
      _appMain.GetObjectServer().RegisterObject(enemy, true);
    }

    void ModeGame::Exit() {
      // ���������I�u�W�F�N�g���폜
      _appMain.GetObjectServer().Release();
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
      const ModelLoadServer::LoadModelMap loadModelMap{
        {"sea", "resource/Model/Sea/skysphere.mv1"},
        {"shark", "resource/Model/Shark/megalodon.mv1"},
        {"tuna", "resource/Model/Tuna/Tuna.mv1"}
      };
      // ���f���ǂݍ��݃T�[�o�Ɉꊇ�ǂݍ���
      _app.GetModelLoadServer().LoadModels(loadModelMap);
      // �ǂݍ��݊���
      _isLoad = true;
    }
  } // namespace Mode
} // namespace Game