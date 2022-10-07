/*****************************************************************//**
 * @file   UIHungryGauge.cpp
 * @brief  UIó Q[WNX
 * 
 * @author {àVs¶
 * @date   October 2022
 *********************************************************************/
#include "UIHungryGauge.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Player/PlayerShark.h"

namespace {
  // ænhL[
  constexpr auto HungryGauge = "hungryGauge";        //!< ó Q[W
  constexpr auto HungryGaugeBar = "hungryGaugeBar";  //!< ó Q[Wo[
  // ó Q[Weíè
  constexpr int OneGaugeWidth = 7;     //!< Q[W1Ú·
  constexpr int GaugeX = 365;          //!< ó Q[WxÀW
  constexpr int GaugeY = 70;           //!< ó Q[WyÀW
  constexpr int GaugeBarLeftX = 25;    //!< ó Q[Wo[¶ãxÀW
  constexpr int GaugeBarLeftY = 70;    //!< ó Q[Wo[¶ãyÀW
  constexpr int GaugeBarRightY = 120;  //!< ó Q[Wo[¶ãyÀW
}

namespace Game {
  namespace UI {
    UIHungryGauge::UIHungryGauge(Application::ApplicationMain& app) : UIBase(app) {
      Init();
    }

    bool UIHungryGauge::Init() {
      // ænhÌÝè
      _gauge = _app.GetGraphicLoadServer().GetGraphicHandle(HungryGauge);
      _gaugeBar = _app.GetGraphicLoadServer().GetGraphicHandle(HungryGaugeBar);
      // Ïú»
      _gaugeBarRightX = GaugeBarLeftX;
      return true;
    }

    void UIHungryGauge::Process() {
      // vC[ÌRs[
      auto player = _app.GetObjectServer().GetPlayerShark();
      // ó l
      int hungry = player->GetHungry();
      // ó Q[WTCYvZ
      _gaugeBarRightX = OneGaugeWidth * hungry + GaugeBarLeftX;
    }

    void UIHungryGauge::Draw() const {
      // ó Q[W`æ
      DrawRotaGraph(GaugeX, GaugeY, 1.0, 0.0, _gauge, true);
      // ó Q[Wo[`æ
      DrawExtendGraph(GaugeBarLeftX, GaugeBarLeftY, _gaugeBarRightX, GaugeBarRightY, _gaugeBar, true);
    }
  } // namespace UI
} // namespace Game