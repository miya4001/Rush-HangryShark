/*****************************************************************//**
 * @file   PlayerShark.cpp
 * @brief  �v���C���[(�T��)�N���X
 * 
 * @author �{�V�s��
 * @date   July 2022
 *********************************************************************/
#include "PlayerShark.h"

namespace {
  // �v���C���[�e��萔
  constexpr int HungryMax = 100;       //!< �󕠒l���
  constexpr int HungryMin = 0;         //!< �󕠒l����
  constexpr int HungryInit = 75;       //!< �����󕠒l
  constexpr int HungryCountMax = 120;  //!< �󕠃J�E���g���
  constexpr int EatTimeMax = 60;       //!< �ߐH���ԏ��
  constexpr int EatValue = 10;         //!< �ߐH�l
  constexpr float SwimSpeed = 10.0f;   //!< �ړ����x
  constexpr float RushSpeed = 20.0f;   //!< �ˌ����x
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
    }

    void PlayerShark::SetParameters() {
      // �e��p�����[�^�̐ݒ�
      _hungry = HungryInit;
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
      // �ړ�����
    }

    void PlayerShark::Hit() {
      // �ߐH���̏ꍇ���f
      if (_isEating) {
        return;
      }
      // �ߐH�J�n
      _isEating = true;
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
  } // namespace Player
} // namespace Game