/*****************************************************************//**
 * @file   EnemyShrimp.cpp
 * @brief  敵(エビ)クラス
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#include "EnemyShrimp.h"
#include "../Application/ApplicationMain.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // エビ各種定数
  constexpr int FoodValue = 3;      //!< 食料値
  constexpr float Scale = 0.1f;     //!< 拡大率
  constexpr float SphereY = 20.0f;  //!< 球y座標
  constexpr float Radius = 20.0f;   //!< 球半径
  // 移動定数
  constexpr float MoveSpeed = 1.0f;     //!< 移動速度
  constexpr float RotateDegree = 1.0f;  //!< 回転角度(デグリー値)
} // namespace

namespace Game {
  namespace Enemy {
    EnemyShrimp::EnemyShrimp(Application::ApplicationMain& app) : EnemyBase(app) {
      Init();
    }

    void EnemyShrimp::Process() {
      // 海中範囲外の場合中断
      if (!InTheSea()) {
        // 死亡状態
        SetDead();
        return;
      }
      // エビの状態に合わせて処理
      switch (_enemyState) {
      // 遊泳
      case EnemyState::Swim:
        // 移動
        Move();
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

    void EnemyShrimp::SetParameters() {
      // モデルハンドルの設定
      _modelHandle = _app.GetModelLoadServer().GetDuplicateModelHandle(ModelKey::Shrimp);
      // 各種パラメータの設定
      _scale.Fill(Scale);
      _enemyID = EnemyID::Shrimp;
      _enemyState = EnemyState::Swim;
      _foodValue = FoodValue;
    }

    void EnemyShrimp::SetCollision() {
      // 球のローカル座標の調整
      auto spherePosition = _position;
      spherePosition.SetY(SphereY);
      // 球の衝突判定の設定
      _sphere = std::make_unique<Collision::CollisionSphere>(*this, spherePosition, Radius);
    }

    void EnemyShrimp::Move() {
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
      // y軸回転行列
#ifdef _DEBUG
      auto rotateY = AppMath::Matrix44::ToRotationY(AppMath::Utility::DegreeToRadian(_rotation.GetY()));
#else
      auto rotateY = AppMath::Matrix44::ToRotationY(_rotation.GetY());
#endif
      // 正面
      auto front = AppMath::Vector4(0.0f, 0.0f, -1.0f);
      // 前方向きの算出
      auto forward = AppMath::Utility::TransformVector(front, rotateY);
      // 移動量
      auto move = forward * MoveSpeed;
      // 移動量の追加
      _position.Add(move);
      // 球の衝突判定の更新
      _sphere->Process(move);
    }
  } // namespace Enemy
} // namespace Game