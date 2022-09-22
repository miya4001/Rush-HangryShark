/*****************************************************************//**
 * @file   EnemyBase.cpp
 * @brief  敵の基底クラス
 * 
 * @author 宮澤耀生
 * @date   September 2022
 *********************************************************************/
#include "EnemyBase.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Sea/SeaSphere.h"
#include "../Player/PlayerShark.h"

namespace {
  // 敵各種定数
  constexpr float Radius = 30.0f;       //!< 球半径
  constexpr float SphereY = 25.0f;      //!< 球y座標
}

namespace Game {
  namespace Enemy {
    EnemyBase::EnemyBase(Application::ApplicationMain& app) : ObjectBase(app) {
      Init();
    }

    bool EnemyBase::Init() {
      // パラメータの設定
      SetParameters();
      return true;
    }

    void EnemyBase::Process() {

    }

    void EnemyBase::Draw() const {
      ObjectBase::Draw();
      // デバッグ情報描画
#ifdef _DEBUG
      // 球の衝突判定の描画
      _sphere->Draw();
#endif
    }

    void EnemyBase::SetParameters() {
      // 各種パラメータの設定
      _objectId = ObjectId::Enemy;
    }

    void EnemyBase::Spawn(const AppMath::Vector4 position, const AppMath::Vector4 rotation) {
      _position = position;
      _rotation = rotation;
      // 球の衝突判定の設定
      auto pos = _position;
      pos.SetY(SphereY);
      _sphere = std::make_unique<Collision::CollisionSphere>(*this, pos, Radius);
    }

    bool EnemyBase::InTheSea() {
      // 海中範囲内
      bool inTheSea = false;
      // オブジェクトのコピー
      auto objects = _app.GetObjectServer().GetObjects();
      // 海中背景を探す
      for (auto object : objects) {
        if (object->GetId() == ObjectId::Sea) {
          // 海中範囲内判定
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