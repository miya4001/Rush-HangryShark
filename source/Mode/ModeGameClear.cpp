/*****************************************************************//**
 * @file   ModeGameClear.cpp
 * @brief  ���[�h�Q�[���N���A�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#include "ModeGameClear.h"
#include "../Application/ApplicationMain.h"
#include "../Result/ResultComponent.h"
#include "ModeTitle.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // �e��萔
  constexpr int TenPlace = 10;      //!< �\�̈�
  constexpr int BackX = 960;        //!< �o�b�Nx���W
  constexpr int BackY = 900;        //!< �o�b�Ny���W
  constexpr int BubbleX = 860;      //!< �Ax���W
  constexpr int BubbleY = 900;      //!< �Ay���W
  constexpr int ResultX = 960;      //!< ���U���gx���W
  constexpr int NumberTenX = 1000;  //!< ��(�\�̈�)x���W
  constexpr int NumberOneX = 1080;  //!< ��(��̈�)x���W
  constexpr int ShrimpY = 550;      //!< �G�ry���W
  constexpr int TunaY = 650;        //!< �}�O��y���W
  constexpr int JerryfishY = 750;   //!< �N���Qy���W
  constexpr int SEVolume = 200;     //!< SE����
} // namespace

namespace Game {
  namespace Mode {
    ModeGameClear::ModeGameClear(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    void ModeGameClear::Enter() {
      // ���\�[�X�̓ǂݎ�菈��
      LoadResource();
      // �摜�n���h���̐ݒ�
      _gameClear = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::GameClear);
      _shrimp = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Shrimp);
      _tuna = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Tuna);
      _jerryfish = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Jerryfish);
      _back = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Back);
      _bubble = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Bubble);
      _number = _app.GetGraphicLoadServer().GetDivGraphicHandles(GraphicKey::Number);
      // �G���̐ݒ�
      SetEnemyNumbers();
    }

    void ModeGameClear::Exit() {
      // �ϐ�������
      _decision = false;
      // �Q�[���N���A�t���O������
      _appMain.SetGameClear(false);
    }

    void ModeGameClear::Input(AppFrame::Input::InputManager& input) {
      // XInput�W���C�p�b�h�̓��͏����̎擾
      auto&& xJoypad = input.GetXJoypad();
      // A�{�^�������͂��ꂽ�ꍇ
      if (xJoypad.GetButton(XINPUT_BUTTON_A, AppFrame::Input::InputTrigger)) {
        // �I������
        _decision = true;
      }
    }

    void ModeGameClear::Process() {
      // ����
      Input(_app.GetInputManager());
      // ���[�h�؂�ւ�
      ChangeMode();
    }

    void ModeGameClear::Draw() const {
      // �摜�̕`��
      DrawGraph(0, 0, _gameClear, true);
      DrawRotaGraph(BackX, BackY, 1.0, 0.0, _back, true);
      DrawRotaGraph(BubbleX, BubbleY, 1.0, 0.0, _bubble, true);
      // ���U���g���̕`��
      DrawRotaGraph(ResultX, ShrimpY, 1.0, 0.0, _shrimp, true);
      DrawRotaGraph(ResultX, TunaY, 1.0, 0.0, _tuna, true);
      DrawRotaGraph(ResultX, JerryfishY, 1.0, 0.0, _jerryfish, true);
      DrawRotaGraph(NumberTenX, ShrimpY, 1.0, 0.0, _number.at(_shrimpTen), true);
      DrawRotaGraph(NumberTenX, TunaY, 1.0, 0.0, _number.at(_tunaTen), true);
      DrawRotaGraph(NumberTenX, JerryfishY, 1.0, 0.0, _number.at(_jerryfishTen), true);
      DrawRotaGraph(NumberOneX, ShrimpY, 1.0, 0.0, _number.at(_shrimpOne), true);
      DrawRotaGraph(NumberOneX, TunaY, 1.0, 0.0, _number.at(_tunaOne), true);
      DrawRotaGraph(NumberOneX, JerryfishY, 1.0, 0.0, _number.at(_jerryfishOne), true);
    }

    void ModeGameClear::LoadResource() {
      // �ǂݍ��ݍς݂̏ꍇ���f
      if (_isLoad) {
        return;
      }
      // �e��摜�n���h���̓ǂݍ���
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap{
        {GraphicKey::GameClear, "resource/Graphic/GameClear/GameClear.png"},
        {GraphicKey::Shrimp, "resource/Graphic/GameClear/Shrimp.png"},
        {GraphicKey::Tuna, "resource/Graphic/GameClear/Tuna.png"},
        {GraphicKey::Jerryfish, "resource/Graphic/GameClear/Jerryfish.png"}
      };
      // �摜�ǂݍ��݃T�[�o�Ɉꊇ�ǂݍ���
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModeGameClear::ChangeMode() {
      // �I�𖢌���̏ꍇ���f
      if (!_decision) {
        return;
      }
      // �A2SE�̍Đ�
      _app.GetSoundComponent().PlayBackGround(SoundKey::Bubble2, SEVolume);
      // ���[�h�^�C�g���J��
      _app.GetModeServer().TransionToMode(Title);
    }

    void ModeGameClear::SetEnemyNumbers() {
      // �G�r���̎擾
      int shrimp = _appMain.GetResultComponent().GetShrimp();
      // �G�r���̐ݒ�
      _shrimpTen = shrimp / TenPlace;
      _shrimpOne = shrimp % TenPlace;
      // �}�O�����̎擾
      int tuna = _appMain.GetResultComponent().GetTuna();
      // �}�O�����̐ݒ�
      _tunaTen = tuna / TenPlace;
      _tunaOne = tuna % TenPlace;
      // �N���Q���̎擾
      int jerryfish = _appMain.GetResultComponent().GetJerryfish();
      // �N���Q���̐ݒ�
      _jerryfishTen = jerryfish / TenPlace;
      _jerryfishOne = jerryfish % TenPlace;
    }
  } // namespae Mode
} // namespace Game