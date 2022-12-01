/*****************************************************************//**
 * @file   ModeGameClear.cpp
 * @brief  ���[�h�Q�[���N���A�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#include "ModeGameClear.h"
#include "../Application/ApplicationMain.h"
#include "ModeTitle.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // �e��萔
  constexpr int BackX = 960;    //!< �o�b�Nx���W
  constexpr int BackY = 750;    //!< �o�b�Ny���W
  constexpr int BubbleX = 860;  //!< �Ax���W
  constexpr int BubbleY = 750;  //!< �Ay���W
} // namespace

namespace Game {
  namespace Mode {
    ModeGameClear::ModeGameClear(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    bool ModeGameClear::Init() {
      return true;
    }

    void ModeGameClear::Enter() {
      // ���\�[�X�̓ǂݎ�菈��
      LoadResource();
      // �摜�n���h���̐ݒ�
      _gameClear = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::GameClear);
      _back = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Back);
      _bubble = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Bubble);
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
    }

    void ModeGameClear::LoadResource() {
      // �ǂݍ��ݍς݂̏ꍇ���f
      if (_isLoad) {
        return;
      }
      // �e��摜�n���h���̓ǂݍ���
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap{
        {GraphicKey::GameClear, "resource/Graphic/GameClear/GameClear.png"}
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
      // ���[�h�^�C�g���J��
      _app.GetModeServer().TransionToMode(Title);
    }
  } // namespae Mode
} // namespace Game