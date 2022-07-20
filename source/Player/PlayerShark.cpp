/*****************************************************************//**
 * @file   PlayerShark.cpp
 * @brief  プレイヤー(サメ)クラス
 * 
 * @author 宮澤耀生
 * @date   July 2022
 *********************************************************************/
#include "PlayerShark.h"

namespace {
  // プレイヤー各種定数
  constexpr int HungryMax = 100;       //!< 空腹値上限
  constexpr int HungryMin = 0;         //!< 空腹値下限
  constexpr int HungryInit = 75;       //!< 初期空腹値
  constexpr int HungryCountMax = 120;  //!< 空腹カウント上限
  constexpr int EatTimeMax = 60;       //!< 捕食時間上限
  constexpr int EatValue = 10;         //!< 捕食値
  constexpr float SwimSpeed = 10.0f;   //!< 移動速度
  constexpr float RushSpeed = 20.0f;   //!< 突撃速度
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
    }

    void PlayerShark::SetParameters() {
      // 各種パラメータの設定
      _hungry = HungryInit;
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
      // 移動処理
    }

    void PlayerShark::Hit() {
      // 捕食中の場合中断
      if (_isEating) {
        return;
      }
      // 捕食開始
      _isEating = true;
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
  } // namespace Player
} // namespace Game