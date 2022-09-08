/*****************************************************************//**
 * @file   EnemyBase.cpp
 * @brief  �G�̊��N���X
 * 
 * @author �{�V�s��
 * @date   September 2022
 *********************************************************************/
#include "EnemyBase.h"

namespace Game {
  namespace Enemy {
    EnemyBase::EnemyBase(Application::ApplicationMain& app) : ObjectBase(app) {
      Init();
    }

    bool EnemyBase::Init() {
      // �p�����[�^�̐ݒ�
      SetParameters();
      return true;
    }

    void EnemyBase::Process() {
      // �C���͈͊O�̏ꍇ���f
      if (IsOverSea()) {
        return;
      }
      // ���[���h���W�̍X�V
      WorldMatrix();
      // ���f���̃��[���h���W�̐ݒ�
      MV1SetMatrix(_modelHandle, AppMath::UtilityDX::ToMATRIX(_world));
    }

    void EnemyBase::SetParameters() {
      // �e��p�����[�^�̐ݒ�
      _objectId = ObjectId::Enemy;
    }

    bool EnemyBase::IsOverSea() {
      // �C���͈͔���
      //if () {
      //  // ���S
      //  _objectState = ObjectState::Dead;
      //  // �C���͈͊O
      //  return true;
      //}
      // �C���͈͓�
      return false;
    }

    void EnemyBase::Hit() {

    }
  } // namespace Enemy
} // namespace Game