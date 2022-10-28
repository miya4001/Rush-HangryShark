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
  constexpr float Scale = 0.15f;        //!< 拡大率
  constexpr float Speed = 1.0f;         //!< 移動速度
  constexpr float RotateDegree = 2.0f;  //!< 回転角度(デグリー値)
}

namespace Game {
  namespace Enemy {
    EnemyShrimp::EnemyShrimp(Application::ApplicationMain& app) : EnemyBase(app) {
      Init();
    }

    void EnemyShrimp::Process() {
      // 海中範囲外の場合中断
      if (!InTheSea()) {
        // 死亡
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

    void EnemyShrimp::SetParameters() {
      // モデルハンドルの設定
      _modelHandle = _app.GetModelLoadServer().GetDuplicateModelHandle(ModelKey::Tuna);
      // 各種パラメータの設定
      _scale.Fill(Scale);
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
      auto move = forward * Speed;
      // 移動量の追加
      _position.Add(move);
      // 球の衝突判定の更新
      _sphere->Process(move);
    }
  } // namespace Enemy
} // namespace Game