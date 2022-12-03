/*****************************************************************//**
 * @file   ModeExplanation.cpp
 * @brief  ���[�h�����N���X
 * 
 * @author �{�V�s��
 * @date   December 2022
 *********************************************************************/
#include "ModeExplanation.h"
#include "../Application/ApplicationMain.h"
#include "ModeTitle.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // �e��萔
  constexpr int BackX = 1700;    //!< �o�b�Nx���W
  constexpr int BackY = 1000;    //!< �o�b�Ny���W
  constexpr int BubbleX = 1600;  //!< �Ax���W
  constexpr int BubbleY = 1000;  //!< �Ay���W
} // namespace

namespace Game {
  namespace Mode {
    ModeExplanation::ModeExplanation(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    void ModeExplanation::Enter() {
      // ���\�[�X�̓ǂݎ�菈��
      LoadResource();
      // �摜�n���h���̐ݒ�
      _explanation = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Explanation);
      _back = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Back);
      _bubble = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Bubble);
    }

    void ModeExplanation::Exit() {
      // �ϐ�������
      _decision = false;
    }

    void ModeExplanation::Input(AppFrame::Input::InputManager& input) {
      // XInput�W���C�p�b�h�̓��͏����̎擾
      auto&& xJoypad = input.GetXJoypad();
      // A�{�^�������͂��ꂽ�ꍇ
      if (xJoypad.GetButton(XINPUT_BUTTON_A, AppFrame::Input::InputTrigger)) {
        // �I������
        _decision = true;
      }
    }

    void ModeExplanation::Process() {
      // ����
      Input(_app.GetInputManager());
      // ���[�h�؂�ւ�
      ChangeMode();
    }

    void ModeExplanation::Draw() const {
      // �摜�̕`��
      DrawGraph(0, 0, _explanation, true);
      DrawRotaGraph(BackX, BackY, 1.0, 0.0, _back, true);
      DrawRotaGraph(BubbleX, BubbleY, 1.0, 0.0, _bubble, true);
    }

    void ModeExplanation::LoadResource() {
      // �ǂݍ��ݍς݂̏ꍇ���f
      if (_isLoad) {
        return;
      }
      // �e��摜�n���h���̓ǂݍ���
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap{
        {GraphicKey::Explanation, "resource/Graphic/Explanation/Explanation.png"}
      };
      // �摜�ǂݍ��݃T�[�o�Ɉꊇ�ǂݍ���
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModeExplanation::ChangeMode() {
      // �I�𖢌���̏ꍇ���f
      if (!_decision) {
        return;
      }
      // ���[�h�^�C�g���J��
      _app.GetModeServer().TransionToMode(Title);
    }
  } // namespace Mode
} // namespace Game