/*****************************************************************//**
 * @file   PlayerShark.cpp
 * @brief  �v���C���[(�T��)�N���X
 * 
 * @author �{�V�s��
 * @date   July 2022
 *********************************************************************/
#include "PlayerShark.h"
#include "../Application/ApplicationMain.h"
#include "../Camera/Camera.h"

namespace {
  // �v���C���[�e��萔
  constexpr auto Modelhandle = "shark";  //!< ���f���n���h���L�[
  constexpr int HungryMax = 100;         //!< �󕠒l���
  constexpr int HungryMin = 0;           //!< �󕠒l����
  constexpr int HungryInit = 75;         //!< �����󕠒l
  constexpr int HungryCountMax = 60;     //!< �󕠃J�E���g���
  constexpr int EatTimeMax = 60;         //!< �ߐH���ԏ��
  constexpr int EatValue = 10;           //!< �ߐH�l
  constexpr float SwimSpeed = 5.0f;      //!< ���j���x
  constexpr float RushSpeed = 10.0f;     //!< �ˌ����x
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
      if (IsDead()) {
        // �Q�[���I�[�o�[
        return;
      }
      // �ړ�
      Swim();
      // �ڐG
      Hit();
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
      DrawFormatString(0, 0, GetColor(255, 255, 255), "x:%f  y:%f, z:%f", x, y, z);
      // ����
      auto [rX, rY, rZ] = _rotation.GetVector3();
      DrawFormatString(0, 20, GetColor(255, 255, 255), "rX:%f  rY:%f rZ:%f", rX, rY, rZ);
      // ���X�e�B�b�N����
      auto [lx, ly] = _app.GetInputManager().GetXJoypad().GetStick(AppFrame::Input::StickLeft);
      DrawFormatString(0, 40, GetColor(255, 255, 255), "lx:%d  ly:%d", lx, ly);
      // ��
      DrawFormatString(0, 60, GetColor(255, 255, 255), "hungry:%d  count:%d", _hungry, _hungryCount);
      // ������
      DrawLine3D(VGet(-200.0f, 0.0f, 0.0f), VGet(200.0f, 0.0f, 0.0f), GetColor(255, 0, 0));
      DrawLine3D(VGet(0.0f, 0.0f, -200.0f), VGet(0.0f, 0.0f, 200.0f), GetColor(0, 255, 0));
#endif
    }

    void PlayerShark::SetParameters() {
      // ���f���n���h���̐ݒ�
      _modelHandle = _app.GetModelLoadServer().GetModelHandle(Modelhandle);
      // �e��p�����[�^�̐ݒ�
      _scale.Fill(1.0f);
      _hungry = HungryInit;
      _speed = SwimSpeed;
    }

    void PlayerShark::Hungry() {
      // �ߐH���̏ꍇ���f
      if (_isEating) {
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
          // ���S
          _objectState = ObjectState::Dead;
        }
        return;
      }
      // �󕠃J�E���g�𑝂₷
      ++_hungryCount;
    }

    void PlayerShark::Swim() {
      // �ߐH���̏ꍇ���f
      if (_isEating) {
        return;
      }
      // �ړ��ʂ̎Z�o
      auto move = Move();
      // ���[�J�����W�̍X�V
      _position.Add(move);
    }

    void PlayerShark::Hit() {
      // �ߐH���̏ꍇ���f
      if (_isEating) {
        return;
      }
      // ���Ƃ̐ڐG����
      // �ߐH�J�n
      // _isEating = true;
    }

    void PlayerShark::Eat() {
      // �ߐH���łȂ��ꍇ���f
      if (!_isEating) {
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
        _isEating = false;
        return;
      }
      // �ߐH���Ԃ𑝂₷
      ++_eatTime;
    }

    AppMath::Vector4 PlayerShark::Move() {
      // �ړ���
      auto move = AppMath::Vector4();
      // ���͏�Ԃ̎擾
      auto xJoypad = _app.GetInputManager().GetXJoypad();
      auto [leftX, leftY] = xJoypad.GetStick(AppFrame::Input::StickLeft);
      // �������̓��͏��(�^�ύX)
      float x = static_cast<float>(leftX);
      float z = static_cast<float>(leftY);
      // �ړ��ʂ������ꍇ���f
      if (x * x + z * z == 0.0f) {
        return move;
      }
      // �f�b�h�]�[���ő�l
      float deadZoneMax = static_cast<float>(xJoypad.GetDeadZoneMax());
      // �ړ�����
      float moveX = x / deadZoneMax;
      float moveZ = z / deadZoneMax;
      // �ړ��ʂ̐ݒ�
      move = AppMath::Vector4(moveX * _speed, 0.0f, moveZ * _speed);
      // ���W�A��
      float radian = std::atan2(move.GetX(), -move.GetZ());
#ifdef _DEBUG
      // �f�O���[�l���Z�b�g
      _rotation.Set(0.0f, AppMath::Utility::RadianToDegree(radian), 0.0f);
#else
      // ���W�A���l���Z�b�g
      _rotation.Set(0.0f, radian, 0.0f);
#endif
      // �O�������̐ݒ�
      _forward = AppMath::Vector4::Normalize(move);
      return move;
    }
  } // namespace Player
} // namespace Game