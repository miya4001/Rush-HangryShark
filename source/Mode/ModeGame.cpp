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
#include "../UI/UIHungryGauge.h"
#include "../UI/UITimer.h"
#include "ModeGameOver.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // �e��萔
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
      // UI�T�[�o�̐���
      _uiServer = std::make_unique<UI::UIServer>();
      return true;
    }

    void ModeGame::Enter() {
      // ���\�[�X�̓ǂݎ�菈��
      LoadResource();
      // �J����������
      _appMain.GetCamera().FixedPoint(CameraPosition, CameraTarget);
      // �������̐ݒ�
      _spawn->SetSpawn();
      // UI�̐ݒ�
      SetUI();
    }

    void ModeGame::Exit() {
      // ���������I�u�W�F�N�g���폜
      _appMain.GetObjectServer().Release();
      // �����������f���̉��
      _appMain.GetModelLoadServer().DeleteDuplicateModels();
      // �����R���|�[�l���g�̉��
      _spawn->Release();
      // UI�T�[�o�̉��
      _uiServer->Release();
    }

    void ModeGame::Input(AppFrame::Input::InputManager& input) {
      // XInput�W���C�p�b�h�̓��͏����̎擾
      auto&& xJoypad = input.GetXJoypad();
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
      // UI�T�[�o�̍X�V
      _uiServer->Process();
      // ���[�h�؂�ւ�
      ChangeMode();
    }

    void ModeGame::Draw() const {
      // �I�u�W�F�N�g�T�[�o�̕`��
      _appMain.GetObjectServer().Draw();
      // UI�T�[�o�̕`��
      _uiServer->Draw();
    }

    void ModeGame::LoadResource() {
      // �ǂݍ��ݍς݂̏ꍇ���f
      if (_isLoad) {
        return;
      }
      // �e��摜�n���h���̓ǂݍ���
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap{
        {GraphicKey::HungryGauge, "resource/Graphic/UI/HungryGauge.png"},
        {GraphicKey::HungryGaugeBar, "resource/Graphic/UI/HungryGaugeBar.png"},
        {GraphicKey::TimerColon, "resource/Graphic/UI/Colon.png"}
      };
      // �e�핪���摜�n���h���̓ǂݍ���
      const GraphicLoadServer::LoadDivGraphicMap loadDivGraphicMap{
        {GraphicKey::TimerNumber, {"resource/Graphic/UI/Number_sheet.png", 10, 10, 1, 70, 106}}
      };
      // �摜�ǂݍ��݃T�[�o�Ɉꊇ�ǂݍ���
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      _app.GetGraphicLoadServer().LoadDivGraphics(loadDivGraphicMap);
      // �e�탂�f���n���h���̓ǂݍ���
      using ModelLoadServer = AppFrame::Model::ModelLoadServer;
      const ModelLoadServer::LoadModelMap loadModelMap {
        {ModelKey::SeaSphere, "resource/Model/Sea/skysphere.mv1"},
        {ModelKey::Shark, "resource/Model/Shark/megalodon.mv1"},
        {ModelKey::Shrimp, "resource/Model/Shrimp/Shrimp.mv1"},
        {ModelKey::Tuna, "resource/Model/Tuna/Tuna.mv1"},
        {ModelKey::Jerryfish, "resource/Model/Jerryfish/jerryfish.mv1"}
      };
      // ���f���ǂݍ��݃T�[�o�Ɉꊇ�ǂݍ���
      _app.GetModelLoadServer().LoadModels(loadModelMap);
      // �e�퉹���n���h���̓ǂݍ���
      using SoundLoadServer = AppFrame::Sound::SoundLoadServer;
      const SoundLoadServer::LoadSoundMap loadSoundMap{
        {SoundKey::Bite, "resource/Sound/SE/Bite.wav"},
        {SoundKey::Eat, "resource/Sound/SE/Eat.wav"}
      };
      // �����ǂݍ��݃T�[�o�Ɉꊇ�ǂݍ���
      _app.GetSoundLoadServer().LoadSounds(loadSoundMap);
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

    void ModeGame::SetUI() {
      // �󕠃Q�[�W�̐���
      auto hungryGauge = std::make_shared<UI::UIHungryGauge>(_appMain);
      _uiServer->RegisterUI(hungryGauge);
      // �^�C�}�[�̐���
      auto timer = std::make_shared<UI::UITimer>(_appMain);
      _uiServer->RegisterUI(timer);
    }
  } // namespace Mode
} // namespace Game