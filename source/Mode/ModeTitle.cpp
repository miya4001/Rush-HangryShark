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
#include "ModeExplanation.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // �e��萔
  constexpr int SwitchX = 1500;       //!< �؂�ւ��摜x���W
  constexpr int SwitchY = 850;        //!< �؂�ւ��摜y���W
  constexpr int CursorStart = 1;      //!< �J�[�\���J�n
  constexpr int CursorExplain = 2;    //!< �J�[�\������
  constexpr int CursorQuit = 3;       //!< �J�[�\���I��
  constexpr int BubbleX = 1350;       //!< �Ax���W
  constexpr int BubbleStart = 750;    //!< �A�J�ny���W
  constexpr int BubbleExplain = 850;  //!< �A����y���W
  constexpr int BubbleQuit = 950;     //!< �A�I��y���W
  constexpr int SEVolume = 200;       //!< SE����
} // namespace

namespace Game {
  namespace Mode {
    ModeTitle::ModeTitle(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    void ModeTitle::Enter() {
      // ���\�[�X�̓ǂݎ�菈��
      LoadResource();
      // �摜�n���h���̐ݒ�
      _sea = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::UnderSea);
      _title = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Title);
      _start = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Start);
      _explain = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Explain);
      _quit = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Quit);
      _bubble = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Bubble);
      // �ϐ�������
      _switch = _start;
      _cursor = CursorStart;
      _bubbleY = BubbleStart;
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
      DrawRotaGraph(BubbleX, _bubbleY, 1.0, 0.0, _bubble, true);
    }

    void ModeTitle::LoadResource() {
      // �ǂݍ��ݍς݂̏ꍇ���f
      if (_isLoad) {
        return;
      }
      // �e��摜�n���h���̓ǂݍ���
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap{
        {GraphicKey::Title, "resource/Graphic/Title/Title.png"},
        {GraphicKey::Start, "resource/Graphic/Title/Start.png"},
        {GraphicKey::Explain, "resource/Graphic/Title/Explain.png"},
        {GraphicKey::Quit, "resource/Graphic/Title/Quit.png"},
        {GraphicKey::Back, "resource/Graphic/Explanation/Back.png"},
        {GraphicKey::Bubble, "resource/Graphic/Cursor/Bubble.png"}
      };
      // �摜�ǂݍ��݃T�[�o�Ɉꊇ�ǂݍ���
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      // �e�퉹���n���h���̓ǂݍ���
      using SoundLoadServer = AppFrame::Sound::SoundLoadServer;
      const SoundLoadServer::LoadSoundMap loadSoundMap{
        {SoundKey::Bubble1, "resource/Sound/SE/Bubble1.wav"},
        {SoundKey::Bubble2, "resource/Sound/SE/Bubble2.wav"},
        {SoundKey::Hungry, "resource/Sound/SE/Hungry.wav"}
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
      // �A2SE�̍Đ�
      _app.GetSoundComponent().PlayBackGround(SoundKey::Bubble2, SEVolume);
      // �J�[�\���ɍ��킹�Đ؂�ւ�
      switch (_cursor) {
      // �J�n�I��
      case CursorStart:
        // ���[�h�Q�[���J��
        ToModeGame();
        break;
      // �����I��
      case CursorExplain:
        // ���[�h�����J��
        ToModeExplanation();
        break;
      // �I���I��
      case CursorQuit:
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
      bool isPositive = AppFrame::Math::Utility::IsPositive(leftY);
      // ���͂ɍ��킹�ăJ�[�\���㉺
      if (isPositive) {
        // �J�n��艺�̏ꍇ
        if (CursorStart < _cursor) {
          // �J�[�\�����グ��
          --_cursor;
        }
      } else {
        // �I������̏ꍇ
        if (_cursor < CursorQuit) {
          // �J�[�\����������
          ++_cursor;
        }
      }
      // �J�[�\���ɍ��킹�ĕϐ��؂�ւ�
      switch (_cursor) {
      // �J�n
      case CursorStart:
        _switch = _start;
        _bubbleY = BubbleStart;
        break;
      // ����
      case CursorExplain:
        _switch = _explain;
        _bubbleY = BubbleExplain;
        break;
      // �I��
      case CursorQuit:
        _switch = _quit;
        _bubbleY = BubbleQuit;
        break;
      default:
        break;
      }
      // �X�e�B�b�N���͂���
      _isStick = true;
      // �A1SE�̍Đ�
      _app.GetSoundComponent().PlayBackGround(SoundKey::Bubble1, SEVolume);
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
      _app.GetSoundComponent().PlayBackGround(SoundKey::Hungry, SEVolume);
    }

    void ModeTitle::ToModeExplanation() {
      // �L�[�̓o�^����
      bool key = _app.GetModeServer().ContainsMode(Explanation);
      // �L�[�����o�^�̏ꍇ
      if (!key) {
        // ���[�h�����̓o�^
        _app.GetModeServer().AddMode(Explanation, std::make_shared<Mode::ModeExplanation>(_appMain));
      }
      // ���[�h�����J��
      _app.GetModeServer().TransionToMode(Explanation);
    }
  } // namespace Mode
} // namespace Game