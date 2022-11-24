/*****************************************************************//**
 * @file   EffectServer.cpp
 * @brief  �G�t�F�N�g���Ǘ�����T�[�o�N���X
 * 
 * @author �{�V�s��
 * @date   November 2022
 *********************************************************************/
#include "EffectServer.h"
#include <EffekseerForDXLib.h>
#include "EffectBase.h"

namespace Game {
  namespace Effect {
    EffectServer::EffectServer() {
      // ���W�X�g���̏�����
      _effectRegistry.clear();
    }

    EffectServer::~EffectServer() {

    }

    void EffectServer::Release() {
      // ���W�X�g������̏ꍇ���f
      if (_effectRegistry.empty()) {
        return;
      }
      // �G�t�F�N�g�̑S���
      for (auto&& effect : _effectRegistry) {
        // �G�t�F�N�g��~
        effect->DeadEffect();
        // ���
        effect.reset();
      }
      // ���W�X�g���̉��
      _effectRegistry.clear();
    }

    void EffectServer::Process() {
      // ���W�X�g�����̃G�t�F�N�g�̍X�V
      for (auto&& effect : _effectRegistry) {
        // �G�t�F�N�g�����S��ԂłȂ��ꍇ
        if (effect->IsDead()) {
          // �X�V
          effect->Process();
        }
      }
      // DX���C�u�����̃J������Effekseer�̃J�����𓯊�
      Effekseer_Sync3DSetting();
      // Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V
      UpdateEffekseer3D();
      // �s�v�ɂȂ����G�t�F�N�g���폜
      std::erase_if(_effectRegistry, [](auto&& effect) {return effect->IsDead(); });
    }

    void EffectServer::Draw() const {
      // Effekseer�ɂ��Đ����̃G�t�F�N�g��`��
      DrawEffekseer3D();
    }

    void EffectServer::MakeEffect(const int number, const AppMath::Vector4 position, const AppMath::Vector4 rotation) {
      // ���ʔԍ����画��
      switch (number) {
      // �Y���Ȃ�
      default:
#ifdef _DEBUG
        throw ("EffectServer:���ʔԍ����s���ł�\n");
#endif
        break;
      }
    }

    void EffectServer::RegisterEffect(std::shared_ptr<EffectBase> effect) {
      // �G�t�F�N�g��null�̏ꍇ�G���[
      if (effect == nullptr) {
#ifdef _DEBUG
        throw ("�G�t�F�N�g��nullptr�ł�");
#endif
        return;
      }
      // �o�^
      _effectRegistry.emplace_back(std::move(effect));
    }
  } // namespace Effect
} // namespace Game