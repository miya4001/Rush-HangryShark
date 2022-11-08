/*****************************************************************//**
 * @file   EnemyTuna.cpp
 * @brief  �G(�}�O��)�N���X
 * 
 * @author �{�V�s��
 * @date   September 2022
 *********************************************************************/
#include "EnemyTuna.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Player/PlayerShark.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // �}�O���e��萔
  constexpr int FoodValue = 8;            //!< �H���l
  constexpr float Scale = 0.25f;          //!< �g�嗦
  constexpr float ScaleX = 0.75f;         //!< �g�嗦x
  constexpr float SphereY = 40.0f;        //!< ��y���W
  constexpr float Radius = 40.0f;         //!< �����a
  constexpr float SearchRadius = 400.0f;  //!< �T�������a
  // �ړ��萔
  constexpr float MoveSpeed = 3.0f;     //!< �ړ����x
  constexpr float RotateDegree = 1.0f;  //!< ��]�p�x(�f�O���[�l)
  // �����萔
  constexpr float EscapeSpeed = 8.0f;  //!< �������x
}

namespace Game {
  namespace Enemy {
    EnemyTuna::EnemyTuna(Application::ApplicationMain& app) : EnemyBase(app) {
      Init();
    }

    void EnemyTuna::Process() {
      // �C���͈͊O�̏ꍇ���f
      if (!InTheSea()) {
        // ���S���
        SetDead();
        return;
      }
      // �}�O���̏�Ԃɍ��킹�ď���
      switch (_enemyState) {
      // �ҋ@�E�V�j
      case EnemyState::Idle:
      case EnemyState::Swim:
        // �ړ�
        Move();
        // �T��
        Search();
        break;
      // ����
      case EnemyState::Escape:
        Escape();
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

    void EnemyTuna::Draw() const {
      EnemyBase::Draw();
      // �f�o�b�O���`��
#ifdef _DEBUG
      // �T�����̏Փ˔���̕`��
      _search->Draw();
#endif
    }

    void EnemyTuna::SetParameters() {
      // ���f���n���h���̐ݒ�
      _modelHandle = _app.GetModelLoadServer().GetDuplicateModelHandle(ModelKey::Tuna);
      // �e��p�����[�^�̐ݒ�
      _scale.Fill(Scale);
      _scale.SetX(ScaleX);
      _enemyID = EnemyID::Tuna;
      _foodValue = FoodValue;
    }

    void EnemyTuna::SetCollision() {
      // ���̃��[�J�����W�̒���
      auto spherePosition = _position;
      spherePosition.SetY(SphereY);
      // ���̏Փ˔���̐ݒ�
      _sphere = std::make_unique<Collision::CollisionSphere>(*this, spherePosition, Radius);
      // �T�����̏Փ˔���̐ݒ�
      _search = std::make_unique<Collision::CollisionSphere>(*this, spherePosition, SearchRadius);
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
      auto move = forward * MoveSpeed;
      // �ړ��ʂ̒ǉ�
      _position.Add(move);
      // ���̏Փ˔���̍X�V
      _sphere->Process(move);
    }

    void EnemyTuna::Search() {
      // ���̃��[�J�����W
      auto pos = _sphere->GetPosition();
      // �T�����̃��[�J�����W�̐ݒ�
      _search->SetPosition(pos);
      // ����
      bool discover = false;
      // �v���C���[�̃R�s�[
      auto player = _app.GetObjectServer().GetPlayerShark();
      // �v���C���[�̍U�����ƏՓ˔���
      discover = _search->IntersectSphere(std::dynamic_pointer_cast<Player::PlayerShark>(player)->GetAttack());
      // �v���C���[�𔭌������ꍇ
      if (discover) {
        // �������
        _enemyState = EnemyState::Escape;
      }
    }

    void EnemyTuna::Escape() {
      // �v���C���[�̃R�s�[
      auto player = _app.GetObjectServer().GetPlayerShark();
      // �v���C���[�̃��[�J�����W
      auto playerPosition = player->GetPosition();
      // �v���C���[����G�֌������x�N�g��
      auto playerToEnemy = playerPosition.Direction(_position);
      // �s�v��y�𖳎�
      playerToEnemy.SetY(0.0f);
      // �x�N�g���̐��K��
      playerToEnemy.Normalize();
      // ������
      auto escape = playerToEnemy * EscapeSpeed;
      // ���W�A���̎Z�o
      auto radian = std::atan2(-escape.GetX(), -escape.GetZ());
#ifdef _DEBUG
      // �f�O���[�l���Z�b�g
      _rotation.SetY(AppMath::Utility::RadianToDegree(radian));
#else
      // ���W�A���l���Z�b�g
      _rotation.SetY(radian);
#endif
      // �����ʂ̒ǉ�
      _position.Add(escape);
      // ���̏Փ˔���̍X�V
      _sphere->Process(escape);
      // ���̏Փ˔���̍X�V
      _search->Process(escape);
#ifdef _DEBUG
      // �T�����̓h��Ԃ�����
      _search->NoFill();
#endif
    }
  } // namespace Enemy
} // namespace Game