/*****************************************************************//**
 * @file   EnemyTuna.cpp
 * @brief  �G(�}�O��)�N���X
 * 
 * @author �{�V�s��
 * @date   September 2022
 *********************************************************************/
#include "EnemyTuna.h"
#include "../Application/ApplicationMain.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // �}�O���e��萔
  constexpr float Scale = 0.15f;        //!< �g�嗦
  constexpr float Speed = 2.0f;         //!< �ړ����x
  constexpr float RotateDegree = 1.0f;  //!< ��]�p�x(�f�O���[�l)
}

namespace Game {
  namespace Enemy {
    EnemyTuna::EnemyTuna(Application::ApplicationMain& app) : EnemyBase(app) {
      Init();
    }

    void EnemyTuna::Process() {
      // �C���͈͊O�̏ꍇ���f
      if (!InTheSea()) {
        // ���S
        Dead();
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

    void EnemyTuna::SetParameters() {
      // ���f���n���h���̐ݒ�
      _modelHandle = _app.GetModelLoadServer().GetDuplicateModelHandle(ModelKey::Tuna);
      // �e��p�����[�^�̐ݒ�
      _scale.Fill(Scale);
    }

    void EnemyTuna::Move() {
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
      auto move = forward * Speed;
      // �ړ��ʂ̒ǉ�
      _position.Add(move);
      // ���̏Փ˔���̍X�V
      _sphere->Process(move);
    }
  } // namespace Enemy
} // namespace Game