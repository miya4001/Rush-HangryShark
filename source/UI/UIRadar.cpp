/*****************************************************************//**
 * @file   UIRadar.cpp
 * @brief  UIレーダークラス
 * 
 * @author 宮澤耀生
 * @date   December 2022
 *********************************************************************/
#include "UIRadar.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Player/PlayerShark.h"
#include "../ConstLoadResourceKey.h"

namespace {
  constexpr int PositionScale = 12;  //!< 座標縮尺
  constexpr int PlayerX = 250;       //!< プレイヤーx座標
  constexpr int PlayerY = 850;       //!< プレイヤーy座標
  constexpr int Radius = 3;          //!< 円半径
}

namespace Game {
  namespace UI {
    UIRadar::UIRadar(Application::ApplicationMain& app) : UIBase(app) {
      Init();
    }

    bool UIRadar::Init() {
      // 画像ハンドルの設定
      _shark = _app.GetGraphicLoadServer().GetGraphicHandle(GraphicKey::Shark);
      // 反応消去
      ResponseClear();
      return true;
    }

    void UIRadar::Process() {
      // 反応消去
      ResponseClear();
      // 入力
      Input();
      // 描画しない場合中断
      if (!_draw) {
        return;
      }
      // プレイヤーのコピー
      auto player = _app.GetObjectServer().GetPlayerShark();
      // プレイヤーのローカル座標
      auto playerPosition = player->GetPosition();
      // プレイヤーの向き
      auto playerRotation = player->GetRotation();
      // 角度(ラジアン)の設定
#ifdef _DEBUG
      _angle = static_cast<double>(AppFrame::Math::Utility::DegreeToRadian(playerRotation.GetY()));
#else
      _angle = static_cast<double>(playerRotation.GetY());
#endif
      // オブジェクトのコピー
      auto objects = _app.GetObjectServer().GetObjects();
      // 敵を探す
      for (auto&& object : objects) {
        if (object->GetId() != Object::ObjectBase::ObjectId::Enemy) {
          continue;
        }
        // 敵のローカル座標
        auto enemyPosition = object->GetPosition();
        // 敵-プレイヤー間距離
        auto distance = enemyPosition - playerPosition;
        // 型変換
        auto distanceX = static_cast<int>(distance.GetX());
        auto distanceZ = static_cast<int>(distance.GetZ());
        // 距離縮小
        distanceX = distanceX / PositionScale;
        distanceZ = distanceZ / PositionScale;
        // 描画座標(描画の都合で反転)
        int drawX = PlayerX - distanceX;
        int drawY = PlayerY + distanceZ;
        // 描画座標に登録する
        _drawPosition.emplace_back(drawX, drawY);
      }
    }

    void UIRadar::Draw() const {
      // 描画しない場合中断
      if (!_draw) {
        return;
      }
      // 仮置き背景円描画
      DrawCircle(PlayerX, PlayerY, 250, GetColor(0, 0, 0));
      DrawCircle(PlayerX, PlayerY, 100, GetColor(0, 255, 0), false);
      DrawCircle(PlayerX, PlayerY, 200, GetColor(0, 255, 0), false);
      // サメ描画
      DrawRotaGraph(PlayerX, PlayerY, 0.5, _angle, _shark, true);
      // 敵円描画
      for (auto&& [x, y] : _drawPosition) {
        DrawCircle(x, y, Radius, GetColor(255, 0, 0));
      }
    }

    void UIRadar::ResponseClear() {
      // 描画座標解放
      _drawPosition.clear();
    }

    void UIRadar::Input() {
      // 入力状態の取得
      auto&& xJoypad = _app.GetInputManager().GetXJoypad();
      // Xボタン(トリガ)の入力状態
      bool buttonX = xJoypad.GetButton(XINPUT_BUTTON_X, AppFrame::Input::InputTrigger);
      // 入力がある場合
      if (buttonX) {
        // 描画フラグ反転
        _draw = !_draw;
      }
    }
  } // namespace UI
} // namespace Game