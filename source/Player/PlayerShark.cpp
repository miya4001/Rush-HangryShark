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
  constexpr float Scale = 1.25f;    //!< �g�嗦
  constexpr float Radius = 50.0f;   //!< �����a
  constexpr float SphereY = 25.0f;  //!< ��y���W
  // �󕠒萔
  constexpr int HungryMax = 100;      //!< �󕠒l���
  constexpr int HungryMin = 0;        //!< �󕠒l����
  constexpr int HungryInit = 30;      //!< �����󕠒l
  constexpr int HungryCountMax = 60;  //!< �󕠃J�E���g���
  // �ߐH�萔
  constexpr int EatCountMax = 60;  //!< �ߐH�J�E���g���
  // ��_���萔
  constexpr int DamageCountMax = 120;  //!< ��_���J�E���g���
  // ���S�萔
  constexpr float DeadPositionY = 50.0f;   //!< ���S�ʒuy
  constexpr float DeadRotationZ = 180.0f;  //!< ���S����z
  constexpr int DrawnSEVolume = 200;       //!< �M���SE����
  // ��]�萔
  constexpr float RotateDegree = 3.0f;  //!< ��]�p�x(�f�O���[�l)
  // �ړ��萔
  constexpr float SwimSpeed = 10.0f;  //!< ���j���x
  constexpr float RushSpeed = 20.0f;  //!< �ˌ����x
  // �U�������萔
  constexpr float AttackDistance = 50.0f;  //!< �U������
  // �V�j�A�j���[�V�����萔
  constexpr int AnimationCountMax = 30;  //!< �A�j���J�E���g���
  constexpr float AnimationY = 0.1f;     //!< �A�j���ʒuy
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
      // �v���C���[�̏�Ԃɍ��킹�ď���
      switch (_playerState) {
      // �ҋ@�E�V�j
      case PlayerState::Idle:
      case PlayerState::Swim:
        Swim();
        break;
      // �U��
      case PlayerState::Attack:
        Attack();
        break;
      // �ߐH
      case PlayerState::Eat:
        Eat();
        break;
      // ��_��
      case PlayerState::Damage:
        Damage();
        break;
        // ���S
      case PlayerState::Dead:
        Dead();
        break;
      default:
        break;
      }
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
      // �V�j�A�j���[�V����
      DrawFormatString(20, 260, GetColor(255, 255, 255), "animCount:%d", _animationCount);
      // ���_������
      DrawLine3D(VGet(-200.0f, 0.0f, 0.0f), VGet(200.0f, 0.0f, 0.0f), GetColor(255, 0, 0));
      DrawLine3D(VGet(0.0f, 0.0f, -200.0f), VGet(0.0f, 0.0f, 200.0f), GetColor(0, 255, 0));
      // �{�̋��̏Փ˔���̕`��
      _sphere->Draw();
      // �U�����̏Փ˔���̕`��
      _attack->Draw();
