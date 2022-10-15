/*****************************************************************//**
 * @file   PlayerShark.cpp
 * @brief  プレイヤー(サメ)クラス
 * 
 * @author 宮澤耀生
 * @date   July 2022
 *********************************************************************/
#include "PlayerShark.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Camera/Camera.h"
#include "../Enemy/EnemyBase.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // プレイヤー各種定数
  constexpr float Scale = 1.0f;     //!< 拡大率
  constexpr float Radius = 50.0f;   //!< 球半径
  constexpr float SphereY = 25.0f;  //!< 球y座標
  // 空腹定数
  constexpr int HungryMax = 100;      //!< 空腹値上限
  constexpr int HungryMin = 0;        //!< 空腹値下限
  constexpr int HungryInit = 30;      //!< 初期空腹値
  constexpr int HungryCountMax = 60;  //!< 空腹カウント上限
  // 捕食定数
  constexpr int EatTimeMax = 60;  //!< 捕食時間上限
  constexpr int EatValue = 10;    //!< 捕食値
  // 回転・移動・攻撃準備定数
  constexpr float RotateDegree = 3.0f;     //!< 回転角度(デグリー値)
  constexpr float SwimSpeed = 10.0f;       //!< 水泳速度
  constexpr float RushSpeed = 20.0f;       //!< 突撃速度
  constexpr float AttackDistance = 50.0f;  //!< 攻撃距離
  // 遊泳アニメーション定数
  constexpr int AnimationCountMax = 60;  //!< アニメカウント上限
  constexpr float AnimationY = 0.05f;    //!< アニメy
}

namespace Game {
  namespace Player {
    PlayerShark::PlayerShark(Application::ApplicationMain& app) : ObjectBase(app) {
      Init();
    }

    bool PlayerShark::Init() {
      // パラメータの設定
      SetParameters();
      return true;
    }

    void PlayerShark::Process() {
      // 空腹
      Hungry();
      // プレイヤーの状態に合わせて処理
      switch (_playerState) {
      // 待機・移動
      case PlayerState::Idle:
      case PlayerState::Swim:
        // 遊泳
        Swim();
        break;
      case PlayerState::Attack:
        // 攻撃
        Attack();
        break;
      // 捕食
      case PlayerState::Eat:
        Eat();
        break;
      // 死亡
      case PlayerState::Dead:
        Dead();
        break;
      default:
        break;
      }
      // ワールド座標の更新
      WorldMatrix();
      // モデルのワールド座標の設定
      MV1SetMatrix(_modelHandle, AppMath::UtilityDX::ToMATRIX(_world));
      // 追従カメラ更新
      _app.GetCamera().Tracking(_position, _forward);
    }

    void PlayerShark::Draw() const {
      ObjectBase::Draw();
      // デバッグ情報描画
#ifdef _DEBUG
      // ローカル座標
      auto [x, y, z] = _position.GetVector3();
      DrawFormatString(20, 200, GetColor(255, 255, 255), "x:%f  y:%f, z:%f", x, y, z);
      // 向き
      auto [rX, rY, rZ] = _rotation.GetVector3();
      DrawFormatString(20, 220, GetColor(255, 255, 255), "rX:%f  rY:%f rZ:%f", rX, rY, rZ);
      // 空腹
      DrawFormatString(20, 240, GetColor(255, 255, 255), "hungry:%d  count:%d", _hungry, _hungryCount);
      // 遊泳アニメーション
      DrawFormatString(20, 260, GetColor(255, 255, 255), "animCount:%d", _animationCount);
      // 原点軸線分
      DrawLine3D(VGet(-200.0f, 0.0f, 0.0f), VGet(200.0f, 0.0f, 0.0f), GetColor(255, 0, 0));
      DrawLine3D(VGet(0.0f, 0.0f, -200.0f), VGet(0.0f, 0.0f, 200.0f), GetColor(0, 255, 0));
      // 本体球の衝突判定の描画
      _sphere->Draw();
      // 攻撃球の衝突判定の描画
      _attack->Draw();
#endif
    }

    void PlayerShark::SetParameters() {
      // モデルハンドルの設定
      _modelHandle = _app.GetModelLoadServer().GetDuplicateModelHandle(ModelKey::Shark);
      // 各種パラメータの設定
      _objectId = ObjectId::Player;
      _scale.Fill(Scale);
      _hungry = HungryInit;
      _moveSpeed = SwimSpeed;
      // 球の衝突判定の設定
      auto position = _position;
      position.SetY(SphereY);
      _sphere = std::make_unique<Collision::CollisionSphere>(*this, position, Radius);
      _attack = std::make_unique<Collision::CollisionSphere>(*this, position, Radius);
    }

    void PlayerShark::Hungry() {
      // 捕食中の場合中断
      if (_playerState == PlayerState::Eat) {
        return;
      }
      // 空腹カウントが上限の場合
      if (HungryCountMax <= _hungryCount) {
        // 空腹カウント初期化
        _hungryCount = 0;
        // 空腹値を減らす
        --_hungry;
        // 空腹値が下限の場合
        if (_hungry <= HungryMin) {
          // 死亡状態
          _playerState = PlayerState::Dead;
        }
        return;
      }
      // 空腹カウントを増やす
      ++_hungryCount;
    }

    void PlayerShark::Swim() {
      // 回転
      Rotate();
      // 移動 
      Move();
      // 攻撃準備
      AttackReady();
      // 遊泳アニメーション
      SwimAnimation();
    }

