/*****************************************************************//**
 * @file   EffectDiscover.cpp
 * @brief  エフェクト(発見)クラス
 * 
 * @author 宮澤耀生
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