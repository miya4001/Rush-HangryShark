/*****************************************************************//**
 * @file   EnemyJerryfish.cpp
 * @brief  �G(�N���Q)�N���X
 * 
 * @author �{�V�s��
 * @date   September 2022
 *********************************************************************/
#include "EnemyJerryfish.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Player/PlayerShark.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // �N���Q�e��萔
  constexpr int FoodValue = 1;            //!< �H���l
  constexpr float Scale = 0.15f;          //!< �g�嗦
  constexpr float SphereY = 50.0f;        //!< ��y���W
  constexpr float Radius = 50.0f;         //!< �����a
  constexpr float AttackRadius = 100.0f;  //!< �U�������a
  // �ړ��萔
  constexpr float RotateDegree = 1.0f;  //!< ��]�p�x(�f�O���[�l)
  constexpr float FloatUpSpeed = 0.1f;  //!< ���㑬�x
  // �[�d�萔
  constexpr int ChargeCountMax = 300;  //!< �[�d�J�E���g���
  // �U���萔
  constexpr int AttackCountMax = 180;  //!< �U���J�E���g���
}

namespace Game {
  namespace Enemy {
    EnemyJerryfish::EnemyJerryfish(Application::ApplicationMain& app) : EnemyBase(app) {
      Init();
    }

    void EnemyJerryfish::Process() {
      // �C���͈͊O�̏ꍇ���f
      if (!InTheSea()) {
        // ���S���
        SetDead();
        return;
      }
      // �N���Q�̏�Ԃɍ��킹�ď���
      switch (_enemyState) {
      // �V�j
      case EnemyState::Swim:
        // �ړ�
        Move();
        // �[�d
        Charge();
        break;
      // �U��
      case EnemyState::Attack:
        Attack();
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

    void EnemyJerryfish::Draw() const {
      EnemyBase::Draw();
      // �f�o�b�O���`��
#ifdef _DEBUG
      // �U�����̏Փ˔���̕`��
      _attack->Draw();
#endif
    }

    void EnemyJerryfish::SetParameters() {
      // ���f���n���h���̐ݒ�
      _modelHandle = _app.GetModelLoadServer().GetDuplicateModelHandle(ModelKey::Jerryfish);
      // �e��p�����[�^�̐ݒ�
      _scale.Fill(Scale);
      _enemyID = EnemyID::Jerryfish;
      _enemyState = EnemyState::Swim;
      _foodValue = FoodValue;
    }

    void EnemyJerryfish::SetCollision() {
      // ���̃��[�J�����W�̒���
      auto spherePosition = _position;
      spherePosition.SetY(SphereY);
      // ���̏Փ˔���̐ݒ�
      _sphere = std::make_unique<Collision::CollisionSphere>(*this, spherePosition, Radius);
      // �U�����̏Փ˔���̐ݒ�
      _attack = std::make_unique<Collision::CollisionSphere>(*this, spherePosition, AttackRadius);
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

    void EnemyJerryfish::Charge() {
      // ���̃��[�J�����W
      auto spherePosition = _sphere->GetPosition();
      // �U�����̃��[�J�����W�̐ݒ�
      _attack->SetPosition(spherePosition);
      // �[�d�J�E���g����̏ꍇ
      if (ChargeCountMax <= _chargeCount) {
        // �[�d�J�E���g������
        _chargeCount = 0;
        // �U�����
        _enemyState = EnemyState::Attack;
        return;
      }
      // �[�d�J�E���g�𑝂₷
      ++_chargeCount;
    }

    void EnemyJerryfish::Attack() {
      // �U���J�E���g����̏ꍇ
      if (AttackCountMax <= _attackCount) {
        // �U���J�E���g������
        _attackCount = 0;
        // �V�j���
        _enemyState = EnemyState::Swim;
        return;
      }
      // �U���J�E���g�𑝂₷
      ++_attackCount;
      // �U��
      bool attack = false;
      // �v���C���[�̃R�s�[
      auto player = _app.GetObjectServer().GetPlayerShark();
      // �v���C���[�̖{�̋��ƏՓ˔���
      attack = _attack->IntersectSphere(std::dynamic_pointer_cast<Player::PlayerShark>(player)->GetSphere());
      // �U�������������ꍇ
      if (attack) {
        // �v���C���[�̔�_����Ԑݒ�
        //player->
      }
    }
  } // namespace Enemy
} // namespace Game