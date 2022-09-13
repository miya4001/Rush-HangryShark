/*****************************************************************//**
 * @file   EnemyBase.cpp
 * @brief  “G‚ÌŠî’êƒNƒ‰ƒX
 * 
 * @author ‹{àV—s¶
 * @date   September 2022
 *********************************************************************/
#include "EnemyBase.h"

namespace Game {
  namespace Enemy {
    EnemyBase::EnemyBase(Application::ApplicationMain& app) : ObjectBase(app) {
      Init();
    }

    bool EnemyBase::Init() {
      // ƒpƒ‰ƒ[ƒ^‚Ìİ’è
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
      // Šeíƒpƒ‰ƒ[ƒ^‚Ìİ’è
      _objectId = ObjectId::Enemy;
    }

    bool EnemyBase::IsOverSea() {
      // ŠC’†”ÍˆÍ”»’è
      //if () {
      //  // €–S
      //  _objectState = ObjectState::Dead;
      //  // ŠC’†”ÍˆÍŠO
      //  return true;
      //}
      // ŠC’†”ÍˆÍ“à
      return false;
    }

    void EnemyBase::Move() {

    }

    void EnemyBase::Hit() {

    }
  } // namespace Enemy
} // namespace Game