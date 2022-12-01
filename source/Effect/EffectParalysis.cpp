/*****************************************************************//**
 * @file   EffectParalysis.cpp
 * @brief  エフェクト(麻痺)クラス
 * 
 * @author 宮澤耀生
 * @date   December 2022
 *********************************************************************/
#include "EffectParalysis.h"
#include "../ConstLoadResourceKey.h"

namespace Game {
  namespace Effect {
    EffectParalysis::EffectParalysis(Application::ApplicationMain& app) : EffectBase(app) {
      Init();
    }

    void EffectParalysis::SetParameters() {
      _loadHandle = GetEffectLoadHandle(EffectKey::Paralysis);
    }
  } // namespace Effect
} // namespace Game