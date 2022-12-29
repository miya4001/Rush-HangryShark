/*****************************************************************//**
 * @file   UIRadar.cpp
 * @brief  UI[_[NX
 * 
 * @author {àVs¶
 * @date   December 2022
 *********************************************************************/
#include "UIRadar.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Player/PlayerShark.h"

namespace {
  constexpr int PositionScale = 12;  //!< ÀWkÚ
  constexpr int PlayerX = 250;       //!< vC[xÀW
  constexpr int PlayerY = 850;       //!< vC[yÀW
  constexpr int Radius = 3;          //!< ~¼a
}

namespace Game {
  namespace UI {
    UIRadar::UIRadar(Application::ApplicationMain& app) : UIBase(app) {
      Init();
    }

    bool UIRadar::Init() {
      // ½Á
      ResponseClear();
      return true;
    }

    void UIRadar::Process() {
      // ½Á
      ResponseClear();
      // vC[ÌRs[
      auto player = _app.GetObjectServer().GetPlayerShark();
      // vC[Ì[JÀW
      auto playerPosition = player->GetPosition();
      // vC[Ìü«
      auto playerRotation = player->GetRotation();
      // px(WA)ÌÝè
#ifdef _DEBUG
      _angle = static_cast<double>(AppFrame::Math::Utility::DegreeToRadian(playerRotation.GetY()));
#else
      _angle = static_cast<double>(playerRotation.GetY());
#endif
      // IuWFNgÌRs[
      auto objects = _app.GetObjectServer().GetObjects();
      // GðT·
      for (auto&& object : objects) {
        if (object->GetId() != Object::ObjectBase::ObjectId::Enemy) {
          continue;
        }
        // GÌ[JÀW
        auto enemyPosition = object->GetPosition();
        // G-vC[Ô£
        auto distance = enemyPosition - playerPosition;
        // ^Ï·
        auto distanceX = static_cast<int>(distance.GetX());
        auto distanceZ = static_cast<int>(distance.GetZ());
        // £k¬
        distanceX = distanceX / PositionScale;
        distanceZ = distanceZ / PositionScale;
        // `æÀW(`æÌsÅ½])
        int drawX = PlayerX - distanceX;
        int drawY = PlayerY + distanceZ;
        // `æÀWÉo^·é
        _drawPosition.emplace_back(drawX, drawY);
      }
    }

    void UIRadar::Draw() const {
      // ¼u«wi~`æ
      DrawCircle(PlayerX, PlayerY, 250, GetColor(0, 0, 0));
      DrawCircle(PlayerX, PlayerY, 100, GetColor(0, 255, 0), false);
      DrawCircle(PlayerX, PlayerY, 200, GetColor(0, 255, 0), false);
      // vC[~`æ
      DrawCircle(PlayerX, PlayerY, Radius, GetColor(0, 255, 0));
      // G~`æ
      for (auto&& [x, y] : _drawPosition) {
        DrawCircle(x, y, Radius, GetColor(255, 0, 0));
      }
    }

    void UIRadar::ResponseClear() {
      // `æÀWðú
      _drawPosition.clear();
    }
  } // namespace UI
} // namespace Game