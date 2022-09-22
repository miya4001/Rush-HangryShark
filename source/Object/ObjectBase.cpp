/*****************************************************************//**
 * @file   ObjectBase.cpp
 * @brief  オブジェクトの基底クラス
 * 
 * @author 宮澤耀生
 * @date   July 2022
 *********************************************************************/
#include "ObjectBase.h"

namespace Game {
  namespace Object {
    ObjectBase::ObjectBase(Application::ApplicationMain& app) : _app(app) {
      _world = AppMath::Matrix44::Identity();
    }

    ObjectBase::~ObjectBase() {

    }

    bool ObjectBase::Init() {
      return true;
    }

    void ObjectBase::Process() {

    }

    void ObjectBase::Draw() const {
      // 死亡状態でない場合描画
      if (!IsDead()) {
        MV1DrawModel(_modelHandle);
      }
    }

    void ObjectBase::Dead() {
      _objectState = ObjectState::Dead;
    }

    bool ObjectBase::IsDead() const {
      return _objectState == ObjectState::Dead;
    }

    void ObjectBase::SetParameters() {

    }

    void ObjectBase::WorldMatrix() {
      // ワールド座標変換
#ifdef _DEBUG
      _world = AppMath::Utility::ToWorldMatrix(_position, _rotation, _scale, AppMath::Degree);
#else
      _world = AppMath::Utility::ToWorldMatrix(_position, _rotation, _scale, AppMath::Radian);
#endif
    }
  } // namespace Object
} // namespace Game