/*****************************************************************//**
 * @file   EffectBase.cpp
 * @brief  �G�t�F�N�g�̊��N���X
 * 
 * @author �{�V�s��
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
      // �p�����[�^�̐ݒ�
      SetParameters();
      // �G�t�F�N�g�Đ�
      PlayEffect();
      return true;
    }

    void EffectBase::Process() {
      // �G�t�F�N�g�Đ��I��������
      if (IsEffekseer3DEffectPlaying(_playHandle)) {
        // �G�t�F�N�g����
        DeadEffect();
        return;
      }
      // �G�t�F�N�g�̈ʒu��ݒ�
      auto [positionX, positionY, positionZ] = _position.GetVector3();
      SetPosPlayingEffekseer3DEffect(_playHandle, positionX, positionY, positionZ);
      // �G�t�F�N�g�̌�����ݒ�
      auto [rotationX, rotationY, rotationZ] = _rotation.GetVector3();
      SetRotationPlayingEffekseer3DEffect(_playHandle, rotationX, rotationY, rotationZ);
    }

    void EffectBase::DeadEffect() {
      // �G�t�F�N�g��~
      StopEffekseer3DEffect(_playHandle);
      // �G�t�F�N�g�Đ��n���h������
      _playHandle = -1;
      // �G�t�F�N�g���S���
      _effectState = EffectState::Dead;
    }

    void EffectBase::SetTransform(const AppMath::Vector4 position, const AppMath::Vector4 rotation) {
      _position = position;
      _rotation = rotation;
    }

    void EffectBase::SetParameters() {

    }

    void EffectBase::PlayEffect() {
      // �G�t�F�N�g�Đ�
      _playHandle = PlayEffekseer3DEffect(_loadHandle);
      // �G�t�F�N�g�������
      _effectState = EffectState::Active;
    }

    int EffectBase::GetEffectLoadHandle(const std::string_view key) {
      return _app.GetEffectLoadServer().GetEffectHandle(key);
    }
  } // namespace Effect
} // namespace Game