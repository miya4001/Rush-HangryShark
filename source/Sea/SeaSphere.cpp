/*****************************************************************//**
 * @file   SeaSphere.cpp
 * @brief  海中背景クラス
 * 
 * @author 宮澤耀生
 * @date   August 2022
 *********************************************************************/
#include "SeaSphere.h"
#include "../Application/ApplicationMain.h"
#include "../Object/ObjectServer.h"

namespace {
  // 海中背景各種定数
  constexpr auto Modelhandle = "sea";  //!< モデルハンドルキー
}

namespace Game {
  namespace Sea {
    SeaSphere::SeaSphere(Application::ApplicationMain& app) : ObjectBase(app) {
      Init();
    }

    bool SeaSphere::Init() {
      // パラメータの設定
      SetParameters();
      return true;
    }

    void SeaSphere::Process() {
      // オブジェクトのコピー
      auto objects = _app.GetObjectServer().GetObjects();
      // プレイヤーを探す
      for (auto obj : objects) {
        if (obj->GetId() == ObjectId::Player) {
          // プレイヤーのローカル座標に更新
          _position = obj->GetPosition();
          break;
        }
      }
      // ワールド座標の更新
      WorldMatrix();
      // モデルのワールド座標の設定
      MV1SetMatrix(_modelHandle, AppMath::UtilityDX::ToMATRIX(_world));
    }

    void SeaSphere::SetParameters() {
      // モデルハンドルの設定
      _modelHandle = _app.GetModelLoadServer().GetModelHandle(Modelhandle);
      // 各種パラメータの設定
      _scale.Fill(1.0f);
    }
  } // namespace Sea
} // namespace Game