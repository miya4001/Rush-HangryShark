/*****************************************************************//**
 * @file   PlayerShark.cpp
 * @brief  �v���C���[(�T��)�N���X
 * 
 * @author �{�V�s��
 * @date   July 2022
 *********************************************************************/
#include "PlayerShark.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"
#include "../Camera/Camera.h"
#include "../Enemy/EnemyBase.h"
#include "../ConstLoadResourceKey.h"

namespace {
  // �v���C���[�e��萔
  constexpr int HungryMax = 100;           //!< �󕠒l���
  constexpr int HungryMin = 0;             //!< �󕠒l����
  constexpr int HungryInit = 75;           //!< �����󕠒l
  constexpr int HungryCountMax = 60;       //!< �󕠃J�E���g���
  constexpr int EatTimeMax = 60;           //!< �ߐH���ԏ��
  constexpr int EatValue = 10;             //!< �ߐH�l
  constexpr float Scale = 1.0f;            //!< �g�嗦
  constexpr float Radius = 50.0f;          //!< �����a
  constexpr float SphereY = 25.0f;         //!< ��y���W
  constexpr float RotateDegree = 3.0f;     //!< ��]�p�x(�f�O���[�l)
  constexpr float SwimSpeed = 10.0f;       //!< ���j���x
  constexpr float RushSpeed = 20.0f;       //!< �ˌ����x
  constexpr float AttackDistance = 50.0f;  //!< �U������
}

namespace Game {
  namespace Player {
    PlayerShark::PlayerShark(Application::ApplicationMain& app) : ObjectBase(app) {
      Init();
    }

    bool PlayerShark::Init() {
      // �p�����[�^�̐ݒ�
      SetParameters();
      return true;
    }

    void PlayerShark::Process() {
      // ��
      Hungry();
      // ���S��Ԕ���
      if (_playerState == PlayerState::Dead) {
        // �Q�[���I�[�o�[
        _app.SetGameOver(true);
        return;
      }
      // ��]
      Rotate();
      // �ړ� 
      Move();
      // �U��
      Attack();
      // �ߐH
      Eat();
      // ���[���h���W�̍X�V
      WorldMatrix();
      // ���f���̃��[���h���W�̐ݒ�
      MV1SetMatrix(_modelHandle, AppMath::UtilityDX::ToMATRIX(_world));
      // �Ǐ]�J�����X�V
      _app.GetCamera().Tracking(_position, _forward);
    }

    void PlayerShark::Draw() const {
      ObjectBase::Draw();
      // �f�o�b�O���`��
#ifdef _DEBUG
      // ���[�J�����W
      auto [x, y, z] = _position.GetVector3();
      DrawFormatString(20, 200, GetColor(255, 255, 255), "x:%f  y:%f, z:%f", x, y, z);
      // ����
      auto [rX, rY, rZ] = _rotation.GetVector3();
      DrawFormatString(20, 220, GetColor(255, 255, 255), "rX:%f  rY:%f rZ:%f", rX, rY, rZ);
      // ��
      DrawFormatString(20, 240, GetColor(255, 255, 255), "hungry:%d  count:%d", _hungry, _hungryCount);
      // ���_������
      DrawLine3D(VGet(-200.0f, 0.0f, 0.0f), VGet(200.0f, 0.0f, 0.0f), GetColor(255, 0, 0));
      DrawLine3D(VGet(0.0f, 0.0f, -200.0f), VGet(0.0f, 0.0f, 200.0f), GetColor(0, 255, 0));
      // �{�̋��̏Փ˔���̕`��
      _sphere->Draw();
      // �U�����̏Փ˔���̕`��
      _attack->Draw();
#endif
    }

    void PlayerShark::SetParameters() {
      // ���f���n���h���̐ݒ�
      _modelHandle = _app.GetModelLoadServer().GetDuplicateModelHandle(ModelKey::Shark);
      // �e��p�����[�^�̐ݒ�
      _objectId = ObjectId::Player;
      _scale.Fill(Scale);
      _hungry = HungryInit;
      _speed = SwimSpeed;
      // ���̏Փ˔���̐ݒ�
      auto position = _position;
      position.SetY(SphereY);
      _sphere = std::make_unique<Collision::CollisionSphere>(*this, position, Radius);
      _attack = std::make_unique<Collision::CollisionSphere>(*this, position, Radius);
    }

    void PlayerShark::Hungry() {
      // �ߐH���̏ꍇ���f
      if (_playerState == PlayerState::Eat) {
        return;
      }
      // �󕠃J�E���g������̏ꍇ
      if (HungryCountMax <= _hungryCount) {
        // �󕠃J�E���g������
        _hungryCount = 0;
        // �󕠒l�����炷
        --_hungry;
        // �󕠒l�������̏ꍇ
        if (_hungry <= HungryMin) {
          // ���S���
          _playerState = PlayerState::Dead;
        }
        return;
      }
      // �󕠃J�E���g�𑝂₷
      ++_hungryCount;
    }