#endif
    }

    void PlayerShark::SetPlayerDamage() {
      // ��_����Ԃ̏ꍇ���f
      if (_playerState == PlayerState::Damage) {
        return;
      }
      // ��_�����
      _playerState = PlayerState::Damage;
      // ���SE�̍Đ�
      _app.GetSoundComponent().PlayBackGround(SoundKey::Paralysis);
      // ��_�����o(��)
#ifdef _DEBUG
        // �{�̋��̓h��Ԃ�
      _sphere->SetFill(true);
#endif
    }

    void PlayerShark::SetParameters() {
      // ���f���n���h���̐ݒ�
      _modelHandle = _app.GetModelLoadServer().GetDuplicateModelHandle(ModelKey::Shark);
      // �e��p�����[�^�̐ݒ�
      _objectId = ObjectId::Player;
      _scale.Fill(Scale);
      _hungry = HungryInit;
      _moveSpeed = SwimSpeed;
      // ����`��p�Ƀ��f���̊g�嗦�̐ݒ�
      MV1SetScale(_modelHandle, AppMath::UtilityDX::ToVECTOR(_scale));
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

    void PlayerShark::Swim() {
      // ��]
      Rotate();
      // �ړ� 
      Move();
      // �U������
      AttackReady();
      // �V�j�A�j���[�V����
      SwimAnimation();
    }

    void PlayerShark::Attack() {
      // �I�u�W�F�N�g�̃R�s�[
      auto objects = _app.GetObjectServer().GetObjects();
      // �G��T��
      for (auto&& object : objects) {
        if (object->GetId() != ObjectId::Enemy) {
          continue;
        }
        // �G�̃R�s�[
        auto enemy = std::dynamic_pointer_cast<Enemy::EnemyBase>(object);
        // �G�Ƃ̐ڐG����
        if (_attack->IntersectSphere(enemy->GetSphere())) {
          // �H���l���擾���ߐH�l��ݒ�
          _eatFood = enemy->GetFoodValue();
          // �G�̎��S
          enemy->SetEnemyDead();
          // �ߐH���
          _playerState = PlayerState::Eat;
          // �ߐHSE�̍Đ�
          _app.GetSoundComponent().PlayBackGround(SoundKey::Eat);
          break;
        }
        // �U���I��
        _playerState = PlayerState::Idle;
      }
    }

    void PlayerShark::Eat() {
      // �ߐH�J�E���g������̏ꍇ
      if (EatCountMax <= _eatCount) {
        // �ߐH�J�E���g������
        _eatCount = 0;
        // �󕠒l�ɕߐH�l�ǉ�
        _hungry += _eatFood;
        // �󕠒l�������
        if (HungryMax <= _hungry) {
          _hungry = HungryMax;
        }
#ifdef _DEBUG
        // �U�����̓h��Ԃ�����
        _attack->SetFill(false);
#endif
        // �ߐH�I��
        _playerState = PlayerState::Idle;
        return;
      }
      // �ߐH�J�E���g�𑝂₷
      ++_eatCount;
    }

    void PlayerShark::Damage() {
      // ��_���J�E���g������̏ꍇ
      if (DamageCountMax <= _damageCount) {
        // ��_���J�E���g������
        _damageCount = 0;
        // �ҋ@���
        _playerState = PlayerState::Idle;
#ifdef _DEBUG
        // �{�̋��̓h��Ԃ�����
        _sphere->SetFill(false);
#endif
        return;
      }
      // ��_���J�E���g�𑝂₷
      ++_damageCount;
    }

    void PlayerShark::Dead() {
      // ���S���o
      _position.SetY(DeadPositionY);
#ifdef _DEBUG
      // �f�O���[�l���Z�b�g
      _rotation.SetZ(DeadRotationZ);
#else
      // ���W�A���l���Z�b�g
      _rotation.SetZ(AppMath::Utility::DegreeToRadian(DeadRotationZ));
#endif
      // �Q�[���I�[�o�[
      _app.SetGameOver(true);
      // �M���SE�̍Đ�
      _app.GetSoundComponent().PlayBackGround(SoundKey::Drawn, DrawnSEVolume);
    }

    void PlayerShark::Rotate() {
      // ���͏�Ԃ̎擾
      auto&& xJoypad = _app.GetInputManager().GetXJoypad();
      // LB�{�^��(����)�̓��͏��
      bool leftB = xJoypad.GetButton(XINPUT_BUTTON_LEFT_SHOULDER, AppFrame::Input::InputPress);
      // RB�{�^��(����)�̓��͏��
      bool rightB = xJoypad.GetButton(XINPUT_BUTTON_RIGHT_SHOULDER, AppFrame::Input::InputPress);
      // �p�x
      auto angle = AppMath::Vector4();
      // �������͂܂��͓��͂Ȃ��̏ꍇ���f
      if (leftB == rightB) {
        return;
      }
      // ����]
      if (leftB) {
#ifdef _DEBUG
        // �f�O���[�l���Z�b�g
        angle.SetY(-RotateDegree);
#else
        // ���W�A���l���Z�b�g
        angle.SetY(AppMath::Utility::DegreeToRadian(-RotateDegree));
#endif
      }
      //�E��]
      if (rightB) {
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
      auto&& xJoypad = _app.GetInputManager().GetXJoypad();
      // ���X�e�B�b�N���͏��
      auto [leftX, leftY] = xJoypad.GetStick(AppFrame::Input::StickLeft);
      // ��������͂Ȃ��̏ꍇ���f
      if (leftY <= 0.0f) {
        return;
      }
      // �V�j���
      _playerState = PlayerState::Swim;
      // �ړ���
      auto move = AppMath::Vector4();
      // �O�������Ɉړ����x�{
      move = _forward * _moveSpeed;
      // �ړ��ʂ̒ǉ�
      _position.Add(move);
      // �{�̋��̏Փ˔���̍X�V
      _sphere->Process(move);
    }

    void PlayerShark::AttackReady() {
      // ���͏�Ԃ̎擾
      auto&& xJoypad = _app.GetInputManager().GetXJoypad();
      // A�{�^��(�g���K)�̓��͏��
      bool buttonA = xJoypad.GetButton(XINPUT_BUTTON_A, AppFrame::Input::InputTrigger);
      // �{�̋��̍��W
      auto spherePosition = _sphere->GetPosition();
      // �O�������̕s�v��y�𖳎�
      auto forward = _forward;
      forward.SetY(0.0f);
      // �O�������̕����ɒ����������{
      auto distance = forward * AttackDistance;
      // �U������{�̋����狗��������ɐݒ�
      auto attackPposition = spherePosition + distance;
      _attack->SetPosition(attackPposition);
      // ���͂�����ꍇ
      if (buttonA) {
        // �U�����
        _playerState = PlayerState::Attack;
        // ���݂�SE�̍Đ�
        _app.GetSoundComponent().PlayBackGround(SoundKey::Bite);
      }
    }

    void PlayerShark::SwimAnimation() {
      // �A�j���[�V����y
      auto animationY = AppMath::Vector4(0.0f, AnimationY, 0.0f);
      // ���[�J�����Wy
      float positionY = _position.GetY();
      // �V�j�㏸�ɍ��킹�ăA�j���[�V����
      if (_swimUp) {
        // �㏸�I���̏ꍇ
        if (AnimationCountMax <= _animationCount) {
          // �V�j���~
          _swimUp = false;
          // �A�j���J�E���g������
          _animationCount = 0;
          return;
        }
        // ���[�J�����Wy�ɉ��Z
        _position.Add(animationY);
      } else {
        // ���~�I���̏ꍇ
        if (AnimationCountMax <= _animationCount) {
          // �V�j�㏸
          _swimUp = true;
          // �A�j���J�E���g������
          _animationCount = 0;
          return;
        }
        // ���[�J�����Wy�Ɍ��Z
        _position.Sub(animationY);
      }
      // �A�j���J�E���g�𑝂₷
      ++_animationCount;
    }
  } // namespace Player
} // namespace Game