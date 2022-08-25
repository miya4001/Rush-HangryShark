/*****************************************************************//**
 * @file   PlayerShark.cpp
 * @brief  プレイヤー(サメ)クラス
 * 
 * @author 宮澤耀生
 * @date   July 2022
 *********************************************************************/
#include "PlayerShark.h"
#include "../Application/ApplicationMain.h"
#include "../Camera/Camera.h"

namespace {
  // プレイヤー各種定数
  constexpr auto Modelhandle = "shark";  //!< モデルハンドルキー
  constexpr int HungryMax = 100;         //!< 空腹値上限
  constexpr int HungryMin = 0;           //!< 空腹値下限
  constexpr int HungryInit = 75;         //!< 初期空腹値
  constexpr int HungryCountMax = 60;     //!< 空腹カウント上限
  constexpr int EatTimeMax = 60;         //!< 捕食時間上限
  constexpr int EatValue = 10;           //!< 捕食値
  constexpr float SwimSpeed = 5.0f;      //!< 水泳速度
  constexpr float RushSpeed = 10.0f;     //!< 突撃速度
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
      // 死亡状態判定
      if (IsDead()) {
        // ゲームオーバー
        return;
      }
      // 移動
      Swim();
      // 接触
      Hit();
      // 捕食
      Eat();
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
      DrawFormatString(0, 0, GetColor(255, 255, 255), "x:%f  y:%f, z:%f", x, y, z);
      // 向き
      auto [rX, rY, rZ] = _rotation.GetVector3();
      DrawFormatString(0, 20, GetColor(255, 255, 255), "rX:%f  rY:%f rZ:%f", rX, rY, rZ);
      // 左スティック入力
      auto [lx, ly] = _app.GetInputManager().GetXJoypad().GetStick(AppFrame::Input::StickLeft);
      DrawFormatString(0, 40, GetColor(255, 255, 255), "lx:%d  ly:%d", lx, ly);
      // 空腹
      DrawFormatString(0, 60, GetColor(255, 255, 255), "hungry:%d  count:%d", _hungry, _hungryCount);
      // 軸線分
      DrawLine3D(VGet(-200.0f, 0.0f, 0.0f), VGet(200.0f, 0.0f, 0.0f), GetColor(255, 0, 0));
      DrawLine3D(VGet(0.0f, 0.0f, -200.0f), VGet(0.0f, 0.0f, 200.0f), GetColor(0, 255, 0));
#endif
    }

    void PlayerShark::SetParameters() {
      // モデルハンドルの設定
      _modelHandle = _app.GetModelLoadServer().GetModelHandle(Modelhandle);
      // 各種パラメータの設定
      _scale.Fill(1.0f);
      _hungry = HungryInit;
      _speed = SwimSpeed;
    }

    void PlayerShark::Hungry() {
      // 捕食中の場合中断
      if (_isEating) {
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
          // 死亡
          _objectState = ObjectState::Dead;
        }
        return;
      }
      // 空腹カウントを増やす
      ++_hungryCount;
    }

    void PlayerShark::Swim() {
      // 捕食中の場合中断
      if (_isEating) {
        return;
      }
      // 移動量の算出
      auto move = Move();
      // ローカル座標の更新
      _position.Add(move);
    }

    void PlayerShark::Hit() {
      // 捕食中の場合中断
      if (_isEating) {
        return;
      }
      // 魚との接触判定
      // 捕食開始
      // _isEating = true;
    }

    void PlayerShark::Eat() {
      // 捕食中でない場合中断
      if (!_isEating) {
        return;
      }
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
        // 捕食終了
        _isEating = false;
        return;
      }
      // 捕食時間を増やす
      ++_eatTime;
    }

    AppMath::Vector4 PlayerShark::Move() {
      // 移動量
      auto move = AppMath::Vector4();
      // 入力状態の取得
      auto xJoypad = _app.GetInputManager().GetXJoypad();
      auto [leftX, leftY] = xJoypad.GetStick(AppFrame::Input::StickLeft);
      // 軸方向の入力状態(型変更)
      float x = static_cast<float>(leftX);
      float z = static_cast<float>(leftY);
      // 移動量が無い場合中断
      if (x * x + z * z == 0.0f) {
        return move;
      }
      // デッドゾーン最大値
      float deadZoneMax = static_cast<float>(xJoypad.GetDeadZoneMax());
      // 移動方向
      float moveX = x / deadZoneMax;
      float moveZ = z / deadZoneMax;
      // 移動量の設定
      move = AppMath::Vector4(moveX * _speed, 0.0f, moveZ * _speed);
      // ラジアン
      float radian = std::atan2(move.GetX(), -move.GetZ());
#ifdef _DEBUG
      // デグリー値をセット
      _rotation.Set(0.0f, AppMath::Utility::RadianToDegree(radian), 0.0f);
#else
      // ラジアン値をセット
      _rotation.Set(0.0f, radian, 0.0f);
#endif
      // 前方向きの設定
      _forward = AppMath::Vector4::Normalize(move);
      return move;
    }
  } // namespace Player
} // namespace Game