    void PlayerShark::Rotate() {
      // ���͏�Ԃ̎擾
      auto xJoypad = _app.GetInputManager().GetXJoypad();
      // LB�{�^��(����)�̓��͏��
      bool leftB = xJoypad.GetButton(XINPUT_BUTTON_LEFT_SHOULDER, AppFrame::Input::InputPress);
      // RB�{�^��(����)�̓��͏��
      bool rightB = xJoypad.GetButton(XINPUT_BUTTON_RIGHT_SHOULDER, AppFrame::Input::InputPress);
      // �p�x
      auto angle = AppMath::Vector4();
      // ���͏�Ԃɉ����Ċp�x�̐ݒ�
      if (leftB) {
        // ����]
#ifdef _DEBUG
      // �f�O���[�l���Z�b�g
        angle.SetY(-RotateDegree);
#else
      // ���W�A���l���Z�b�g
        angle.SetY(AppMath::Utility::DegreeToRadian(-RotateDegree));
#endif
      } else if (rightB) {
        //�E��]
#ifdef _DEBUG
      // �f�O���[�l���Z�b�g
        angle.SetY(RotateDegree);
#else
      // ���W�A���l���Z�b�g
        angle.SetY(AppMath::Utility::DegreeToRadian(RotateDegree));
#endif
      }
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
      _forward = AppMath::Utility::TransformVector(front, rotateY);
    }

    void PlayerShark::Move() {
      // ���͏�Ԃ̎擾
      auto xJoypad = _app.GetInputManager().GetXJoypad();
      // ���X�e�B�b�N���͏��
      auto [leftX, leftY] = xJoypad.GetStick(AppFrame::Input::StickLeft);
      // ��������͂������ꍇ���f
      if (leftY <= 0.0f) {
        return;
      }
      // �ړ����
      _playerState = PlayerState::Swim;
      // �ړ���
      auto move = AppMath::Vector4();
      // �O�������Ɉړ����x�{
      move = _forward * _speed;
      // �ړ��ʂ̒ǉ�
      _position.Add(move);
      // �{�̋��̏Փ˔���̍X�V
      _sphere->Process(move);
    }

    void PlayerShark::Attack() {
      // ���͏�Ԃ̎擾
      auto xJoypad = _app.GetInputManager().GetXJoypad();
      // A�{�^��(�g���K)�̓��͏��
      bool buttonA = xJoypad.GetButton(XINPUT_BUTTON_A, AppFrame::Input::InputTrigger);
      // �{�̋��̍��W
      auto spherePosition = _sphere->GetPosition();
      // �U�����Ă��Ȃ��ꍇ���f
      if (!buttonA) {
        // �U������{�̋��ƍ��킹��
        _attack->SetPosition(spherePosition);
#ifdef _DEBUG
        _attack->NoFill();
#endif
        return;
      }
      // �U�����
      _playerState = PlayerState::Attack;
      // �O�������̕s�v��y�𖳎�
      auto forward = _forward;
      forward.SetY(0.0f);
      // �O�������̕����ɒ����������{
      auto distance = forward * AttackDistance;
      // �U������{�̋����狗��������ɐݒ�
      auto attackPposition = spherePosition + distance;
      _attack->SetPosition(attackPposition);
      // �I�u�W�F�N�g�̃R�s�[
      auto objects = _app.GetObjectServer().GetObjects();
      // �G��T��
      for (auto object : objects) {
        if (object->GetId() != ObjectId::Enemy) {
          continue;
        }
        // �G�Ƃ̐ڐG����
        if (_attack->IntersectSphere(std::dynamic_pointer_cast<Enemy::EnemyBase>(object)->GetSphere())) {
          // �G�̎��S
          object->Dead();
          // �ߐH���
          _playerState = PlayerState::Eat;
          break;
        }
        // �U���I��
        _playerState = PlayerState::Idle;
      }
    }

    void PlayerShark::Eat() {
      // �ߐH���łȂ��ꍇ���f
      if (_playerState != PlayerState::Eat) {
        return;
      }
      // �ߐH���Ԃ�����̏ꍇ
      if (EatTimeMax <= _eatTime) {
        // �ߐH���ԏ�����
        _eatTime = 0;
        // �󕠒l�ɕߐH�l�ǉ�
        _hungry += EatValue;
        // �󕠒l�������
        if (HungryMax <= _hungry) {
          _hungry = HungryMax;
        }
        // �ߐH�I��
        _playerState = PlayerState::Idle;
        return;
      }
      // �ߐH���Ԃ𑝂₷
      ++_eatTime;
    }
  } // namespace Player
} // namespace Game