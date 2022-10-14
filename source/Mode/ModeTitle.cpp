/*****************************************************************//**
 * @file   ModeTitle.cpp
 * @brief  ���[�h�^�C�g���N���X
 * 
 * @author �{�V�s��
 * @date   April 2022
 *********************************************************************/
#include "ModeTitle.h"
#include "../Application/ApplicationMain.h"
#include "ModeGame.h"

namespace {
  // �摜�n���h���L�[
  constexpr auto UnderSea = "underSea";  //!< �C��
  constexpr auto Title = "title";        //!< �^�C�g��
  constexpr auto Start = "start";        //!< �J�n
  constexpr auto Quit = "quit";          //!< �I��
  constexpr auto Cursor = "cursor";      //!< �J�[�\��
  // �����n���h���L�[
  constexpr auto Bubble = "bubble";  //!< �A
  constexpr auto Hungry = "hungry";  //!< ��
  // �e��萔
  constexpr int SwitchX = 1500;      //!< �؂�ւ��摜x���W
  constexpr int SwitchY = 850;       //!< �؂�ւ��摜y���W
  constexpr int BubbleUpX = 1350;    //!< �A��x���W
  constexpr int BubbleDownX = 1400;  //!< �A��x���W
  constexpr int BubbleUpY = 800;     //!< �A��y���W
  constexpr int BubbleDownY = 900;   //!< �A��y���W
  constexpr int SEVolume = 200;      //!< SE����
}

namespace Game {
  namespace Mode {
    ModeTitle::ModeTitle(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    bool ModeTitle::Init() {
      return true;
    }

    void ModeTitle::Enter() {
      // ���\�[�X�̓ǂݎ�菈��
      LoadResource();
      // �摜�n���h���̐ݒ�
      _sea = _app.GetGraphicLoadServer().GetGraphicHandle(UnderSea);
      _title = _app.GetGraphicLoadServer().GetGraphicHandle(Title);
      _start = _app.GetGraphicLoadServer().GetGraphicHandle(Start);
      _quit = _app.GetGraphicLoadServer().GetGraphicHandle(Quit);
      _bubble = _app.GetGraphicLoadServer().GetGraphicHandle(Cursor);
      _switch = _start;
      // �ϐ�������
      _bubbleX = BubbleUpX;
      _bubbleY = BubbleUpY;
    }

    void ModeTitle::Exit() {
      // �ϐ�������
      _decision = false;
    }

    void ModeTitle::Input(AppFrame::Input::InputManager& input) {
      // XInput�W���C�p�b�h�̓��͏����̎擾
      auto&& xJoypad = input.GetXJoypad();
      // ���X�e�B�b�N���͏��
      auto [leftX, leftY] = xJoypad.GetStick(AppFrame::Input::StickLeft);
      // �J�[�\������
      CursorInput(leftY);
      // A�{�^�������͂��ꂽ�ꍇ
      if (xJoypad.GetButton(XINPUT_BUTTON_A, AppFrame::Input::InputTrigger)) {
        // �I������
        _decision = true;
      }
    }

    void ModeTitle::Process() {
      // ����
      Input(_app.GetInputManager());
      // ���[�h�؂�ւ�
      ChangeMode();
    }

    void ModeTitle::Draw() const {
      // �摜�̕`��
      DrawGraph(0, 0, _sea, true);
      DrawGraph(0, 0, _title, true);
      DrawRotaGraph(SwitchX, SwitchY, 1.0, 0.0, _switch, true);
      DrawRotaGraph(_bubbleX, _bubbleY, 1.0, 0.0, _bubble, true);
    }

    void ModeTitle::LoadResource() {
      // �ǂݍ��ݍς݂̏ꍇ���f
      if (_isLoad) {
        return;
      }
      // �e��摜�n���h���̓ǂݍ���
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap{
        {Title, "resource/Graphic/Title/Title.png"},
        {Start, "resource/Graphic/Title/Start.png"},
        {Quit, "resource/Graphic/Title/Quit.png"},
        {Cursor, "resource/Graphic/Cursor/Bubble.png"}
      };
      // �摜�ǂݍ��݃T�[�o�Ɉꊇ�ǂݍ���
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      // �e�퉹���n���h���̓ǂݍ���
      using SoundLoadServer = AppFrame::Sound::SoundLoadServer;
      const SoundLoadServer::LoadSoundMap loadSoundMap{
        {Bubble, "resource/Sound/SE/Bubble.wav"},
        {Hungry, "resource/Sound/SE/Hungry.wav"}
      };
      // �����ǂݍ��݃T�[�o�Ɉꊇ�ǂݍ���
      _app.GetSoundLoadServer().LoadSounds(loadSoundMap);
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModeTitle::ChangeMode() {
      // �I�𖢌���̏ꍇ���f
      if (!_decision) {
        return;
      }
      // �J�[�\���ɍ��킹�Đ؂�ւ�
      switch (_bubbleY) {
      // �I����
      case BubbleUpY:
        // ���[�h�Q�[���J��
        ToModeGame();
        break;
      // �I����
      case BubbleDownY:
        // �A�v���P�[�V�����̏I���v��
        _app.RequestTerminate();
        break;
      default:
        break;
      }
    }

    void ModeTitle::CursorInput(const int leftY) {
      // ���͒l�Ȃ��̏ꍇ���f
      if (leftY == 0) {
        // �X�e�B�b�N���͂Ȃ�
        _isStick = false;
        return;
      }
      // ���͂��ꑱ���Ă���ꍇ���f
      if (_isStick) {
        return;
      }
      // �����ǂ��炩����
      bool isPositive = 0 <= leftY;
      // ���͂ɍ��킹�ĕϐ��؂�ւ�
      _switch = isPositive ? _start : _quit;
      _bubbleX = isPositive ? BubbleUpX : BubbleDownX;
      _bubbleY = isPositive ? BubbleUpY : BubbleDownY;
      // �X�e�B�b�N���͂���
      _isStick = true;
      // �ASE�̍Đ�
      _app.GetSoundComponent().PlayBackGround(Bubble, SEVolume);
    }

    void ModeTitle::ToModeGame() {
      // �L�[�̓o�^����
      bool key = _app.GetModeServer().ContainsMode(Game);
      // �L�[�����o�^�̏ꍇ
      if (!key) {
        // ���[�h�Q�[���̓o�^
        _app.GetModeServer().AddMode(Game, std::make_shared<Mode::ModeGame>(_appMain));
      }
      // ���[�h�Q�[���J��
      _app.GetModeServer().TransionToMode(Game);
      // ��SE�̍Đ�
      _app.GetSoundComponent().PlayBackGround(Hungry, SEVolume);
    }
  } // namespace Mode
} // namespace Game