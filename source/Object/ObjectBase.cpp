/*****************************************************************//**
 * @file   ObjectBase.cpp
 * @brief  �I�u�W�F�N�g�̊��N���X
 * 
 * @author �{�V�s��
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

    }

    bool ObjectBase::IsDead() const {
      return _objectState == ObjectState::Dead;
    }

    void ObjectBase::WorldMatrix() {
      // ���[���h���W�ϊ�
#ifdef _DEBUG
      _world = AppMath::Utility::ToWorldMatrix(_position, _rotation, _scale, AppMath::Degree);
#else
      _world = AppMath::Utility::ToWorldMatrix(_position, _rotation, _scale, AppMath::Radian);
#endif
    }
  } // namespace Object
} // namespace Game