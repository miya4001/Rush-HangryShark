/*****************************************************************//**
 * @file   ResultComponent.cpp
 * @brief  リザルトコンポーネント
 *
 * @author 宮澤耀生
 * @date   December 2022
 *********************************************************************/
#include "ResultComponent.h"

namespace Game {
  namespace Result {
    ResultComponent::ResultComponent() {

    }

    ResultComponent::~ResultComponent() {

    }

    void ResultComponent::Release() {
      // 変数初期化
      _shrimp = 0;
      _tuna = 0;
      _jerryfish = 0;
    }

    void ResultComponent::DeadCount(Enemy::EnemyBase::EnemyID enemy) {
      // 敵の識別に合わせて数を増やす
      switch (enemy) {
      // エビ
      case Game::Enemy::EnemyBase::EnemyID::Shrimp:
        ++_shrimp;
        break;
      // マグロ
      case Game::Enemy::EnemyBase::EnemyID::Tuna:
        ++_tuna;
        break;
      // クラゲ
      case Game::Enemy::EnemyBase::EnemyID::Jerryfish:
        ++_jerryfish;
        break;
      // 該当なし
      default:
        break;
      }
    }
  } // namespace Result
} // namespace Game