/*****************************************************************//**
 * @file   EnemyBase.cpp
 * @brief  敵の基底クラス
 * 
 * @author 宮澤耀生
 * @date   September 2022
 *********************************************************************/
#include "EnemyBase.h"

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
      // 海中範囲外の場合中断
      if (IsOverSea()) {
        return;
      }
      // ワールド座標の更新
      WorldMatrix();
      // モデルのワールド座標の設定
      MV1SetMatrix(_modelHandle, AppMath::UtilityDX::ToMATRIX(_world));
    }

    void EnemyBase::SetParameters() {
      // 各種パラメータの設定
      _objectId = ObjectId::Enemy;
    }

    bool EnemyBase::IsOverSea() {
      // 海中範囲判定
      //if () {
      //  // 死亡
      //  _objectState = ObjectState::Dead;
      //  // 海中範囲外
      //  return true;
      //}
      // 海中範囲内
      return false;
    }

    void EnemyBase::Hit() {

    }
  } // namespace Enemy
} // namespace Game