/*****************************************************************//**
 * @file   EnemyJerryfish.cpp
 * @brief  敵(クラゲ)クラス
 * 
 * @author 宮澤耀生
 * @date   September 2022
 *********************************************************************/
#include "EnemyJerryfish.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Player/PlayerShark.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // クラゲ各種定数
  constexpr int FoodValue = 1;            //!< 食料値
  constexpr float Scale = 0.15f;          //!< 拡大率
  constexpr float SphereY = 50.0f;        //!< 球y座標
  constexpr float Radius = 50.0f;         //!< 球半径
  constexpr float AttackRadius = 100.0f;  //!< 攻撃球半径
  // 移動定数
  constexpr float RotateDegree = 1.0f;  //!< 回転角度(デグリー値)
  constexpr float FloatUpSpeed = 0.1f;  //!< 浮上速度
  // 充電定数
  constexpr int ChargeCountMax = 300;  //!< 充電カウント上限
  // 攻撃定数
  constexpr int AttackCountMax = 180;  //!< 攻撃カウント上限
}

namespace Game {
  namespace Enemy {
    EnemyJerryfish::EnemyJerryfish(Application::ApplicationMain& app) : EnemyBase(app) {
      Init();
    }

    void EnemyJerryfish::Process() {
      // 海中範囲外の場合中断
      if (!InTheSea()) {
        // 死亡状態
        SetDead();
        return;
      }
      // クラゲの状態に合わせて処理
      switch (_enemyState) {
      // 遊泳
      case EnemyState::Swim:
        // 移動
        Move();
        // 充電
        Charge();
        break;
      // 攻撃
      case EnemyState::Attack:
        Attack();
        break;
      // 死亡
      case EnemyState::Dead:
        Dead();
        break;
      default:
        break;
      }
      // 衝突
      Hit();
      // ワールド座標の更新
      WorldMatrix();
      // モデルのワールド座標の設定
      MV1SetMatrix(_modelHandle, AppMath::UtilityDX::ToMATRIX(_world));
    }

    void EnemyJerryfish::Draw() const {
      EnemyBase::Draw();
      // デバッグ情報描画
#ifdef _DEBUG
      // 攻撃球の衝突判定の描画
      _attack->Draw();
#endif
    }

    void EnemyJerryfish::SetParameters() {
      // モデルハンドルの設定
      _modelHandle = _app.GetModelLoadServer().GetDuplicateModelHandle(ModelKey::Jerryfish);
      // 各種パラメータの設定
      _scale.Fill(Scale);
      _enemyID = EnemyID::Jerryfish;
      _enemyState = EnemyState::Swim;
      _foodValue = FoodValue;
    }

    void EnemyJerryfish::SetCollision() {
      // 球のローカル座標の調整
      auto spherePosition = _position;
      spherePosition.SetY(SphereY);
      // 球の衝突判定の設定
      _sphere = std::make_unique<Collision::CollisionSphere>(*this, spherePosition, Radius);
      // 攻撃球の衝突判定の設定
      _attack = std::make_unique<Collision::CollisionSphere>(*this, spherePosition, AttackRadius);
    }

    void EnemyJerryfish::Move() {
      // 角度
      auto angle = AppMath::Vector4();
#ifdef _DEBUG
      // デグリー値をセット
      angle.SetY(RotateDegree);
#else
      // ラジアン値をセット
      angle.SetY(AppMath::Utility::DegreeToRadian(RotateDegree));
#endif
      // 向きに角度を加算
      _rotation.Add(angle);
      // 浮上量
      auto floatUp = AppMath::Vector4();
      floatUp.SetY(FloatUpSpeed);
      // 浮上量の追加
      _position.Add(floatUp);
      // 球の衝突判定の更新
      _sphere->Process(floatUp);
    }

    void EnemyJerryfish::Charge() {
      // 球のローカル座標
      auto spherePosition = _sphere->GetPosition();
      // 攻撃球のローカル座標の設定
      _attack->SetPosition(spherePosition);
      // 充電カウント上限の場合
      if (ChargeCountMax <= _chargeCount) {
        // 充電カウント初期化
        _chargeCount = 0;
        // 攻撃状態
        _enemyState = EnemyState::Attack;
        return;
      }
      // 充電カウントを増やす
      ++_chargeCount;
    }

    void EnemyJerryfish::Attack() {
      // 攻撃カウント上限の場合
      if (AttackCountMax <= _attackCount) {
        // 攻撃カウント初期化
        _attackCount = 0;
        // 遊泳状態
        _enemyState = EnemyState::Swim;
        return;
      }
      // 攻撃カウントを増やす
      ++_attackCount;
      // 攻撃
      bool attack = false;
      // プレイヤーのコピー
      auto player = _app.GetObjectServer().GetPlayerShark();
      // プレイヤーの本体球と衝突判定
      attack = _attack->IntersectSphere(std::dynamic_pointer_cast<Player::PlayerShark>(player)->GetSphere());
      // 攻撃が当たった場合
      if (attack) {
        // プレイヤーの被ダメ状態設定
        //player->
      }
    }
  } // namespace Enemy
} // namespace Game