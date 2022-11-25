/*****************************************************************//**
 * @file   EffectBlood.cpp
 * @brief  �G�t�F�N�g(��)�N���X
 * 
 * @author �{�V�s��
 * @date   November 2022
 *********************************************************************/
#include "EffectBlood.h"
#include "../ConstLoadResourceKey.h"

namespace Game {
  namespace Effect {
    EffectBlood::EffectBlood(Application::ApplicationMain& app) : EffectBase(app) {
      Init();
    }

    void EffectBlood::SetParameters() {
      _loadHandle = GetEffectLoadHandle(EffectKey::Blood);
    }
  } // namespace Effect
} // namespace Game