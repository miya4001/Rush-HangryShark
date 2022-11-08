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

    void EnemyBase::Spawn(const AppMath::Vector4 position, const AppMath::Vector4 rotation) {
      // プレイヤーのコピー
      auto player = _app.GetObjectServer().GetPlayerShark();
      // プレイヤーのローカル座標
      auto playerPosition = player->GetPosition();
      // 各種パラメータの設定
      _position = playerPosition + position;
      _rotation = rotation;
      // 衝突判定の設定
      SetCollision();
    }

    void EnemyBase::SetParameters() {
      // 各種パラメータの設定
      _objectId = ObjectId::Enemy;
    }

    void EnemyBase::SetCollision() {

    }

    bool EnemyBase::InTheSea() {
      // 海中範囲内
      bool inTheSea = false;
      // オブジェクトのコピー
      auto objects = _app.GetObjectServer().GetObjects();
      // 海中背景を探す
      for (auto&& object : objects) {
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
      // プレイヤーのコピー
      auto player = _app.GetObjectServer().GetPlayerShark();
      // プレイヤーの攻撃球と衝突判定
      _sphere->IntersectSphere(std::dynamic_pointer_cast<Player::PlayerShark>(player)->GetAttack());
    }

    void EnemyBase::Dead() {
      // 死亡演出

      // 死亡状態
      SetDead();
    }
  } // namespace Enemy
} // namespace Game