    void PlayerShark::Attack() {
      // オブジェクトのコピー
      auto objects = _app.GetObjectServer().GetObjects();
      // 敵を探す
      for (auto&& object : objects) {
        if (object->GetId() != ObjectId::Enemy) {
          continue;
        }
        // 敵との接触判定
        if (_attack->IntersectSphere(std::dynamic_pointer_cast<Enemy::EnemyBase>(object)->GetSphere())) {
          // 敵の死亡
          object->SetDead();
          // 捕食状態
          _playerState = PlayerState::Eat;
          break;
        }
        // 攻撃終了
        _playerState = PlayerState::Idle;
      }
    }

    void PlayerShark::Eat() {
      // 捕食時間が上限の場合
      if (EatTimeMax <= _eatTime) {
        // 捕食時間初期化
        _eatTime = 0;
        // 空腹値に捕食値追加
        _hungry += EatValue;
        // 空腹値上限調整
        if (HungryMax <= _hungry) {
          _hungry = HungryMax;
        }
#ifdef _DEBUG
        // 攻撃球の塗りつぶし解除
        _attack->NoFill();
#endif
        // 捕食終了
        _playerState = PlayerState::Idle;
        return;
      }
      // 捕食時間を増やす
      ++_eatTime;
    }

    void PlayerShark::Dead() {
      // 死亡演出
      _position.SetY(50.0f);
      _rotation.SetZ(180.0f);
      // ゲームオーバー
      _app.SetGameOver(true);
    }

    void PlayerShark::Rotate() {
      // 入力状態の取得
      auto&& xJoypad = _app.GetInputManager().GetXJoypad();
      // LBボタン(押下)の入力状態
      bool leftB = xJoypad.GetButton(XINPUT_BUTTON_LEFT_SHOULDER, AppFrame::Input::InputPress);
      // RBボタン(押下)の入力状態
      bool rightB = xJoypad.GetButton(XINPUT_BUTTON_RIGHT_SHOULDER, AppFrame::Input::InputPress);
      // 角度
      auto angle = AppMath::Vector4();
      // 同時入力または入力なしの場合中断
      if (leftB == rightB) {
        return;
      }
      // 左回転
      if (leftB) {
#ifdef _DEBUG
        // デグリー値をセット
        angle.SetY(-RotateDegree);
#else
        // ラジアン値をセット
        angle.SetY(AppMath::Utility::DegreeToRadian(-RotateDegree));
#endif
      }
      //右回転
      if (rightB) {
#ifdef _DEBUG
        // デグリー値をセット
        angle.SetY(RotateDegree);
#else
        // ラジアン値をセット
        angle.SetY(AppMath::Utility::DegreeToRadian(RotateDegree));
#endif
      }
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
      _forward = AppMath::Utility::TransformVector(front, rotateY);
    }

    void PlayerShark::Move() {
      // 入力状態の取得
      auto&& xJoypad = _app.GetInputManager().GetXJoypad();
      // 左スティック入力状態
      auto [leftX, leftY] = xJoypad.GetStick(AppFrame::Input::StickLeft);
      // 上方向入力なしの場合中断
      if (leftY <= 0.0f) {
        return;
      }
      // 遊泳状態
      _playerState = PlayerState::Swim;
      // 移動量
      auto move = AppMath::Vector4();
      // 前方向きに移動速度倍
      move = _forward * _moveSpeed;
      // 移動量の追加
      _position.Add(move);
      // 本体球の衝突判定の更新
      _sphere->Process(move);
    }

    void PlayerShark::AttackReady() {
      // 入力状態の取得
      auto&& xJoypad = _app.GetInputManager().GetXJoypad();
      // Aボタン(トリガ)の入力状態
      bool buttonA = xJoypad.GetButton(XINPUT_BUTTON_A, AppFrame::Input::InputTrigger);
      // 本体球の座標
      auto spherePosition = _sphere->GetPosition();
      // 前方向きの不要なyを無視
      auto forward = _forward;
      forward.SetY(0.0f);
      // 前方向きの方向に長さを距離倍
      auto distance = forward * AttackDistance;
      // 攻撃球を本体球から距離分後方に設定
      auto attackPposition = spherePosition + distance;
      _attack->SetPosition(attackPposition);
      // 入力がある場合
      if (buttonA) {
        // 攻撃状態
        _playerState = PlayerState::Attack;
      }
    }

    void PlayerShark::SwimAnimation() {
      // アニメーションy
      auto animationY = AppMath::Vector4(0.0f, AnimationY, 0.0f);
      // ローカル座標y
      float positionY = _position.GetY();
      // 遊泳上昇に合わせてアニメーション
      if (_swimUp) {
        // 上昇終了の場合
        if (AnimationCountMax <= _animationCount) {
          // 遊泳下降
          _swimUp = false;
          // アニメカウント初期化
          _animationCount = 0;
          return;
        }
        // ローカル座標yに加算
        _position.Add(animationY);
      } else {
        // 下降終了の場合
        if (AnimationCountMax <= _animationCount) {
          // 遊泳上昇
          _swimUp = true;
          // アニメカウント初期化
          _animationCount = 0;
          return;
        }
        // ローカル座標yに減算
        _position.Sub(animationY);
      }
      // アニメカウントを増やす
      ++_animationCount;
    }
  } // namespace Player
} // namespace Game