/*****************************************************************//**
 * @file   ModeAMG.cpp
 * @brief  ���[�hAMG�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#include "ModeAMG.h"
#include "../Application/ApplicationMain.h"
#include "ModeTitle.h"

namespace {
  // �摜�n���h���L�[
  constexpr auto UnderSea = "underSea";  //!< �C��
  constexpr auto AMGLogo = "amg";        //!< AMG
  // �e��萔
  constexpr int MaxCount = 30;  //!< �J�E���g���
}

namespace Game {
  namespace Mode {
    ModeAMG::ModeAMG(Application::ApplicationMain& app) : ModeBase(*app.GetApplication()), _appMain(app) {

    }

    bool ModeAMG::Init() {
      return true;
    }

    void ModeAMG::Enter() {
      // ���\�[�X�̓ǂݎ�菈��
      LoadResource();
      // �摜�n���h���̐ݒ�
      _sea = _app.GetGraphicLoadServer().GetGraphicHandle(UnderSea);
      _amg = _app.GetGraphicLoadServer().GetGraphicHandle(AMGLogo);
    }

    void ModeAMG::Exit() {

    }

    void ModeAMG::Process() {
      // �J�E���g�𑝂₷
      ++_modeCount;
      // ���[�h�؂�ւ�
      ChangeMode();
    }

    void ModeAMG::Draw() const {
      // �摜�̕`��
      DrawGraph(0, 0, _sea, true);
      DrawGraph(0, 0, _amg, true);
    }

    void ModeAMG::LoadResource() {
      // �ǂݍ��ݍς݂̏ꍇ���f
      if (_isLoad) {
        return;
      }
      // �e��摜�n���h���̓ǂݍ���
      using GraphicLoadServer = AppFrame::Graphic::GraphicLoadServer;
      const GraphicLoadServer::LoadGraphicMap loadGraphicMap {
        {UnderSea, "resource/Graphic/BackGround/UnderSea.png"},
        {AMGLogo, "resource/Graphic/BackGround/AMG.png"}
      };
      // �摜�ǂݍ��݃T�[�o�Ɉꊇ�ǂݍ���
      _app.GetGraphicLoadServer().LoadGraphics(loadGraphicMap);
      // �ǂݍ��݊���
      _isLoad = true;
    }

    void ModeAMG::ChangeMode() {
      // �J�E���g����������̏ꍇ���f
      if (_modeCount <= MaxCount) {
        return;
      }
      // ���[�h�^�C�g���̓o�^
      _app.GetModeServer().AddMode(Title, std::make_shared<Mode::ModeTitle>(_appMain));
      // ���[�h�^�C�g���J��
      _app.GetModeServer().TransionToMode(Title);
    }
  } // namespace Mode
} // Game