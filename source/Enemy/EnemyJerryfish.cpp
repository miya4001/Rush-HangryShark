/*****************************************************************//**
 * @file   EnemyJerryfish.cpp
 * @brief  �G(�N���Q)�N���X
 * 
 * @author �{�V�s��
 * @date   September 2022
 *********************************************************************/
#include "EnemyJerryfish.h"
#include "../Application/ApplicationMain.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // �N���Q�e��萔
  constexpr int FoodValue = 1;      //!< �H���l
  constexpr float Scale = 0.15f;    //!< �g�嗦
  constexpr float SphereY = 50.0f;  //!< ��y���W
  constexpr float Radius = 50.0f;   //!< �����a
  // �ړ��萔
  constexpr float RotateDegree = 1.0f;  //!< ��]�p�x(�f�O���[�l)
  constexpr float FloatUpSpeed = 0.1f;  //!< ���㑬�x
}

namespace Game {
  namespace Enemy {
    EnemyJerryfish::EnemyJerryfish(Application::ApplicationMain& app) : EnemyBase(app) {
      Init();
    }

    void EnemyJerryfish::Process() {
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

    void EnemyJerryfish::SetParameters() {
      // ���f���n���h���̐ݒ�
      _modelHandle = _app.GetModelLoadServer().GetDuplicateModelHandle(ModelKey::Jerryfish);
      // �e��p�����[�^�̐ݒ�
      _scale.Fill(Scale);
      _enemyID = EnemyID::Jerryfish;
      _foodValue = FoodValue;
    }

    void EnemyJerryfish::SetCollision() {
      // ���̃��[�J�����W�̒���
      auto spherePosition = _position;
      spherePosition.SetY(SphereY);
      // ���̏Փ˔���̐ݒ�
      _sphere = std::make_unique<Collision::CollisionSphere>(*this, spherePosition, Radius);
    }

    void EnemyJerryfish::Move() {
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
      // �����
      auto floatUp = AppMath::Vector4();
      floatUp.SetY(FloatUpSpeed);
      // ����ʂ̒ǉ�
      _position.Add(floatUp);
      // ���̏Փ˔���̍X�V
      _sphere->Process(floatUp);
    }
  } // namespace Enemy
} // namespace Game