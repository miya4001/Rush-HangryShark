/*****************************************************************//**
 * @file   Camera.cpp
 * @brief  カメラクラス
 * 
 * @author 宮澤耀生
 * @date   July 2022
 *********************************************************************/
#include "Camera.h"

namespace {
  // カメラ各種定数
  constexpr float Near = 100.0f;      //!< 手前クリップ距離
  constexpr float Far = 5000.0f;      //!< 奥クリップ距離
  constexpr float Distance = 250.0f;  //!< 位置-注視点間距離
}

namespace Game {
  namespace Camera {
    Camera::Camera() {
      Init();
    }

    Camera::~Camera() {

    }

    bool Camera::Init() {
      // カメラクリップ距離設定
      SetCameraNearFar(Near, Far);
      return true;
    }

    void Camera::Tracking(const AppMath::Vector4 target, const AppMath::Vector4 forward) {
      _target = target;
      // 前方向きの不要なyを無視
      auto forwardTarget = forward;
      forwardTarget.SetY(0.0f);
      // 前方向きの逆方向に長さを距離倍
      auto distance = forwardTarget * -Distance;
      // 位置を注視点から距離分後方にする
      _position = target + distance;
      //カメラの更新
      SetCameraPositionAndTarget_UpVecY(AppMath::UtilityDX::ToVECTOR(_position), AppMath::UtilityDX::ToVECTOR(_target));
    }

    void Camera::FixedPoint(const AppMath::Vector4 position, const AppMath::Vector4 target) {
      _position = position;
      _target = target;
      //カメラの更新
      SetCameraPositionAndTarget_UpVecY(AppMath::UtilityDX::ToVECTOR(_position), AppMath::UtilityDX::ToVECTOR(_target));
    }
  } // namespace Camera
} // namespace Game