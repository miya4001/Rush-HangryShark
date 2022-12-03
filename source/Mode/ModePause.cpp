/*****************************************************************//**
 * @file   ModePause.cpp
 * @brief  ���[�h�|�[�Y�N���X
 * 
 * @author �{�V�s��
 * @date   December 2022
 *********************************************************************/
#include "ModePause.h"
#include "../Application/ApplicationMain.h"
#include "ModeTitle.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // �e��萔
  constexpr int SwitchX = 1500;       //!< �؂�ւ��摜x���W
  constexpr int SwitchY = 1000;       //!< �؂�ւ��摜y���W
  constexpr int BubbleY = 1000;       //!< �Ay���W
  constexpr int BubbleLeftX = 1150;   //!< �A��x���W
  constexpr int BubbleRightX = 1600;  //!< �A�Ex���W
  constexpr int SEVolume = 200;       //!< SE����
} // namespace

namespace Game {
  namespace Mode {
    ModePause::ModePause(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    bool ModePause::Init() {
      return true;
    }

    void ModePause::Enter() {
      // ���\�[�X�̓ǂݎ�菈��
      LoadResource();
      // �摜�n���h���̐ݒ�
      _pause = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Pause);
      _continue = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Continue);
      _retire = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Retire);
      _bubble = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Bubble);
      // �ϐ�������
      _switch = _continue;
      _bubbleX = BubbleLeftX;
    }

    void ModePause::Exit() {
      // �ϐ�������
      _decision = false;
    }

    void ModePause::Input(AppFrame::Input::InputManager& input) {
      // XInput�W���C�p�b�h�̓��͏����̎擾
      auto&& xJoypad = input.GetXJoypad();
      // ���X�e�B�b�N���͏��
      auto [leftX, leftY] = xJoypad.GetStick(AppFrame::Input::StickLeft);
      // �J�[�\������
      CursorInput(leftX);
      // A�{�^�������͂��ꂽ�ꍇ
      if (xJoypad.GetButton(XINPUT_BUTTON_A, AppFrame::Input::InputTrigger)) {
        // �I������
        _decision = true;
      }
    }

    void ModePause::Process() {
      // ����
      Input(_app.GetInputManager());
      // ���[�h�؂�ւ�
      ChangeMode();
    }

    void ModePause::Draw() const {
      // �摜�̕`��
      DrawGraph(0, 0, _pause, true);
      DrawRotaGraph(SwitchX, SwitchY, 1.0, 0.0, _switch, true);
      DrawRotaGraph(_bubbleX, BubbleY, 1.0, 0.0, _bubble, true);
    }

    void ModePause::LoadResource() {
      // �ǂݍ��ݍς݂̏ꍇ���f
      if (_isLoad) {
        return;
      }
      // �e��摜�n���h���̓ǂݍ���
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap{
        {GraphicKey::Pause, "resource/Graphic/Pause/Pause.png"},
        {GraphicKey::Continue, "resource/Graphic/Pause/Continue.png"},
        {GraphicKey::Retire, "resource/Graphic/Pause/Retire.png"},
      };
      // �摜�ǂݍ��݃T�[�o�Ɉꊇ�ǂݍ���
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModePause::ChangeMode() {
      // �I�𖢌���̏ꍇ���f
      if (!_decision) {
        return;
      }
      // ���[�h�|�[�Y�폜
      _app.GetModeServer().PopBuck();
      // ���^�C�A�I���̏ꍇ
      if (_bubbleX == BubbleRightX) {
        // ���[�h�^�C�g���J��
        _app.GetModeServer().TransionToMode(Title);
      }
    }

    void ModePause::CursorInput(const int leftX) {
      // ���͒l�Ȃ��̏ꍇ���f
      if (leftX == 0) {
        // �X�e�B�b�N���͂Ȃ�
        _isStick = false;
        return;
      }
      // ���͂��ꑱ���Ă���ꍇ���f
      if (_isStick) {
        return;
      }
      // �����ǂ��炩����
      bool isPositive = AppFrame::Math::Utility::IsPositive(leftX);
      // ���͂ɍ��킹�ĕϐ��؂�ւ�
      _switch = isPositive ? _retire : _continue;
      _bubbleX = isPositive ? BubbleRightX : BubbleLeftX;
      // �X�e�B�b�N���͂���
      _isStick = true;
      // �ASE�̍Đ�
      _app.GetSoundComponent().PlayBackGround(SoundKey::Bubble, SEVolume);
    }
  } // namespace Mode
} // namespace Game