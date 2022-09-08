/*****************************************************************//**
 * @file   EnemyBase.cpp
 * @brief  GĖîęNX
 * 
 * @author {āVsķ
 * @date   September 2022
 *********************************************************************/
#include "EnemyBase.h"

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
      // CÍÍOĖęf
      if (IsOverSea()) {
        return;
      }
      // [hĀWĖXV
      WorldMatrix();
      // fĖ[hĀWĖÝč
      MV1SetMatrix(_modelHandle, AppMath::UtilityDX::ToMATRIX(_world));
    }

    void EnemyBase::SetParameters() {
      // eíp[^ĖÝč
      _objectId = ObjectId::Enemy;
    }

    bool EnemyBase::IsOverSea() {
      // CÍÍŧč
      //if () {
      //  // S
      //  _objectState = ObjectState::Dead;
      //  // CÍÍO
      //  return true;
      //}
      // CÍÍā
      return false;
    }

    void EnemyBase::Move() {

    }

    void EnemyBase::Hit() {

    }
  } // namespace Enemy
} // namespace Game