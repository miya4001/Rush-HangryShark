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
#include "../Player/PlayerShark.h"

namespace {
  // 海中背景各種定数
  constexpr auto Modelhandle = "sea";  //!< モデルハンドルキー
  constexpr float Scale = 0.5f;        //!< 拡大率
  constexpr float Radius = 2500.0f;    //!< 球半径
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
      // プレイヤーのコピー
      auto player = _app.GetObjectServer().GetPlayerShark();
      // プレイヤーのローカル座標に更新
      _position = player->GetPosition();
      // 球のローカル座標の設定
      _sphere->SetPosition(_position);
      // ワールド座標の更新
      WorldMatrix();
      // モデルのワールド座標の設定
      MV1SetMatrix(_modelHandle, AppMath::UtilityDX::ToMATRIX(_world));
    }

    void SeaSphere::SetParameters() {
      // モデルハンドルの設定
      _modelHandle = _app.GetModelLoadServer().GetModelHandle(Modelhandle);
      // 各種パラメータの設定
      _objectId = ObjectId::Sea;
      _scale.Fill(Scale);
      // 球の衝突判定の設定
      _sphere = std::make_unique<Collision::CollisionSphere>(*this, _position, Radius);
    }
  } // namespace Sea
} // namespace Game