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
  constexpr float Scale = 0.1f;  //!< �g�嗦
  // �ړ��萔
  constexpr float RotateDegree = 1.0f;  //!< ��]�p�x(�f�O���[�l)
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
    }
  } // namespace Enemy
} // namespace Game