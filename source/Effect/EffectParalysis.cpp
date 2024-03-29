/*****************************************************************//**
 * @file   EffectParalysis.cpp
 * @brief  GtFNg(á)NX
 * 
 * @author {āVsķ
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