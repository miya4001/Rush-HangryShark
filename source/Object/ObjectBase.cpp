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

    }

    ObjectBase::~ObjectBase() {

    }

    bool ObjectBase::Init() {

    }

    void ObjectBase::Process() {

    }

    void ObjectBase::Draw() const {

    }

    bool ObjectBase::IsDead() const {
      return _objectState == ObjectState::Dead;
    }

    void ObjectBase::WorldMatrix() {

    }
  } // namespace Object
} // namespace Game