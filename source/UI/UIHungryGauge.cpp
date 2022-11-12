/*****************************************************************//**
 * @file   UIHungryGauge.cpp
 * @brief  UI空腹ゲージクラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#include "UIHungryGauge.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Player/PlayerShark.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // 空腹ゲージ各種定数
  constexpr int OneGaugeWidth = 7;     //!< ゲージ1目盛幅
  constexpr int GaugeX = 365;          //!< 空腹ゲージx座標
  constexpr int GaugeY = 70;           //!< 空腹ゲージy座標
  constexpr int GaugeBarLeftX = 25;    //!< 空腹ゲージバー左上x座標
  constexpr int GaugeBarLeftY = 70;    //!< 空腹ゲージバー左上y座標
  constexpr int GaugeBarRightY = 120;  //!< 空腹ゲージバー左上y座標
} // namespace

namespace Game {
  namespace UI {
    UIHungryGauge::UIHungryGauge(Application::ApplicationMain& app) : UIBase(app) {
      Init();
    }

    bool UIHungryGauge::Init() {
      // 画像ハンドルの設定
      _gauge = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::HungryGauge);
      _gaugeBar = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::HungryGaugeBar);
      // 変数初期化
      _gaugeBarRightX = GaugeBarLeftX;
      return true;
    }

    void UIHungryGauge::Process() {
      // プレイヤーのコピー
      auto player = _app.GetObjectServer().GetPlayerShark();
      // 空腹値
      int hungry = player->GetHungry();
      // 空腹ゲージサイズ計算
      _gaugeBarRightX = OneGaugeWidth * hungry + GaugeBarLeftX;
    }

    void UIHungryGauge::Draw() const {
      // 空腹ゲージ描画
      DrawRotaGraph(GaugeX, GaugeY, 1.0, 0.0, _gauge, true);
      // 空腹ゲージバー描画
      DrawExtendGraph(GaugeBarLeftX, GaugeBarLeftY, _gaugeBarRightX, GaugeBarRightY, _gaugeBar, true);
    }
  } // namespace UI
} // namespace Game