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
  constexpr int FoodValue = 3;      //!< �H���l
  constexpr float Scale = 0.1f;     //!< �g�嗦
  constexpr float SphereY = 20.0f;  //!< ��y���W
  constexpr float Radius = 20.0f;   //!< �����a
  // �ړ��萔
  constexpr float MoveSpeed = 1.0f;     //!< �ړ����x
  constexpr float RotateDegree = 1.0f;  //!< ��]�p�x(�f�O���[�l)
} // namespace

namespace Game {
  namespace Enemy {
    EnemyShrimp::EnemyShrimp(Application::ApplicationMain& app) : EnemyBase(app) {
      Init();
    }

    void EnemyShrimp::Process() {
      // �C���͈͊O�̏ꍇ���f
      if (!InTheSea()) {
        // ���S���
        SetDead();
        return;
      }
      // �G�r�̏�Ԃɍ��킹�ď���
      switch (_enemyState) {
      // �V�j
      case EnemyState::Swim:
        // �ړ�
        Move();
        break;
      // ���S
      case EnemyState::Dead:
        Dead();
        break;
      default:
        break;
      }
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
      _enemyState = EnemyState::Swim;
      _foodValue = FoodValue;
    }

    void EnemyShrimp::SetCollision() {
      // ���̃��[�J�����W�̒���
      auto spherePosition = _position;
      spherePosition.SetY(SphereY);
      // ���̏Փ˔���̐ݒ�
      _sphere = std::make_unique<Collision::CollisionSphere>(*this, spherePosition, Radius);
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