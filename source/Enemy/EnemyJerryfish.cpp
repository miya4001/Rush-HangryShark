/*****************************************************************//**
 * @file   EnemyJerryfish.cpp
 * @brief  敵(クラゲ)クラス
 * 
 * @author 宮澤耀生
 * @date   September 2022
 *********************************************************************/
#include "EnemyJerryfish.h"
#include "../Application/ApplicationMain.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // クラゲ各種定数
  constexpr int FoodValue = 1;      //!< 食料値
  constexpr float Scale = 0.15f;    //!< 拡大率
  constexpr float SphereY = 50.0f;  //!< 球y座標
  constexpr float Radius = 50.0f;   //!< 球半径
  // 移動定数
  constexpr float RotateDegree = 1.0f;  //!< 回転角度(デグリー値)
  constexpr float FloatUpSpeed = 0.1f;  //!< 浮上速度
}

namespace Game {
  namespace Enemy {
    EnemyJerryfish::EnemyJerryfish(Application::ApplicationMain& app) : EnemyBase(app) {
      Init();
    }

    void EnemyJerryfish::Process() {
      // 敵の状態が死亡の場合中断
      if (_enemyState == EnemyState::Dead) {
        // 死亡
        Dead();
        return;
      }
      // 海中範囲外の場合中断
      if (!InTheSea()) {
        // 死亡状態
        SetDead();
        return;
      }
      // 移動
      Move();
      // 衝突
      Hit();
      // ワールド座標の更新
      WorldMatrix();
      // モデルのワールド座標の設定
      MV1SetMatrix(_modelHandle, AppMath::UtilityDX::ToMATRIX(_world));
    }

    void EnemyJerryfish::SetParameters() {
      // モデルハンドルの設定
      _modelHandle = _app.GetModelLoadServer().GetDuplicateModelHandle(ModelKey::Jerryfish);
      // 各種パラメータの設定
      _scale.Fill(Scale);
      _enemyID = EnemyID::Jerryfish;
      _foodValue = FoodValue;
    }

    void EnemyJerryfish::SetCollision() {
      // 球のローカル座標の調整
      auto spherePosition = _position;
      spherePosition.SetY(SphereY);
      // 球の衝突判定の設定
      _sphere = std::make_unique<Collision::CollisionSphere>(*this, spherePosition, Radius);
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
  } // namespace Enemy
} // namespace Game