/*****************************************************************//**
 * @file   ResultComponent.cpp
 * @brief  ���U���g�R���|�[�l���g
 *
 * @author �{�V�s��
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
      // �ϐ�������
      _shrimp = 0;
      _tuna = 0;
      _jerryfish = 0;
    }

    void ResultComponent::DeadCount(Enemy::EnemyBase::EnemyID enemy) {
      // �G�̎��ʂɍ��킹�Đ��𑝂₷
      switch (enemy) {
      // �G�r
      case Game::Enemy::EnemyBase::EnemyID::Shrimp:
        ++_shrimp;
        break;
      // �}�O��
      case Game::Enemy::EnemyBase::EnemyID::Tuna:
        ++_tuna;
        break;
      // �N���Q
      case Game::Enemy::EnemyBase::EnemyID::Jerryfish:
        ++_jerryfish;
        break;
      // �Y���Ȃ�
      default:
        break;
      }
    }
  } // namespace Result
} // namespace Game