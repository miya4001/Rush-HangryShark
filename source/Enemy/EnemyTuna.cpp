/*****************************************************************//**
 * @file   EnemyTuna.cpp
 * @brief  敵(マグロ)クラス
 * 
 * @author 宮澤耀生
 * @date   September 2022
 *********************************************************************/
#include "EnemyTuna.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Player/PlayerShark.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // マグロ各種定数
  constexpr int FoodValue = 8;            //!< 食料値
  constexpr float Scale = 0.25f;          //!< 拡大率
  constexpr float ScaleX = 0.75f;         //!< 拡大率x
  constexpr float SphereY = 40.0f;        //!< 球y座標
  constexpr float Radius = 40.0f;         //!< 球半径
  constexpr float SearchRadius = 400.0f;  //!< 探索球半径
  // 移動定数
  constexpr float MoveSpeed = 3.0f;     //!< 移動速度
  constexpr float RotateDegree = 1.0f;  //!< 回転角度(デグリー値)
  // 逃走定数
  constexpr float EscapeSpeed = 8.0f;  //!< 逃走速度
}

namespace Game {
  namespace Enemy {
    EnemyTuna::EnemyTuna(Application::ApplicationMain& app) : EnemyBase(app) {
      Init();
    }

    void EnemyTuna::Process() {
      // 海中範囲外の場合中断
      if (!InTheSea()) {
        // 死亡状態
        SetDead();
        return;
      }
      // マグロの状態に合わせて処理
      switch (_enemyState) {
      // 待機・遊泳
      case EnemyState::Idle:
      case EnemyState::Swim:
        // 移動
        Move();
        // 探索
        Search();
        break;
      // 逃走
      case EnemyState::Escape:
        Escape();
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

    void EnemyTuna::Draw() const {
      EnemyBase::Draw();
      // デバッグ情報描画
#ifdef _DEBUG
      // 探索球の衝突判定の描画
      _search->Draw();
#endif
    }

    void EnemyTuna::SetParameters() {
      // モデルハンドルの設定
      _modelHandle = _app.GetModelLoadServer().GetDuplicateModelHandle(ModelKey::Tuna);
      // 各種パラメータの設定
      _scale.Fill(Scale);
      _scale.SetX(ScaleX);
      _enemyID = EnemyID::Tuna;
      _foodValue = FoodValue;
    }

    void EnemyTuna::SetCollision() {
      // 球のローカル座標の調整
      auto spherePosition = _position;
      spherePosition.SetY(SphereY);
      // 球の衝突判定の設定
      _sphere = std::make_unique<Collision::CollisionSphere>(*this, spherePosition, Radius);
      // 探索球の衝突判定の設定
      _search = std::make_unique<Collision::CollisionSphere>(*this, spherePosition, SearchRadius);
    }

    void EnemyTuna::Move() {
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

    void EnemyTuna::Search() {
      // 球のローカル座標
      auto pos = _sphere->GetPosition();
      // 探索球のローカル座標の設定
      _search->SetPosition(pos);
      // 発見
      bool discover = false;
      // プレイヤーのコピー
      auto player = _app.GetObjectServer().GetPlayerShark();
      // プレイヤーの攻撃球と衝突判定
      discover = _search->IntersectSphere(std::dynamic_pointer_cast<Player::PlayerShark>(player)->GetAttack());
      // プレイヤーを発見した場合
      if (discover) {
        // 逃走状態
        _enemyState = EnemyState::Escape;
      }
    }

    void EnemyTuna::Escape() {
      // プレイヤーのコピー
      auto player = _app.GetObjectServer().GetPlayerShark();
      // プレイヤーのローカル座標
      auto playerPosition = player->GetPosition();
      // プレイヤーから敵へ向かうベクトル
      auto playerToEnemy = playerPosition.Direction(_position);
      // 不要なyを無視
      playerToEnemy.SetY(0.0f);
      // ベクトルの正規化
      playerToEnemy.Normalize();
      // 逃走量
      auto escape = playerToEnemy * EscapeSpeed;
      // ラジアンの算出
      auto radian = std::atan2(-escape.GetX(), -escape.GetZ());
#ifdef _DEBUG
      // デグリー値をセット
      _rotation.SetY(AppMath::Utility::RadianToDegree(radian));
#else
      // ラジアン値をセット
      _rotation.SetY(radian);
#endif
      // 逃走量の追加
      _position.Add(escape);
      // 球の衝突判定の更新
      _sphere->Process(escape);
      // 球の衝突判定の更新
      _search->Process(escape);
#ifdef _DEBUG
      // 探索球の塗りつぶし解除
      _search->NoFill();
#endif
    }
  } // namespace Enemy
} // namespace Game