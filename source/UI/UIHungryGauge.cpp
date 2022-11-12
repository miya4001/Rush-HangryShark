/*****************************************************************//**
 * @file   UIHungryGauge.cpp
 * @brief  UI�󕠃Q�[�W�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#include "UIHungryGauge.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Player/PlayerShark.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // �󕠃Q�[�W�e��萔
  constexpr int OneGaugeWidth = 7;     //!< �Q�[�W1�ڐ���
  constexpr int GaugeX = 365;          //!< �󕠃Q�[�Wx���W
  constexpr int GaugeY = 70;           //!< �󕠃Q�[�Wy���W
  constexpr int GaugeBarLeftX = 25;    //!< �󕠃Q�[�W�o�[����x���W
  constexpr int GaugeBarLeftY = 70;    //!< �󕠃Q�[�W�o�[����y���W
  constexpr int GaugeBarRightY = 120;  //!< �󕠃Q�[�W�o�[����y���W
} // namespace

namespace Game {
  namespace UI {
    UIHungryGauge::UIHungryGauge(Application::ApplicationMain& app) : UIBase(app) {
      Init();
    }

    bool UIHungryGauge::Init() {
      // �摜�n���h���̐ݒ�
      _gauge = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::HungryGauge);
      _gaugeBar = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::HungryGaugeBar);
      // �ϐ�������
      _gaugeBarRightX = GaugeBarLeftX;
      return true;
    }

    void UIHungryGauge::Process() {
      // �v���C���[�̃R�s�[
      auto player = _app.GetObjectServer().GetPlayerShark();
      // �󕠒l
      int hungry = player->GetHungry();
      // �󕠃Q�[�W�T�C�Y�v�Z
      _gaugeBarRightX = OneGaugeWidth * hungry + GaugeBarLeftX;
    }

    void UIHungryGauge::Draw() const {
      // �󕠃Q�[�W�`��
      DrawRotaGraph(GaugeX, GaugeY, 1.0, 0.0, _gauge, true);
      // �󕠃Q�[�W�o�[�`��
      DrawExtendGraph(GaugeBarLeftX, GaugeBarLeftY, _gaugeBarRightX, GaugeBarRightY, _gaugeBar, true);
    }
  } // namespace UI
} // namespace Game