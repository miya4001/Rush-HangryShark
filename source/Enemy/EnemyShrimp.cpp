/*****************************************************************//**
 * @file   EnemyShrimp.cpp
 * @brief  �G(�G�r)�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#include "EnemyShrimp.h"
#include "../Application/ApplicationMain.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // �G�r�e��萔
  constexpr int FoodValue = 3;    //!< �H���l
  constexpr float Scale = 0.05f;  //!< �g�嗦
  // �ړ��萔
  constexpr float MoveSpeed = 1.0f;     //!< �ړ����x
  constexpr float RotateDegree = 1.0f;  //!< ��]�p�x(�f�O���[�l)
}

namespace Game {
  namespace Enemy {
    EnemyShrimp::EnemyShrimp(Application::ApplicationMain& app) : EnemyBase(app) {
      Init();
    }

    void EnemyShrimp::Process() {
      // �G�̏�Ԃ����S�̏ꍇ���f
      if (_enemyState == EnemyState::Dead) {
        // ���S
        Dead();
        return;
      }
      // �C���͈͊O�̏ꍇ���f
      if (!InTheSea()) {
        // ���S���
        SetDead();
        return;
      }
      // �ړ�
      Move();
      // �Փ�
      Hit();
      // ���[���h���W�̍X�V
      WorldMatrix();
      // ���f���̃��[���h���W�̐ݒ�
      MV1SetMatrix(_modelHandle, AppMath::UtilityDX::ToMATRIX(_world));
    }

    void EnemyShrimp::SetParameters() {
      // ���f���n���h���̐ݒ�
      _modelHandle = _app.GetModelLoadServer().GetDuplicateModelHandle(ModelKey::Shrimp);
      // �e��p�����[�^�̐ݒ�
      _scale.Fill(Scale);
      _enemyID = EnemyID::Shrimp;
      _foodValue = FoodValue;
    }

    void EnemyShrimp::Move() {
      // �p�x
      auto angle = AppMath::Vector4();
#ifdef _DEBUG
      // �f�O���[�l���Z�b�g
      angle.SetY(RotateDegree);
#else
      // ���W�A���l���Z�b�g
      angle.SetY(AppMath::Utility::DegreeToRadian(RotateDegree));
#endif
      // �����Ɋp�x�����Z
      _rotation.Add(angle);
      // y����]�s��
#ifdef _DEBUG
      auto rotateY = AppMath::Matrix44::ToRotationY(AppMath::Utility::DegreeToRadian(_rotation.GetY()));
#else
      auto rotateY = AppMath::Matrix44::ToRotationY(_rotation.GetY());
#endif
      // ����
      auto front = AppMath::Vector4(0.0f, 0.0f, -1.0f);
      // �O�������̎Z�o
      auto forward = AppMath::Utility::TransformVector(front, rotateY);
      // �ړ���
      auto move = forward * MoveSpeed;
      // �ړ��ʂ̒ǉ�
      _position.Add(move);
      // ���̏Փ˔���̍X�V
      _sphere->Process(move);
    }
  } // namespace Enemy
} // namespace Game