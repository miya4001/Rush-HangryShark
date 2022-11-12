/*****************************************************************//**
 * @file   Camera.cpp
 * @brief  �J�����N���X
 * 
 * @author �{�V�s��
 * @date   July 2022
 *********************************************************************/
#include "Camera.h"

namespace {
  // �J�����e��萔
  constexpr float Near = 50.0f;        //!< ��O�N���b�v����
  constexpr float Far = 10000.0f;      //!< ���N���b�v����
  constexpr float PositionY = 100.0f;  //!< �ʒuy���W
  constexpr float TargetY = 50.0f;     //!< �����_y���W
  constexpr float Distance = 250.0f;   //!< �ʒu-�����_�ԋ���
} // namespace

namespace Game {
  namespace Camera {
    Camera::Camera() {
      Init();
    }

    Camera::~Camera() {

    }

    bool Camera::Init() {
      // �J�����N���b�v�����ݒ�
      SetCameraNearFar(Near, Far);
      return true;
    }

    void Camera::Tracking(const AppMath::Vector4 target, const AppMath::Vector4 forward) {
      // �����_�̐ݒ�
      _target = target;
      _target.SetY(TargetY);
      // �O�������̕s�v��y�𖳎�
      auto forwardTarget = forward;
      forwardTarget.SetY(0.0f);
      // �O�������̋t�����ɒ����������{
      auto distance = forwardTarget * -Distance;
      // �ʒu�𒍎��_���狗��������ɐݒ�
      _position = target + distance;
      _position.SetY(PositionY);
      //�J�����̍X�V
      SetCameraPositionAndTarget_UpVecY(AppMath::UtilityDX::ToVECTOR(_position), AppMath::UtilityDX::ToVECTOR(_target));
    }

    void Camera::FixedPoint(const AppMath::Vector4 position, const AppMath::Vector4 target) {
      _position = position;
      _target = target;
      //�J�����̍X�V
      SetCameraPositionAndTarget_UpVecY(AppMath::UtilityDX::ToVECTOR(_position), AppMath::UtilityDX::ToVECTOR(_target));
    }
  } // namespace Camera
} // namespace Game