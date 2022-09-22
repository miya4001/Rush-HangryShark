/*****************************************************************//**
 * @file   EnemyBase.cpp
 * @brief  GĖîęNX
 * 
 * @author {āVsķ
 * @date   September 2022
 *********************************************************************/
#include "EnemyBase.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Sea/SeaSphere.h"
#include "../Player/PlayerShark.h"

namespace {
  // Geíč
  constexpr float Radius = 30.0f;       //!< ža
  constexpr float SphereY = 25.0f;      //!< yĀW
}

namespace Game {
  namespace Enemy {
    EnemyBase::EnemyBase(Application::ApplicationMain& app) : ObjectBase(app) {
      Init();
    }

    bool EnemyBase::Init() {
      // p[^ĖÝč
      SetParameters();
      return true;
    }

    void EnemyBase::Process() {

    }

    void EnemyBase::Draw() const {
      ObjectBase::Draw();
      // fobOîņ`æ
#ifdef _DEBUG
      // ĖÕËŧčĖ`æ
      _sphere->Draw();
#endif
    }

    void EnemyBase::SetParameters() {
      // eíp[^ĖÝč
      _objectId = ObjectId::Enemy;
    }

    void EnemyBase::Spawn(const AppMath::Vector4 position, const AppMath::Vector4 rotation) {
      _position = position;
      _rotation = rotation;
      // ĖÕËŧčĖÝč
      auto pos = _position;
      pos.SetY(SphereY);
      _sphere = std::make_unique<Collision::CollisionSphere>(*this, pos, Radius);
    }

    bool EnemyBase::InTheSea() {
      // CÍÍā
      bool inTheSea = false;
      // IuWFNgĖRs[
      auto objects = _app.GetObjectServer().GetObjects();
      // CwiðT·
      for (auto object : objects) {
        if (object->GetId() == ObjectId::Sea) {
          // CÍÍāŧč
          inTheSea = _sphere->IntersectSphere(std::dynamic_pointer_cast<Sea::SeaSphere>(object)->GetSphere());
          break;
        }
      }
      return inTheSea;
    }

    void EnemyBase::Move() {

    }

    void EnemyBase::Hit() {
      auto objects = _app.GetObjectServer().GetObjects();
      for (auto object : objects) {
        if (object->GetId() != ObjectId::Player) {
          continue;
        }
        if (_sphere->IntersectSphere(std::dynamic_pointer_cast<Player::PlayerShark>(object)->GetSphere())) {
          break;
        }
      }
    }
  } // namespace Enemy
} // namespace Game