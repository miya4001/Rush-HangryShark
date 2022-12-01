/*****************************************************************//**
 * @file   EffectDiscover.cpp
 * @brief  �G�t�F�N�g(����)�N���X
 * 
 * @author �{�V�s��
 * @date   December 2022
 *********************************************************************/
#include "EffectDiscover.h"
#include "../ConstLoadResourceKey.h"

namespace Game {
  namespace Effect {
    EffectDiscover::EffectDiscover(Application::ApplicationMain& app) : EffectBase(app) {
      Init();
    }

    void EffectDiscover::SetParameters() {
      _loadHandle = GetEffectLoadHandle(EffectKey::Discover);
    }
  } // namespace Effect
} // namespace Game