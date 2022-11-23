/*****************************************************************//**
 * @file   EffectBase.cpp
 * @brief  エフェクトの基底クラス
 * 
 * @author 宮澤耀生
 * @date   November 2022
 *********************************************************************/
#include "EffectBase.h"
#include <EffekseerForDXLib.h>
#include "../Application/ApplicationMain.h"

namespace Game {
  namespace Effect {
    EffectBase::EffectBase(Application::ApplicationMain& app) : _app(app) {

    }

    EffectBase::~EffectBase() {

    }

    bool EffectBase::Init() {
      // パラメータの設定
      SetParameters();
      // エフェクト再生
      PlayEffect();
      return true;
    }

    void EffectBase::Process() {
      // エフェクト再生終了したか
      if (IsEffekseer3DEffectPlaying(_playHandle)) {
        // エフェクト消去
        DeadEffect();
        return;
      }
      // エフェクトの位置を設定
      auto [positionX, positionY, positionZ] = _position.GetVector3();
      SetPosPlayingEffekseer3DEffect(_playHandle, positionX, positionY, positionZ);
      // エフェクトの向きを設定
      auto [rotationX, rotationY, rotationZ] = _rotation.GetVector3();
      SetRotationPlayingEffekseer3DEffect(_playHandle, rotationX, rotationY, rotationZ);
    }

    void EffectBase::DeadEffect() {
      // エフェクト停止
      StopEffekseer3DEffect(_playHandle);
      // エフェクト再生ハンドル消去
      _playHandle = -1;
      // エフェクト死亡状態
      _effectState = EffectState::Dead;
    }

    void EffectBase::SetTransform(const AppMath::Vector4 position, const AppMath::Vector4 rotation) {
      _position = position;
      _rotation = rotation;
    }

    void EffectBase::SetParameters() {

    }

    void EffectBase::PlayEffect() {
      // エフェクト再生
      _playHandle = PlayEffekseer3DEffect(_loadHandle);
      // エフェクト活動状態
      _effectState = EffectState::Active;
    }

    int EffectBase::GetEffectLoadHandle(const std::string_view key) {
      return _app.GetEffectLoadServer().GetEffectHandle(key);
    }
  } // namespace Effect
} // namespace Game