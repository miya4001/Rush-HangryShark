/*****************************************************************//**
 * @file   ModeGameOver.cpp
 * @brief  ���[�h�Q�[���I�[�o�[�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#include "ModeGameOver.h"
#include "../Application/ApplicationMain.h"
#include "ModeGame.h"
#include "ModeTitle.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // �e��萔
  constexpr int SwitchX = 960;       //!< �؂�ւ��摜x���W
  constexpr int SwitchY = 750;       //!< �؂�ւ��摜y���W
  constexpr int BubbleUpX = 785;     //!< �A��x���W
  constexpr int BubbleDownX = 860;   //!< �A��x���W
  constexpr int BubbleUpY = 700;     //!< �A��y���W
  constexpr int BubbleDownY = 800;   //!< �A��y���W
  constexpr int SEVolume = 200;      //!< SE����
}

namespace Game {
  namespace Mode {
    ModeGameOver::ModeGameOver(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    bool ModeGameOver::Init() {
      return true;
    }

    void ModeGameOver::Enter() {
      // ���\�[�X�̓ǂݎ�菈��
      LoadResource();
      // �摜�n���h���̐ݒ�
      _gameOver = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::GameOver);
      _retry = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Retry);
      _backTitle = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::BackTitle);
      _bubble = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Bubble);
      _switch = _retry;
      // �ϐ�������
      _bubbleX = BubbleUpX;
      _bubbleY = BubbleUpY;
    }

    void ModeGameOver::Exit() {
      // �ϐ�������
      _decision = false;
      // �Q�[���I�[�o�[�t���O������
      _appMain.SetGameOver(false);
    }

    void ModeGameOver::Input(AppFrame::Input::InputManager& input) {
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

    void ModeGameOver::Process() {
      // ����
      Input(_app.GetInputManager());
      // ���[�h�؂�ւ�
      ChangeMode();
    }

    void ModeGameOver::Draw() const {
      // �摜�̕`��
      DrawGraph(0, 0, _gameOver, true);
      DrawRotaGraph(SwitchX, SwitchY, 1.0, 0.0, _switch, true);
      DrawRotaGraph(_bubbleX, _bubbleY, 1.0, 0.0, _bubble, true);
    }

    void ModeGameOver::LoadResource() {
      // �ǂݍ��ݍς݂̏ꍇ���f
      if (_isLoad) {
        return;
      }
      // �e��摜�n���h���̓ǂݍ���
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap{
        {GraphicKey::GameOver, "resource/Graphic/GameOver/GameOver.png"},
        {GraphicKey::Retry, "resource/Graphic/GameOver/Retry.png"},
        {GraphicKey::BackTitle, "resource/Graphic/GameOver/BackTitle.png"},
      };
      // �摜�ǂݍ��݃T�[�o�Ɉꊇ�ǂݍ���
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModeGameOver::ChangeMode() {
      // �I�𖢌���̏ꍇ���f
      if (!_decision) {
        return;
      }
      // �J�[�\���ɍ��킹�Đ؂�ւ�
      switch (_bubbleY) {
        // �I����
      case BubbleUpY:
        // ���[�h�Q�[���J��
        _app.GetModeServer().TransionToMode(Game);
        // ��SE�̍Đ�
        _app.GetSoundComponent().PlayBackGround(SoundKey::Hungry, SEVolume);
        break;
        // �I����
      case BubbleDownY:
        // ���[�h�Q�[���J��
        _app.GetModeServer().TransionToMode(Title);
        break;
      default:
        break;
      }
    }

    void ModeGameOver::CursorInput(const int leftY) {
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
      _switch = isPositive ? _retry : _backTitle;
      _bubbleX = isPositive ? BubbleUpX : BubbleDownX;
      _bubbleY = isPositive ? BubbleUpY : BubbleDownY;
      // �X�e�B�b�N���͂���
      _isStick = true;
      // �ASE�̍Đ�
      _app.GetSoundComponent().PlayBackGround(SoundKey::Bubble, SEVolume);
    }
  } // namespae Mode
} // namespace Game