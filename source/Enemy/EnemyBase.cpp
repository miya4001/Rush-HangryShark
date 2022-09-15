/*****************************************************************//**
 * @file   EnemyBase.cpp
 * @brief  “G‚ÌŠî’êƒNƒ‰ƒX
 * 
 * @author ‹{àV—s¶
 * @date   September 2022
 *********************************************************************/
#include "EnemyBase.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Sea/SeaSphere.h"
#include "../Player/PlayerShark.h"

namespace Game {
  namespace Enemy {
    EnemyBase::EnemyBase(Application::ApplicationMain& app) : ObjectBase(app) {
      Init();
    }

    bool EnemyBase::Init() {
      // ƒpƒ‰ƒ[ƒ^‚ÌÝ’è
      SetParameters();
      return true;
    }

    void EnemyBase::Process() {

    }

    void EnemyBase::Draw() const {
      ObjectBase::Draw();
      // ƒfƒoƒbƒOî•ñ•`‰æ
#ifdef _DEBUG
      // ‹…‚ÌÕ“Ë”»’è‚Ì•`‰æ
      _sphere->Draw();
#endif
    }

    void EnemyBase::SetParameters() {
      // ŠeŽíƒpƒ‰ƒ[ƒ^‚ÌÝ’è
      _objectId = ObjectId::Enemy;
    }

    bool EnemyBase::InTheSea() {
      // ŠC’†”ÍˆÍ“à
      bool inTheSea = false;
      // ƒIƒuƒWƒFƒNƒg‚ÌƒRƒs[
      auto objects = _app.GetObjectServer().GetObjects();
      // ŠC’†”wŒi‚ð’T‚·
      for (auto object : objects) {
        if (object->GetId() == ObjectId::Sea) {
          // ŠC’†”ÍˆÍ“à”»’è
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