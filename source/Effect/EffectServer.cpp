/*****************************************************************//**
 * @file   EffectServer.cpp
 * @brief  エフェクトを管理するサーバクラス
 * 
 * @author 宮澤耀生
 * @date   November 2022
 *********************************************************************/
#include "EffectServer.h"
#include <EffekseerForDXLib.h>
#include "../Application/ApplicationMain.h"
#include "EffectBase.h"
#include "EffectBlood.h"

namespace Game {
  namespace Effect {
    EffectServer::EffectServer(Application::ApplicationMain& app) : _app(app) {
      // レジストリの初期化
      _effectRegistry.clear();
    }

    EffectServer::~EffectServer() {

    }

    void EffectServer::Release() {
      // レジストリが空の場合中断
      if (_effectRegistry.empty()) {
        return;
      }
      // エフェクトの全解放
      for (auto&& effect : _effectRegistry) {
        // エフェクト停止
        effect->DeadEffect();
        // 解放
        effect.reset();
      }
      // レジストリの解放
      _effectRegistry.clear();
    }

    void EffectServer::Process() {
      // レジストリ内のエフェクトの更新
      for (auto&& effect : _effectRegistry) {
        // エフェクトが死亡状態でない場合
        if (effect->IsDead()) {
          // 更新
          effect->Process();
        }
      }
      // DXライブラリのカメラとEffekseerのカメラを同期
      Effekseer_Sync3DSetting();
      // Effekseerにより再生中のエフェクトを更新
      UpdateEffekseer3D();
      // 不要になったエフェクトを削除
      std::erase_if(_effectRegistry, [](auto&& effect) {return effect->IsDead(); });
    }

    void EffectServer::Draw() const {
      // Effekseerにより再生中のエフェクトを描画
      DrawEffekseer3D();
    }

    void EffectServer::MakeEffect(const int number, const AppMath::Vector4 position, const AppMath::Vector4 rotation) {
      // 識別番号から判別
      switch (number) {
      // 血
      case EffectNumber::Blood:
        RegisterEffect(Blood(position, rotation));
        break;
      // 該当なし
      default:
#ifdef _DEBUG
        throw ("EffectServer:識別番号が不正です\n");
#endif
        break;
      }
    }

    void EffectServer::RegisterEffect(std::shared_ptr<EffectBase> effect) {
      // エフェクトがnullの場合エラー
      if (effect == nullptr) {
#ifdef _DEBUG
        throw ("エフェクトはnullptrです");
#endif
        return;
      }
      // 登録
      _effectRegistry.emplace_back(std::move(effect));
    }

    std::shared_ptr<EffectBlood> EffectServer::Blood(const AppMath::Vector4 position, const AppMath::Vector4 rotation) {
      // 血の生成
      auto blood = std::make_shared<EffectBlood>(_app);
      // エフェクト再生情報の設定
      blood->SetTransform(position, rotation);
      // 生成したシェアードポインタを返す
      return std::move(blood);
    }
  } // namespace Effect
} // namespace Game