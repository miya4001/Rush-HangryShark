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
#include "../Effect/EffectServer.h"
#include "../UI/UIHungryGauge.h"
#include "../UI/UITimer.h"
#include "ModeGameOver.h"
#include "ModeGameClear.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // �e��萔
  namespace AppMath = AppFrame::Math;
  const AppMath::Vector4 CameraPosition{ 0.0f, 100.0f, 250.0f };  //!< �����J�����ʒu
  const AppMath::Vector4 CameraTarget{ 0.0f, 50.0f, 0.0f };       //!< �����J���������_
  const AppMath::Vector4 DirLight{ 0.0f, -1.0f, 0.0f };           //!< �f�B���N�V���i�����C�g
} // namespace

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
      // �f�B���N�V���i�����C�g�̕ύX
      ChangeLightTypeDir(AppMath::UtilityDX::ToVECTOR(DirLight));
      // ���C�g��F�ɕύX
      SetLightDifColor(GetColorF(0.5f, 0.5f, 1.0f, 0.0f));
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
      // �����R���|�[�l���g�̉��
      _spawn->Release();
      // ���������G�t�F�N�g���폜
      _appMain.GetEffectServer().Release();
      // UI�T�[�o�̉��
      _uiServer->Release();
      // �����������f���̉��
      _appMain.GetModelLoadServer().DeleteDuplicateModels();
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
      // �G�t�F�N�g�T�[�o�̍X�V
      _appMain.GetEffectServer().Process();
      // UI�T�[�o�̍X�V
      _uiServer->Process();
      // ���[�h�؂�ւ�
      ChangeMode();
    }

    void ModeGame::Draw() const {
      // �I�u�W�F�N�g�T�[�o�̕`��
      _appMain.GetObjectServer().Draw();
      // �G�t�F�N�g�T�[�o�̕`��
      _appMain.GetEffectServer().Draw();
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
        {GraphicKey::Number, {"resource/Graphic/UI/Number_sheet.png", 10, 10, 1, 70, 106}}
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
      // �e��G�t�F�N�g�n���h���̓ǂݍ���
      using EffectLoadServer = AppFrame::Effect::EffectLoadServer;
      const EffectLoadServer::LoadEffectMap loadEffectMap {
        {EffectKey::Blood, "resource/Effect/Blood/Blood.efkefc", EffectMagni::Blood},
        {EffectKey::Discover, "resource/Effect/Discover/Discover.efkefc", EffectMagni::Discover},
        {EffectKey::Paralysis, "resource/Effect/Paralysis/Paralysis.efkefc", EffectMagni::Paralysis}
      };
      // �G�t�F�N�g�ǂݍ��݃T�[�o�Ɉꊇ�ǂݍ���
      _app.GetEffectLoadServer().LoadEffects(loadEffectMap);
      // �e�퉹���n���h���̓ǂݍ���
      using SoundLoadServer = AppFrame::Sound::SoundLoadServer;
      const SoundLoadServer::LoadSoundMap loadSoundMap{
        {SoundKey::Bite, "resource/Sound/SE/Bite.wav"},
        {SoundKey::Eat, "resource/Sound/SE/Eat.wav"},
        {SoundKey::Paralysis, "resource/Sound/SE/Paralysis.wav"},
        {SoundKey::Drawn, "resource/Sound/SE/Drawn.wav"},
        {SoundKey::Whistle, "resource/Sound/SE/Whistle.wav"}
      };
      // �����ǂݍ��݃T�[�o�Ɉꊇ�ǂݍ���
      _app.GetSoundLoadServer().LoadSounds(loadSoundMap);
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModeGame::ChangeMode() {
      // �Q�[���I�[�o�[�̏ꍇ
      if (_appMain.GetGameOver()) {
        // ���[�h�Q�[���I�[�o�[�J��
        ToModeGameOver();
        return;
      }
      // �Q�[���N���A�̏ꍇ
      if (_appMain.GetGameClear()) {
        // ���[�h�Q�[���N���A�J��
        ToModeGameClear();
        return;
      }
    }

    void ModeGame::SetUI() {
      // �󕠃Q�[�W�̐���
      auto hungryGauge = std::make_shared<UI::UIHungryGauge>(_appMain);
      _uiServer->RegisterUI(hungryGauge);
      // �^�C�}�[�̐���
      auto timer = std::make_shared<UI::UITimer>(_appMain);
      _uiServer->RegisterUI(timer);
    }

    void ModeGame::ToModeGameOver() {
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

    void ModeGame::ToModeGameClear() {
      // �L�[�̓o�^����
      bool key = _app.GetModeServer().ContainsMode(GameClear);
      // �L�[�����o�^�̏ꍇ
      if (!key) {
        // ���[�h�Q�[���N���A�̓o�^
        _app.GetModeServer().AddMode(GameClear, std::make_shared<Mode::ModeGameClear>(_appMain));
      }
      // ���[�h�Q�[���N���A�J��
      _app.GetModeServer().TransionToMode(GameClear);
    }
  } // namespace Mode
} // namespace Game